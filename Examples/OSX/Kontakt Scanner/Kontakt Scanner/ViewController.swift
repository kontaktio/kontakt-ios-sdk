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
    
    @IBOutlet weak var tableView: NSTableView!
    @IBOutlet weak var searchItem: NSToolbarItem!
    @IBOutlet weak var arrayController: NSArrayController!

    // =========================================================================
    // MARK: -
    
    var devicesManager: KTKDevicesManager!
    
    var devicesList: [KTKNearbyDevice] = []
    
    var selectedDevice: KTKNearbyDevice?

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
    
    override var representedObject: AnyObject? {
        didSet {
        // Update the view, if already loaded.
        }
    }
}

// =========================================================================
// MARK: - KTKDevicesManagerDelegate

extension ViewController: NSTableViewDelegate {
    
    func tableViewSelectionDidChange(notification: NSNotification) {
        if let nearbyDevice = arrayController.selectedObjects.first as? KTKNearbyDevice where nearbyDevice != selectedDevice {
            // Assign
            selectedDevice = nearbyDevice
            
            // Call Cloud
            if let uniqueID = selectedDevice?.uniqueID {
                KTKCloudClient.sharedInstance().getObject(KTKDevice.self, primaryKey: uniqueID) { response, error in
                    if let device = response?.objects?.first as? KTKDevice {
                        
                    }
                }
            }
        }
        else if arrayController.selectedObjects.count == 0 {
            
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
    
    func devicesManagerDidFailToStartDiscovery(manager: KTKDevicesManager, withError error: NSError?) {
        
    }
    
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
