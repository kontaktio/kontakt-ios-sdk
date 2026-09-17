//  Copyright © 2024 Kontakt.io

import Foundation
import Combine
import KontaktSDK

@globalActor
private actor ScanningResultsActor {
    static let shared = ScanningResultsActor()
}

enum NearbyDevicesScannerError: LocalizedError {
    case nearbyDeviceNotFound(String)
    case scanningError(sdkError: Error)

    var localizedDescription: String {
        switch self {
        case let .nearbyDeviceNotFound(uniqueId):
            "Device (\(uniqueId)) not found"
        case let .scanningError(sdkError):
            "Scanning interrupted: \(sdkError.localizedDescription)"
        }
    }
}

final class NearbyDevicesScanner {

    @Published var bluetoothOff = false
    @Published var nearbyDevices: Set<NearbyDevice> = []
    var nearbyDevicesPublisher = CurrentValueSubject<Result<Set<NearbyDevice>, NearbyDevicesScannerError>, Never>(.success([]))

    private var privateTelemetryPublisher: PassthroughSubject<NearbyDeviceTelemetry, Never> = .init()
    var telemetryPublisher: AnyPublisher<NearbyDeviceTelemetry, Never> {
        privateTelemetryPublisher.eraseToAnyPublisher()
    }

    private(set) var isScanning = false
    fileprivate let devicesManager: DevicesManager
    private let devicesManagerDelegateProxy: KTKDevicesManagerDelegateProxy
    private var disappearCandidatePool: Set<String> = Set()
    private var cancellables: Set<AnyCancellable> = []

    init() {
        devicesManagerDelegateProxy = .init()
        devicesManager = DevicesManager(delegate: devicesManagerDelegateProxy)
        devicesManagerDelegateProxy.delegate = self
        $nearbyDevices.sink { [weak self] value in
            self?.nearbyDevicesPublisher.send(.success(value))
        }.store(in: &cancellables)
    }

    func startScanning(interval: Double) {
        if devicesManager.discoveryInterval != interval {
            stopScanning()
        }

        guard isScanning == false else { return }

        print("[Nearby Devices Scanner] - Start with interval: \(interval) sec")

        devicesManager.invalidationAge = 15.0
        devicesManager.isDetectingLocks = true
        devicesManager.startDevicesDiscovery(interval: interval)

        isScanning = true
    }

    func stopScanning() {
        print("[Nearby Devices Scanner] - Stop")

        devicesManager.stopDevicesDiscovery()

        // Using ScanningResultsActor to prevent races with removing nearby device in `processDiscoveredDevices` method
        Task { @ScanningResultsActor [weak self] in
            self?.nearbyDevices.removeAll()
        }

        isScanning = false
    }

    func nearbyDevice(uniqueId: String) -> NearbyDevice? {
        guard !uniqueId.isEmpty else {
            return nil
        }

        return nearbyDevices.first { $0.uniqueID == uniqueId }
    }

    @ScanningResultsActor
    fileprivate func processDiscoveredDevices(_ devices: [NearbyDevice]) async {
        var nearbyDevices = self.nearbyDevices
        let newDevices = devices.filter { $0.uniqueID != nil }

        // Remove devices that are not present after two updates
        disappearCandidatePool
            .filter { uniqueID in
                !newDevices.contains { $0.uniqueID == uniqueID }
            }
            .forEach { uniqueID in
                print("[Nearby Devices Scanner] - Lost device: \(uniqueID)")

                if let indexOfDeviceToRemove = nearbyDevices.firstIndex(where: { $0.uniqueID == uniqueID }) {
                    nearbyDevices.remove(at: indexOfDeviceToRemove)
                }
            }

        disappearCandidatePool = Set(nearbyDevices.subtracting(newDevices).compactMap(\.uniqueID))
        nearbyDevices.formUnion(newDevices)
        update(with: nearbyDevices)
    }

    @ScanningResultsActor
    private func update(with devices: Set<NearbyDevice>) {
        nearbyDevices = devices
        for device in devices where device.onTelemetryChange == nil {
            device.onTelemetryChange = { [weak self] in
                self?.privateTelemetryPublisher.send($0)
            }
        }
    }
}

// MARK: - KTKDevicesManagerDelegate
private final class KTKDevicesManagerDelegateProxy: NSObject, DevicesManagerDelegate {
    weak var delegate: NearbyDevicesScanner?

    func devicesManager(_ manager: DevicesManager, didDiscoverDevices devices: [NearbyDevice]) {
        print("Delivered devices by KTKDevicesManager: \(String(describing: devices.count))")

        if delegate?.devicesManager.centralState == .poweredOn && delegate?.bluetoothOff == true {
            delegate?.bluetoothOff = false
        }
        Task {
            await delegate?.processDiscoveredDevices(devices)
        }
    }

    func devicesManagerDidFail(toStartDiscovery manager: DevicesManager, withError error: Error) {
        print("[Nearby Devices Scanner] - Error: \(error.localizedDescription)")

        delegate?.nearbyDevicesPublisher.send(.failure(.scanningError(sdkError: error)))

        if delegate?.devicesManager.centralState != .poweredOn {
            delegate?.bluetoothOff = true
            delegate?.devicesManager.restartDeviceDiscovery { _ in }
        }
    }
}
