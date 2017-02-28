//
//  NearbyDevicesScanningViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 14.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class NearbyDevicesScanningViewController: UIViewController {
    
    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var launchButton: LaunchButton!
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    // =========================================================================
    // MARK: - Vars
    
    var devicesManager: KTKDevicesManager!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Devices Manager
        devicesManager = KTKDevicesManager(delegate: self)
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        if self.navigationController?.viewControllers.index(of: self) == nil {
            // Back button pressed because self is no longer in the navigation stack.
            // Stop scanning if needed
            devicesManager.stopDevicesDiscovery()
        }
        super.viewWillDisappear(animated)
    }
    
    // =========================================================================
    // MARK: - Actions
    
    @IBAction func launchButtonClicked(_ sender: Any) {
        // Determine action based on button state
        switch (launchButton.currentState) {
        case .Start:
            devicesManager.startDevicesDiscovery(withInterval: 2.0)
            launchButton.currentState = .Stop
        case .Stop:
            devicesManager.stopDevicesDiscovery()
            launchButton.currentState = .Start
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Nearby Scanning"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
    }
}

// =========================================================================
// MARK: - KTKDevicesManagerDelegate

extension NearbyDevicesScanningViewController: KTKDevicesManagerDelegate {
    
    func devicesManager(_ manager: KTKDevicesManager, didDiscover devices: [KTKNearbyDevice]?) {
        guard let nearbyDevices = devices else {
            return
        }
        
        for device in nearbyDevices {
            if let uniqueID = device.uniqueID {
                print("Detected a beacon \(uniqueID)")
            } else {
                print("Detected a beacon with an unknown unique ID")
            }
        }
    }
    
    func devicesManagerDidFail(toStartDiscovery manager: KTKDevicesManager, withError error: Error?) {
        print("Discovery did fail with error: \(error)")
    }
    
}
