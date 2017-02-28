//
//  ApplyDeviceConfigViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 24.01.2017.
//  Copyright © 2017 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class ApplyDeviceConfigViewController: UITableViewController {

    // =========================================================================
    // MARK: - Constants
    
    let DEVICE_NOT_FOUND_TIMEOUT: TimeInterval! = TimeInterval(7.0)
    
    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    @IBOutlet weak var uniqueIdField: UITextField!
    
    @IBOutlet weak var majorField: UITextField!
    
    @IBOutlet weak var minorField: UITextField!
    
    @IBOutlet weak var infoLabel: UILabel!
    
    @IBOutlet weak var applyConfigButton: BorderedButton!
    
    // =========================================================================
    // MARK: - Vars
    
    var devicesManager: KTKDevicesManager!
    
    var configuration: KTKDeviceConfiguration!
    
    var timer: Timer!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Devices Manager
        devicesManager = KTKDevicesManager(delegate: self)
    }
    
    // =========================================================================
    // MARK: - Actions
    
    @IBAction func applyConfig(_ sender: Any) {
        if validInput() {
            // Start scanning for device
            showInfo(info: "Looking for device ...")
            devicesManager.startDevicesDiscovery(withInterval: 2.0)
            
            // Schedule timer - perform actions when device not found
            timer = Timer.scheduledTimer(timeInterval: DEVICE_NOT_FOUND_TIMEOUT,
                                         target: self,
                                         selector: #selector(onDeviceNotFound),
                                         userInfo: nil,
                                         repeats: false);
            
            // Disable button while applying config
            applyConfigButton.isEnabled = false
        }
    }
    
    func onDeviceNotFound() {
        devicesManager.stopDevicesDiscovery()
        showError(error: "Device not found")
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Setup nav bar
        navigationItem.title = "Apply Config"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
        
        // Setup fields
        uniqueIdField.textColor = UIColor.kontaktMediumGray
        
        majorField.textColor = UIColor.kontaktMediumGray
        majorField.keyboardType = UIKeyboardType.numberPad
        
        minorField.textColor = UIColor.kontaktMediumGray
        minorField.keyboardType = UIKeyboardType.numberPad
        
        // Setup button
        applyConfigButton.backgroundColor = UIColor.kontaktMainDarkBlue
        applyConfigButton.layer.borderColor = UIColor.kontaktMainDarkBlue.cgColor
        applyConfigButton.tintColor = UIColor.white
    }
    
    private func validInput() -> Bool {
        // Validate if fields are not empty
        if majorField.text == "" || minorField.text == "" || uniqueIdField.text == "" {
            showError(error: "Fields not filled")
            return false
        }
        
        // Validate unique ID length
        let uniqueID = uniqueIdField.text!
        if uniqueID.characters.count == 4 {
            configuration = KTKDeviceConfiguration(uniqueID: uniqueID)
        } else {
            showError(error: "Unique ID must be 4-char length")
            return false
        }
        
        // Validate major value
        if let major = UInt16(majorField.text!) {
            configuration.major = major as NSNumber?
        } else {
            showError(error: "Wrong major value")
            return false
        }
        
        // Validate minor value
        if let minor = UInt16(minorField.text!) {
            configuration.minor = minor as NSNumber?
        } else {
            showError(error: "Wrong minor value")
            return false
        }
        
        return true
    }
    
    // =========================================================================
    // MARK: - Helper Methods
    
    func showInfo(info: String!) {
        infoLabel.text = info
        infoLabel.textColor = UIColor.kontaktMediumGray
    }
    
    func showError(error: String!) {
        infoLabel.text = error
        infoLabel.textColor = UIColor.kontaktRed
        applyConfigButton.isEnabled = true
    }
    
    func showSuccessInfo(info: String!) {
        infoLabel.text = info
        infoLabel.textColor = UIColor.kontaktMainGreen
        applyConfigButton.isEnabled = true
    }
    
}

// =========================================================================
// MARK: - KTKDevicesManagerDelegate

extension ApplyDeviceConfigViewController: KTKDevicesManagerDelegate {
    
    func devicesManager(_ manager: KTKDevicesManager, didDiscover devices: [KTKNearbyDevice]?) {
        guard let nearbyDevices = devices else {
            return
        }
        
        // Filter for desired device
        if let device = nearbyDevices.filter({$0.uniqueID == configuration.uniqueID}).first {
            // Device found - stop discovery
            devicesManager.stopDevicesDiscovery()
            
            // Invalidate timer
            timer.invalidate()
            
            // Try to connect with device
            let connection: KTKDeviceConnection? = KTKDeviceConnection(nearbyDevice: device)
            
            // Check if connected
            if let connection = connection {
                showInfo(info: "Applying configuration ...")
                
                // Write config if connected to device
                connection.write(configuration) { synchronized, appliedConfiguration, error in
                    // Check if config applied successfully
                    if let _ = error {
                        self.showError(error: "Error while applying configuration")
                    } else {
                        self.showSuccessInfo(info: "Configuration applied")
                    }
                }
            }
        }
    }
    
    func devicesManagerDidFail(toStartDiscovery manager: KTKDevicesManager, withError error: Error?) {
        print("Discovery did fail with error: \(error)")
        self.showError(error: "Device discovery did fail")
    }
    
}
