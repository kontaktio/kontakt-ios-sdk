//
//  BeaconScanningManager.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 19.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import Foundation
import KontaktSDK
import UserNotifications

class BeaconScanningManager: NSObject {
    
    // =========================================================================
    // MARK: - Shared instance
    
    static let sharedInstance = BeaconScanningManager()
    
    // =========================================================================
    // MARK: - Vars
    
    var eddystoneRegion: EddystoneRegion?

    var beaconManager: BeaconManager!
    
    var eddystoneManager: EddystoneManager!
    
    // =========================================================================
    // MARK: - Initializer
    
    private override init() {
        super.init()
        
        self.beaconManager = BeaconManager(delegate: self)
        self.eddystoneManager = EddystoneManager(delegate: self)
    }
    
    // =========================================================================
    // MARK: - Scanning methods
    
    func resumeScanning() {
        let regionMonitored = UserDefaults.standard.bool(forKey: WakeUpRegionMonitoredKey)
        if regionMonitored {
            startScanning(forWakeUpRegion: restoreWakeUpRegion(), inEddystoneRegion: restoreEddystoneRegion())
        }
    }
    
    func startScanning(forWakeUpRegion region: BeaconRegion?, inEddystoneRegion eddystoneRegion: EddystoneRegion?) {
        defer { UserDefaults.standard.synchronize() }
        if let region = region {
            // Start monitoring for wakeup iBeacon region
            beaconManager.requestLocationAlwaysAuthorization()
            beaconManager.startMonitoring(for: region)
            
            // Store wake-up region data in user defaults
            UserDefaults.standard.set(region.proximityUUID.uuidString, forKey: WakeUpRegionProximityUuidKey)
            UserDefaults.standard.set(region.identifier, forKey: WakeUpRegionIdentifierKey)
            
            // Set region monitored flag to true and store it
            UserDefaults.standard.set(true, forKey: WakeUpRegionMonitoredKey)
            
            // Check Eddystone region
            if let eddystoneRegion = eddystoneRegion {
                // Set region
                self.eddystoneRegion = eddystoneRegion
                
                // Store its data in user defaults
                UserDefaults.standard.set(eddystoneRegion.namespaceID, forKey: EddystoneRegionNamespaceIdKey)
                UserDefaults.standard.set(eddystoneRegion.instanceID, forKey: EddystoneRegionInstanceIdKey)
            }
        }
    }
    
    func stopScanning() {
        stopScanning(wakeUpRegion: restoreWakeUpRegion())
        
        // Set region monitored flag to false and store it
        UserDefaults.standard.set(false, forKey: WakeUpRegionMonitoredKey)
    }
    
    func stopScanning(wakeUpRegion region: BeaconRegion?) {
        if let region = region {
            beaconManager.stopMonitoring(for: region)
            eddystoneManager.stopEddystoneDiscoveryInAllRegions()
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func restoreWakeUpRegion() -> BeaconRegion? {
        // Get UUID and identifier from defaults
        let uuidString = UserDefaults.standard.string(forKey: WakeUpRegionProximityUuidKey)
        let identifier = UserDefaults.standard.string(forKey: WakeUpRegionIdentifierKey)
        
        // If not nil then create and return region, otherwise return nil
        if let uuidString = uuidString, let identifier = identifier {
            return BeaconRegion(proximityUUID: UUID(uuidString: uuidString)!, identifier: identifier)
        }
        return nil
    }
    
    private func restoreEddystoneRegion() -> EddystoneRegion? {
        // Get namespace and instance ID from defaults
        let namespaceID = UserDefaults.standard.string(forKey: EddystoneRegionNamespaceIdKey)
        let instanceID = UserDefaults.standard.string(forKey: EddystoneRegionInstanceIdKey)
        
        // If not nil then create and return region, otherwise return nil
        if let namespaceID = namespaceID {
            return EddystoneRegion(namespaceID: namespaceID, instanceID: instanceID)
        }
        return nil
    }
}

// =========================================================================
// MARK: - KTKBeaconManagerDelegate

extension BeaconScanningManager: BeaconManagerDelegate {
    
    func beaconManager(_ manager: BeaconManager, monitoringDidFailFor region: BeaconRegion?, withError error: Error?) {
        print("Monitoring did fail for region: \(String(describing: region))")
        print("Error: \(String(describing: error))")
    }
    
    func beaconManager(_ manager: BeaconManager, didStartMonitoringFor region: BeaconRegion) {
        print("Did start monitoring for region: \(region)")
    }
    
    func beaconManager(_ manager: BeaconManager, didEnter region: BeaconRegion) {
        print("Did enter region: \(region)")
        
        // Start eddystones scanning when wake-up region entered
        eddystoneManager.startEddystoneDiscovery(inRegion: eddystoneRegion)
    }
    
    func beaconManager(_ manager: BeaconManager, didExitRegion region: BeaconRegion) {
        print("Did exit region \(region)")
    }
    
}

// =========================================================================
// MARK: - KTKEddystoneManagerDelegate

extension BeaconScanningManager: EddystoneManagerDelegate {
    
    func eddystoneManagerDidFailToStartDiscovery(_ manager: EddystoneManager, withError error: Error?) {
        print("Did fail to start discovery: \(String(describing: error))")
    }
    
    func eddystoneManager(_ manager: EddystoneManager, didDiscoverEddystones eddystones: Set<Eddystone>, inRegion region: EddystoneRegion?) {
        print("Did discover \(eddystones.count) Eddystones")
    }
    
    func eddystoneManager(_ manager: EddystoneManager, didUpdate eddystone: Eddystone, with frameType: EddystoneFrameType) {
        sendEddystoneUpdatedNotification(updatedEddystone: eddystone)
    }
    
    private func sendEddystoneUpdatedNotification(updatedEddystone : Eddystone) {
        // Create notification
        let content = UNMutableNotificationContent()
        content.title = "Scan result"
        content.body = "Eddystone \(updatedEddystone.identifier?.uuidString ?? "") updated"
        content.sound = UNNotificationSound.default
        content.categoryIdentifier = KontaktLocalNotificationCategoryID
        
        // Deliver the notification in five seconds.
        let trigger = UNTimeIntervalNotificationTrigger.init(timeInterval: 5.0, repeats: false)
        let request = UNNotificationRequest.init(identifier: "FiveSecond", content: content, trigger: trigger)
        
        // Schedule the notification
        UNUserNotificationCenter.current().add(request)
    }
}
