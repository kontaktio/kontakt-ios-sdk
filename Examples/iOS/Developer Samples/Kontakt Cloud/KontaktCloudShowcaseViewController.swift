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
    
    var kontaktCloud: CloudClient!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        
        // Initialize Kontakt Cloud Client
        kontaktCloud = CloudClient()
    }

    // =========================================================================
    // MARK: - Actions
    
    @IBAction func fetchDevices(_ sender: Any) {
        // Fetch devices through Kontakt Cloud API client
        Task { [weak self] in
            do {
                let response = try await self?.kontaktCloud.getObjects(Device.self)
                if let devices = response?.objects as? [Device] {
                    self?.showAlert(
                        title: "Devices fetched",
                        message: "Fetched \(devices.count) device(s) from API"
                    )
                }

            } catch {
                self?.showAlert(
                    title: "Error while fetching devices",
                    message: KTKCloudErrorFromError(error as NSError)?.debugDescription ?? error.localizedDescription
                )
            }
        }
    }

    @IBAction func fetchConfigs(_ sender: Any) {
        // Fetch configs through Kontakt Cloud API client
        let parameters = ["deviceType": "beacon"]
        Task { [weak self] in
            do {
                let response = try await self?.kontaktCloud.getObjects(DeviceConfiguration.self, parameters: parameters)
                if let configs = response?.objects as? [DeviceConfiguration] {
                    self?.showAlert(
                        title: "Configs fetched",
                        message: "Fetched \(configs.count) config(s) from API"
                    )
                }

            } catch {
                self?.showAlert(
                    title: "Error while fetching configs",
                    message: KTKCloudErrorFromError(error as NSError)?.debugDescription ?? error.localizedDescription
                )
            }
        }
    }
 
    @IBAction func fetchManagers(_ sender: Any) {
        // Fetch managers through Kontakt Cloud API client
        Task { [weak self] in
            do {
                let response = try await self?.kontaktCloud.getObjects(Manager.self)
                if let managers = response?.objects as? [Manager] {
                    self?.showAlert(
                        title: "Managers fetched",
                        message: "Fetched \(managers.count) manager(s) from API"
                    )
                }

            } catch {
                self?.showAlert(
                    title: "Error while fetching managers",
                    message: KTKCloudErrorFromError(error as NSError)?.debugDescription ?? error.localizedDescription
                )
            }
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
