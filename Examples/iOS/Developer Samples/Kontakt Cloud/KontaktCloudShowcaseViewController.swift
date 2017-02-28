//
//  KontaktCloudShowcaseViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 16.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK

class KontaktCloudShowcaseViewController: UIViewController {
    
    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    @IBOutlet weak var fetchDevicesButton: BorderedButton!

    @IBOutlet weak var fetchConfigsButton: BorderedButton!
    
    @IBOutlet weak var fetchManagersButton: BorderedButton!
    
    // =========================================================================
    // MARK: - Vars
    
    var kontaktCloud: KTKCloudClient!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Kontakt Cloud Client
        kontaktCloud = KTKCloudClient()
    }

    // =========================================================================
    // MARK: - Actions
    
    @IBAction func fetchDevices(_ sender: Any) {
        // Fetch devices through Kontakt Cloud API client
        kontaktCloud.getObjects(KTKDevice.self) {
            response, error in
            // Title and message for alert
            var title = "", message = ""
            
            // Check response
            if let ktkError = KTKCloudErrorFromError(error) {
                title = "Error while fetching devices"
                message = ktkError.debugDescription
            } else if let devices = response?.objects as? [KTKDevice] {
                title = "Devices fetched"
                message = "Fetched \(devices.count) device(s) from API"
            }
            
            // Show alert to inform user about request result
            self.showAlert(title: title, message: message)
        }
    }

    @IBAction func fetchConfigs(_ sender: Any) {
        // Fetch configs through Kontakt Cloud API client
        let parameters = ["deviceType": "beacon"]
        kontaktCloud.getObjects(KTKDeviceConfiguration.self, parameters: parameters) {
            response, error in
            // Title and message for alert
            var title = "", message = ""
            
            // Check response
            if let ktkError = KTKCloudErrorFromError(error) {
                title = "Error while fetching configs"
                message = ktkError.debugDescription
            } else if let configs = response?.objects as? [KTKDeviceConfiguration] {
                title = "Configs fetched"
                message = "Fetched \(configs.count) config(s) from API"
            }
            
            // Show alert to inform user about request result
            self.showAlert(title: title, message: message)
        }
    }
 
    @IBAction func fetchManagers(_ sender: Any) {
        // Fetch managers through Kontakt Cloud API client
        kontaktCloud.getObjects(KTKManager.self) {
            response, error in
            // Title and message for alert
            var title = "", message = ""
            
            // Check response
            if let ktkError = KTKCloudErrorFromError(error) {
                title = "Error while fetching managers"
                message = ktkError.debugDescription
            } else if let managers = response?.objects as? [KTKManager] {
                title = "Managers fetched"
                message = "Fetched \(managers.count) manager(s) from API"
            }
            
            // Show alert to inform user about request result
            self.showAlert(title: title, message: message)
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Kontakt Cloud"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
        
        // Setup buttons
        fetchDevicesButton.backgroundColor = UIColor.kontaktMainDarkBlue
        fetchDevicesButton.layer.borderColor = UIColor.kontaktMainDarkBlue.cgColor
        fetchDevicesButton.tintColor = UIColor.white
        
        fetchConfigsButton.backgroundColor = UIColor.kontaktMainDarkBlue
        fetchConfigsButton.layer.borderColor = UIColor.kontaktMainDarkBlue.cgColor
        fetchConfigsButton.tintColor = UIColor.white
        
        fetchManagersButton.backgroundColor = UIColor.kontaktMainDarkBlue
        fetchManagersButton.layer.borderColor = UIColor.kontaktMainDarkBlue.cgColor
        fetchManagersButton.tintColor = UIColor.white
    }
    
    private func showAlert(title: String, message: String) {
        if title.isEmpty || message.isEmpty {
            return
        }
        
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
}
