//
//  InfiniteScanViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 20.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class InfiniteScanViewController: UIViewController {

    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var launchButton: LaunchButton!
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    // =========================================================================
    // MARK: - Vars
    
    var region: KTKBeaconRegion!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Create wake-up iBeacon Region
        // When this region will be entered, the scanning process will be started
        region = KTKBeaconRegion(proximityUUID: UUID(uuidString: KontaktProximityUUID)!, identifier: "region-identifier")
    }

    // =========================================================================
    // MARK: - Actions
    
    @IBAction func launchButtonClicked(_ sender: Any) {
        // Determine action based on button state
        switch (launchButton.currentState) {
        case .Start:
            // Specify your Eddystone region here - with nil param, all regions will be scanned
            BeaconScanningManager.sharedInstance.startScanning(forWakeUpRegion: region, inEddystoneRegion: nil)
            launchButton.currentState = .Stop
        case .Stop:
            BeaconScanningManager.sharedInstance.stopScanning()
            launchButton.currentState = .Start
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Infinite Scan"

        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
    }

}
