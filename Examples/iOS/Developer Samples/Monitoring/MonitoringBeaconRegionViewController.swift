//
//  MonitoringIBeaconsViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 12.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class MonitoringBeaconRegionViewController: UIViewController {

    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var launchButton: LaunchButton!
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    // =========================================================================
    // MARK: - Vars
    
    var beaconManager: BeaconManager!
    
    var region: BeaconRegion!
    
    static let regionIdentifier = "region-identifier"
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Beacon Manager
        beaconManager = BeaconManager(delegate: self)
        beaconManager.requestLocationAlwaysAuthorization()
        
        // Create Beacon Region
        if let region = beaconManager.monitoredRegions.filter ({ $0.identifier == MonitoringBeaconRegionViewController.regionIdentifier }).first {
            self.region = region
            self.launchButton.currentState = .Stop
        }
        else {
            region = BeaconRegion(proximityUUID: UUID(uuidString: KontaktProximityUUID)!, identifier: MonitoringBeaconRegionViewController.regionIdentifier)
            self.launchButton.currentState = .Start
        }
    }
    
    // =========================================================================
    // MARK: - Actions

    @IBAction func launchButtonClicked(_ sender: Any) {
        // Determine action based on button state
        switch (launchButton.currentState) {
        case .Start:
            beaconManager.startMonitoring(for: region)
            launchButton.currentState = .Stop
        case .Stop:
            beaconManager.stopMonitoring(for: region)
            launchButton.currentState = .Start
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Monitoring Regions"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
    }
}

// =========================================================================
// MARK: - KTKBeaconManagerDelegate (Monitoring)

extension MonitoringBeaconRegionViewController: BeaconManagerDelegate {
    
    func beaconManager(_ manager: BeaconManager, monitoringDidFailFor region: BeaconRegion?, withError error: Error?) {
        print("Monitoring did fail for region: \(String(describing: region))")
        print("Error: \(String(describing: error))")
    }
    
    func beaconManager(_ manager: BeaconManager, didStartMonitoringFor region: BeaconRegion) {
        print("Did start monitoring for region: \(region)")
    }
    
    func beaconManager(_ manager: BeaconManager, didEnter region: BeaconRegion) {
        print("Did enter region: \(region)")
    }
    
    func beaconManager(_ manager: BeaconManager, didExitRegion region: BeaconRegion) {
        print("Did exit region \(region)")
    }
    
}
