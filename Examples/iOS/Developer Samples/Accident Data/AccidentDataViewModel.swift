//  Copyright © 2025 kontakt.io

import Foundation
import CoreLocation
import Combine
import SwiftUI
import KontaktSDK

final class AccidentDataViewModel: NSObject, ObservableObject {
    enum ConnectionState: Equatable {
        case disconnected
        case processing
        case searching
        case connecting
        case connected
        case error(String)

        var label: String {
            switch self {
            case .disconnected: "Disconnected"
            case .searching: "Searching..."
            case .processing: "Processing..."
            case .connecting: "Connecting..."
            case .connected: "Connected"
            case let .error(message): "Error: \(message)"
            }
        }

        var color: Color {
            switch self {
            case .disconnected: .red
            case .processing: .yellow
            case .searching: .yellow
            case .connecting: .blue
            case .connected: .green
            case .error: .red
            }
        }
    }

    enum MonitoringMode: Equatable {
        case proximity
        case accident
    }

    @Published var status = ConnectionState.disconnected {
        didSet {
            if status == .disconnected {
                connectedBeaconID = nil
            }
        }
    }
    @Published var connectedBeaconID: String?
    @Published var accidentEvent: AccidentFrame?
    @Published var monitoringMode = MonitoringMode.accident {
        didSet {
            self.setupMonitoring(for: monitoringMode)
        }
    }
    @Published var accelerometerData: [AccelerationSample] = []

    var beaconManager: KTKBeaconManager!
    let nearbyDevicesScanner = NearbyDevicesScanner()
    let proximityUUID = UUID(uuidString: "F7826DA6-4FA2-4E98-8024-BC5B71E0893E")!
    let accidentUUID = UUID(uuidString: "57797061-6465-6B41-6C65-7274505A5521")!

    private var deviceConnection: KTKDeviceConnection?
    private var nearbyDevice: KTKNearbyDevice?
    private var rangedBeacons: [BeaconID: BeaconEvent] = [:]

    override init() {
        super.init()
        beaconManager = KTKBeaconManager(delegate: self)
        beaconManager.requestLocationAlwaysAuthorization()
    }

    func setupMonitoring(for mode: MonitoringMode) {
        beaconManager.stopMonitoringForAllRegions()
        beaconManager.stopRangingBeaconsInAllRegions()

        let region = switch mode {
        case .proximity:
            KTKBeaconRegion(proximityUUID: proximityUUID, identifier: "proximity-region")
        case .accident:
            KTKBeaconRegion(proximityUUID: accidentUUID, identifier: "accident-region")
        }
        beaconManager.startMonitoring(for: region)
    }

    private func connectToBeacon(_ nearbyDevice: KTKNearbyDevice) {
        guard let uniqueId = nearbyDevice.uniqueID else {
            print("Cannot connect: device has no unique ID")
            return
        }

        status = .connecting
        print("Connecting to beacon with unique ID: \(uniqueId)")

        // Create device connection
        deviceConnection = KTKDeviceConnection(nearbyDevice: nearbyDevice)
        deviceConnection?.delegate = self

        readAccelerometerData()
    }

    private func setupTelemetry(_ nearbyDevice: KTKNearbyDevice) {
        nearbyDevice.onTelemetryChange = { telemetry in
            DispatchQueue.main.async { [weak self] in
                self?.accidentEvent = telemetry.accidentData
            }
        }
    }

    private func readAccelerometerData() {
        guard let deviceConnection else {
            print("Cannot read data: not connected to the beacon")
            status = .disconnected
            return
        }

        print("Reading accelerometer data from the beacon...")
        accelerometerData = []

        deviceConnection.readAccelerometerData { [weak self] samples, error in
            DispatchQueue.main.async {
                if let error = error {
                    self?.status = .error("BLE Error: \(error)")
                    print("Error reading accelerometer data: \(error)")
                    return
                }

                self?.accelerometerData = samples ?? []
            }
        }
    }

