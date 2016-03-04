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
    
    var deviceConfiguration: [[String:AnyObject]] = [[:]]
    
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
        devicesManager.startDevicesDiscoveryWithInterval(3.0)
    }
    
    override func viewWillAppear() {
        super.viewWillAppear()
        
        if let window = view.window {
            window.titleVisibility = .Hidden

            if let toolbar = window.toolbar {
                toolbar.delegate = self
                toolbar.insertItemWithItemIdentifier("search", atIndex: toolbar.items.count)
            }
        }
    }
}

// =========================================================================
// MARK: - NSTableViewDelegate

extension ViewController: NSTableViewDelegate {
    
    func tableViewSelectionDidChange(notification: NSNotification) {
        if let nearbyDevice = arrayController.selectedObjects.first as? KTKNearbyDevice where nearbyDevice != selectedDevice {

            if let uniqueID = nearbyDevice.uniqueID {

                // Update Unique ID field
                self.deviceUniqueID.stringValue = uniqueID
                
                // Fetch Device from the Cloud API
                KTKCloudClient.sharedInstance().getObject(KTKDevice.self, primaryKey: uniqueID) { [weak self] response, error in
                    guard let strongSelf = self else { return }
                    
                    if let device = response?.objects?.first as? KTKDevice {
                    
                        strongSelf.willChangeValueForKey("deviceConfiguration")
                        strongSelf.deviceConfiguration = [
                            ["label": "Unique ID", "value": device.uniqueID],
                            ["label": "Proximity UUID", "value": device.configuration.proximityUUID!.UUIDString],
                            ["label": "Major", "value": device.configuration.major!],
                            ["label": "Minor", "value": device.configuration.minor!],
                            ["label": "Interval", "value": device.configuration.advertisingInterval!],
                            ["label": "TX Power", "value": device.configuration.transmissionPower.rawValue],
                            ["label": "Namespace ID", "value": device.configuration.namespaceID!],
                            ["label": "Instance ID", "value": device.configuration.instanceID!]
                        ]
                        strongSelf.didChangeValueForKey("deviceConfiguration")
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
    
    func toolbar(toolbar: NSToolbar, itemForItemIdentifier itemIdentifier: String, willBeInsertedIntoToolbar flag: Bool) -> NSToolbarItem? {
        if itemIdentifier == "search" {
            return searchItem
        }
        return nil
    }
}

// =========================================================================
// MARK: - KTKDevicesManagerDelegate

extension ViewController: KTKDevicesManagerDelegate {

    func devicesManager(manager: KTKDevicesManager, didDiscoverDevices devices: [KTKNearbyDevice]?) {
        dispatch_async(dispatch_get_main_queue()) {
            if let devices = devices {
                
                self.willChangeValueForKey("devicesList")
                self.devicesList = devices.map { ($0.copy() as! KTKNearbyDevice) }
                self.didChangeValueForKey("devicesList")
                
            }
        }
    }
}
