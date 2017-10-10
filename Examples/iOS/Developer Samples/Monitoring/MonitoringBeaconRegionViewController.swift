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
    
    var beaconManager: KTKBeaconManager!
    
    var region: KTKBeaconRegion!
    
    static let regionIdentifier = "region-identifier"
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Beacon Manager
        beaconManager = KTKBeaconManager(delegate: self)
        beaconManager.requestLocationAlwaysAuthorization()
        
        // Create Beacon Region
        if let region = beaconManager.monitoredRegions.filter ({ $0.identifier == MonitoringBeaconRegionViewController.regionIdentifier }).first {
            self.region = region
            self.launchButton.currentState = .Stop
        }
        else {
            region = KTKBeaconRegion(proximityUUID: UUID(uuidString: KontaktProximityUUID)!, identifier: MonitoringBeaconRegionViewController.regionIdentifier)
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

extension MonitoringBeaconRegionViewController: KTKBeaconManagerDelegate {
    
    func beaconManager(_ manager: KTKBeaconManager, monitoringDidFailFor region: KTKBeaconRegion?, withError error: Error?) {
        print("Monitoring did fail for region: \(String(describing: region))")
        print("Error: \(String(describing: error))")
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didStartMonitoringFor region: KTKBeaconRegion) {
        print("Did start monitoring for region: \(region)")
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didEnter region: KTKBeaconRegion) {
        print("Did enter region: \(region)")
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didExitRegion region: KTKBeaconRegion) {
        print("Did exit region \(region)")
    }
    
}
