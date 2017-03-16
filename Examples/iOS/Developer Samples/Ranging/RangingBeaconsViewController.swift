//
//  RangingIBeaconsViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 12.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class RangingBeaconsViewController: UIViewController {

    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var launchButton: LaunchButton!
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    // =========================================================================
    // MARK: - Vars
    
    var beaconManager: KTKBeaconManager!
    
    var region: KTKBeaconRegion!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Beacon Manager
        beaconManager = KTKBeaconManager(delegate: self)
        beaconManager.requestLocationAlwaysAuthorization()
        
        // Create Beacon Region
        region = KTKBeaconRegion(proximityUUID: UUID(uuidString: KontaktProximityUUID)!, identifier: "region-identifier")
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        if self.navigationController?.viewControllers.index(of: self) == nil {
            // Back button pressed because self is no longer in the navigation stack.
            // Stop ranging if needed
            beaconManager.stopRangingBeacons(in: region)
        }
        super.viewWillDisappear(animated)
    }
    
    // =========================================================================
    // MARK: - Actions

    @IBAction func launchButtonClicked(_ sender: Any) {
        // Determine action based on button state
        switch (launchButton.currentState) {
        case .Start:
            beaconManager.startRangingBeacons(in: region)
            launchButton.currentState = .Stop
        case .Stop:
            beaconManager.stopRangingBeacons(in: region)
            launchButton.currentState = .Start
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Ranging Beacons"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
    }
}

// =========================================================================
// MARK: - KTKBeaconManagerDelegate (Ranging)

extension RangingBeaconsViewController: KTKBeaconManagerDelegate {
    
    func beaconManager(_ manager: KTKBeaconManager, didRangeBeacons beacons: [CLBeacon], in region: KTKBeaconRegion) {
        print("Did ranged \"\(beacons.count)\" beacons")
    }
    
}