    func stopReadingData() {
        status = .disconnected
        deviceConnection?.stopCurrentListeningOperation()
        deviceConnection = nil
        connectedBeaconID = nil
    }
}

// MARK: - KTKBeaconManagerDelegate
extension AccidentDataViewModel: KTKBeaconManagerDelegate {
    struct BeaconEvent: Hashable {
        let beacon: CLBeacon
        let uniqueId: String
    }

    struct BeaconID: Hashable {
        let major: Int
        let minor: Int
    }

    func beaconManager(_ manager: KTKBeaconManager, didEnter region: KTKBeaconRegion) {
        beaconManager.startRangingBeacons(in: region)
    }

    func beaconManager(_ manager: KTKBeaconManager, didExitRegion region: KTKBeaconRegion) {
        beaconManager.stopRangingBeaconsInAllRegions()
    }

    func beaconManager(_ manager: KTKBeaconManager, didRangeBeacons beacons: [CLBeacon], in region: KTKBeaconRegion) {
        guard region.proximityUUID == accidentUUID else {
            return
        }
        for beacon in beacons {
            var isCurrentlyActive = false
            if let previouslyRangedBeacon = rangedBeacons[beacon.beaconId],
               previouslyRangedBeacon.beacon.isActive {
                isCurrentlyActive = true
            }
            if !isCurrentlyActive {
                Task {
                    do {
                        try await process(beacon: beacon)
                    } catch {
                        print("Processing error: \(error.localizedDescription)")
                    }
                }
            }
        }
    }

    @MainActor
    private func process(beacon: CLBeacon) async throws {
        guard ![.connected, .searching, .connecting].contains(status) else {
            return
        }
        print("Processing beacon: \(beacon)")
        status = .processing

        if let uniqueId = try await getDeviceUniqueId(beaconId: beacon.beaconId) {
            rangedBeacons[beacon.beaconId] = .init(beacon: beacon, uniqueId: uniqueId)
            print("Beacon unique ID: \(uniqueId)")
            connectedBeaconID = uniqueId
            status = .searching

            Task {
                for _ in 1...10 {
                    if let nearbyDevice = nearbyDevicesScanner.nearbyDevice(uniqueId: uniqueId) {
                        setupTelemetry(nearbyDevice)
                        connectToBeacon(nearbyDevice)
                        return
                    }
                    try? await Task.sleep(nanoseconds: NSEC_PER_SEC)
                }
                print("Not found nearby")
                status = .disconnected
            }
        } else {
            print("Unknown Beacon: \(beacon.major)/\(beacon.minor)")
            status = .disconnected
        }
    }

    private func getDeviceUniqueId(beaconId: BeaconID) async throws -> String? {
        let query = "major==\(beaconId.major)&minor==\(beaconId.minor)"
        let response = try await KTKCloudClient.sharedInstance().get("device", parameters: ["q": query, "selector": "uniqueId"])

        let device = response.objects?.first as? KTKDevice
        return device?.uniqueID
    }
}

// MARK: - KTKDeviceConnectionDelegate
extension AccidentDataViewModel: KTKDeviceConnectionDelegate {
    func deviceConnectionDidConnect(_ connection: KTKDeviceConnection) {
        print("Device connection established")
        status = .connected
    }

    func deviceConnection(_ connection: KTKDeviceConnection, didFailToConnect error: Error) {
        print("Device connection failed: \(error)")
        DispatchQueue.main.async {
            self.status = .disconnected
            self.connectedBeaconID = nil
        }
    }

    func deviceConnectionDidDisconnect(_ connection: KTKDeviceConnection) {
        print("Device connection disconnected")
        DispatchQueue.main.async {
            self.status = .disconnected
            self.connectedBeaconID = nil
            self.accelerometerData = []
        }
    }
}

extension CLBeacon {
    var beaconId: AccidentDataViewModel.BeaconID {
        .init(major: major.intValue, minor: minor.intValue)
    }

    var isActive: Bool {
        timestamp.addingTimeInterval(30) >= .now
    }
}
