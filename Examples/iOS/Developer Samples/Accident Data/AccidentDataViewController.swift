//  Copyright © 2025 Kontakt.io

import UIKit
import SwiftUI
import KontaktSDK

// MARK: - UIKit View Controller
class AccidentDataViewController: UIViewController {

    private var hostingController: UIHostingController<AccidentDataView>!
    private var viewModel: AccidentDataViewModel!

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSwiftUIView()
    }

    private func setupSwiftUIView() {
        viewModel = AccidentDataViewModel()
        let accidentDataView = AccidentDataView(viewModel: viewModel)

        hostingController = UIHostingController(rootView: accidentDataView)
        hostingController.view.translatesAutoresizingMaskIntoConstraints = false

        addChild(hostingController)
        view.addSubview(hostingController.view)
        hostingController.didMove(toParent: self)

        NSLayoutConstraint.activate([
            hostingController.view.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            hostingController.view.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            hostingController.view.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            hostingController.view.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
    }
}

// MARK: - SwiftUI Accident Data View
struct AccidentDataView: View {
    @ObservedObject var viewModel: AccidentDataViewModel

    var body: some View {
        VStack(spacing: 20) {
            // Header
            VStack(spacing: 10) {
                Text("Accident Data Monitor")
                    .font(.title)
                    .fontWeight(.bold)

                Text("Detected beacon ID: \(viewModel.connectedBeaconID ?? "None")")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
                    .padding(.top)

                // Connection Status
                HStack {
                    Circle()
                        .fill(viewModel.status.color)
                        .frame(width: 12, height: 12)

                    Text(viewModel.status.label)
                        .font(.subheadline)
                        .foregroundColor(viewModel.status.color)
                }
            }
            .padding()

            Picker("Monitoring Mode", selection: $viewModel.monitoringMode) {
                Text("Proximity").tag(AccidentDataViewModel.MonitoringMode.proximity)
                Text("Accident").tag(AccidentDataViewModel.MonitoringMode.accident)
            }
            .pickerStyle(.segmented)

            VStack(spacing: 10) {
                Text("Accident data (telemetry)")
                    .font(.headline)
                    .padding(.horizontal)
                Divider()
                if let accidentEvent = viewModel.accidentEvent {
                    AccidentEventView(event: accidentEvent)
                } else {
                    Text("No accident data")
                        .foregroundColor(.secondary)
                        .padding()
                }

                Spacer()

                Text("Accelerometer samples")
                    .font(.headline)
                    .padding(.horizontal)
                Divider()

                ScrollView {
                    LazyVStack(spacing: 8) {
                        ForEach(viewModel.accelerometerData, id: \.self) { event in
                            HStack {
                                Text(event.dataString)
                                    .font(.body)
                                Divider()
                                Text(event.dateString)
                                    .font(.body)
                            }
                            .padding()
                            .background(Color.gray.opacity(0.1))
                            .cornerRadius(8)
                        }
                        if viewModel.accelerometerData.isEmpty {
                            Text("No accelerometer data")
                                .foregroundColor(.secondary)
                                .padding()
                        }
                    }
                }
            }

            VStack(spacing: 15) {
                if viewModel.status != .connected {
                    Text("Trigger iBeacon event to start reading data")
                        .multilineTextAlignment(.center)
                        .font(.headline)
                        .foregroundColor(.white)
                        .frame(maxWidth: .infinity)
                        .padding()
                        .background(Color.gray)
                        .cornerRadius(10)
                } else {
                    Button(action: {
                        viewModel.stopReadingData()
                    }) {
                        Text("Stop reading data")
                            .font(.headline)
                            .foregroundColor(.white)
                            .frame(maxWidth: .infinity)
                            .padding()
                            .background(Color.red)
                            .cornerRadius(10)
                    }
                }
            }
            .padding(.horizontal)
        }
        .padding()
        .onAppear {
            viewModel.nearbyDevicesScanner.startScanning(interval: 3)
        }
        .onDisappear {
            viewModel.nearbyDevicesScanner.stopScanning()
        }
    }
}

struct AccidentEventView: View {
    let event: AccidentFrame

    var body: some View {
        HStack {
            if event.accidentDetected {
                Image(systemName: "exclamationmark.circle.fill")
                    .foregroundColor(.red)
            } else if event.alertMode {
                Image(systemName: "exclamationmark.triangle.fill")
                    .foregroundColor(.orange)
            } else {
                Image(systemName: "info.circle.fill")
                    .foregroundColor(.blue)
            }

            Text(event.label)
                .font(.body)
                .lineLimit(2)

            Spacer()
        }
        .padding()
        .background(Color.gray.opacity(0.1))
        .cornerRadius(8)
    }
}

extension AccidentFrame {
    var label: String {
        "Detected: \(accidentDetected), Alert: \(alertMode)\nx: \(accelerationData.xg.f3), y: \(accelerationData.yg.f3), z: \(accelerationData.zg.f3)"
    }
}

extension AccelerationSample: @retroactive Identifiable {
    public var id: UUID {
        UUID()
    }

    var dateString: String {
        let date = Date(timeIntervalSince1970: timestamp)
        return Formatter.dateFormatter.string(from: date)
    }

    var dataString: String {
        "x: \(xg.f3) y: \(yg.f3) z: \(zg.f3)"
    }
}

extension Formatter {
    static let threeDigitsFormatter: NumberFormatter = {
        let formatter = NumberFormatter()
        formatter.minimumFractionDigits = 1
        formatter.maximumFractionDigits = 3
        formatter.roundingMode = .halfEven
        formatter.numberStyle = .decimal
        return formatter
    }()


    static let dateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "HH:mm:ss.SSS"
        formatter.timeZone = TimeZone.current
        return formatter
    }()
}

private extension FloatingPoint {
    var f3: String {
        Formatter.threeDigitsFormatter.string(for: self) ?? ""
    }
}

#Preview {
    AccidentDataView(viewModel: .init())
}
