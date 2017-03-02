//
//  ViewController.swift
//  Kontakt Scanner
//
//  Created by Marek Serafin on 02/03/16.
//  Copyright © 2016 Marek Serafin. All rights reserved.
//

import Cocoa
import KontaktSDK

class ViewController: NSViewController {
    
    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var deviceUniqueID: NSTextField!    
    @IBOutlet weak var tableView: NSTableView!
    @IBOutlet weak var searchItem: NSToolbarItem!
    @IBOutlet weak var arrayController: NSArrayController!

    // =========================================================================
    // MARK: -
    
    var devicesManager: KTKDevicesManager!
    
    var devicesList: [KTKNearbyDevice] = []
    
    var selectedDevice: KTKNearbyDevice?
    
    var deviceConfiguration: [[String:Any]] = [[:]]
    
    var sortDescriptors = [
        NSSortDescriptor(key: "uniqueID", ascending: true),
        NSSortDescriptor(key: "name", ascending: true),
        NSSortDescriptor(key: "batteryLevel", ascending: true),
        NSSortDescriptor(key: "firmwareVersion", ascending: true),
        NSSortDescriptor(key: "RSSI", ascending: true),
    ]

    // =========================================================================
    // MARK: -
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Devices Manager
        devicesManager = KTKDevicesManager(delegate: self)
        devicesManager.startDevicesDiscovery(withInterval: 3.0)
    }
    
    override func viewWillAppear() {
        super.viewWillAppear()
        
        if let window = view.window {
            window.titleVisibility = .hidden

            if let toolbar = window.toolbar {
                toolbar.delegate = self
                toolbar.insertItem(withItemIdentifier: "search", at: toolbar.items.count)
            }
        }
    }
}

// =========================================================================
// MARK: - NSTableViewDelegate

extension ViewController: NSTableViewDelegate {
    
    func tableViewSelectionDidChange(_ notification: Notification) {
        if let nearbyDevice = arrayController.selectedObjects.first as? KTKNearbyDevice, nearbyDevice != selectedDevice {

            if let uniqueID = nearbyDevice.uniqueID {

                // Update Unique ID field
                self.deviceUniqueID.stringValue = uniqueID
                
                // Fetch Device from the Cloud API
                KTKCloudClient.sharedInstance().getObject(KTKDevice.self, primaryKey: uniqueID) { [weak self] response, error in
                    guard let strongSelf = self else { return }
                    
                    if let device = response?.objects?.first as? KTKDevice {
                    
                        strongSelf.willChangeValue(forKey: "deviceConfiguration")
                        strongSelf.deviceConfiguration = [
                            ["label": "Unique ID", "value": device.uniqueID],
                            ["label": "Proximity UUID", "value": device.configuration.proximityUUID!.uuidString],
                            ["label": "Major", "value": device.configuration.major!],
                            ["label": "Minor", "value": device.configuration.minor!],
                            ["label": "Interval", "value": device.configuration.advertisingInterval!],
                            ["label": "TX Power", "value": device.configuration.transmissionPower.rawValue],
                            ["label": "Namespace ID", "value": device.configuration.namespaceID!],
                            ["label": "Instance ID", "value": device.configuration.instanceID!]
                        ]
                        strongSelf.didChangeValue(forKey: "deviceConfiguration")
                    }
                }
            }
            
            selectedDevice = nearbyDevice
        }
    }
}

// =========================================================================
// MARK: - NSToolbarDelegate

extension ViewController: NSToolbarDelegate {
    
    func toolbar(_ toolbar: NSToolbar, itemForItemIdentifier itemIdentifier: String, willBeInsertedIntoToolbar flag: Bool) -> NSToolbarItem? {
        if itemIdentifier == "search" {
            return searchItem
        }
        return nil
    }
}

// =========================================================================
// MARK: - KTKDevicesManagerDelegate

extension ViewController: KTKDevicesManagerDelegate {

    func devicesManager(_ manager: KTKDevicesManager, didDiscover devices: [KTKNearbyDevice]?) {
        DispatchQueue.main.async {
            if let devices = devices {
                
                self.willChangeValue(forKey: "devicesList")
                self.devicesList = devices.map { ($0.copy() as! KTKNearbyDevice) }
                self.didChangeValue(forKey: "devicesList")
                
            }
        }
    }
}
