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
    
    var eddystoneRegion: KTKEddystoneRegion?
    
    var beaconManager: KTKBeaconManager!
    
    var eddystoneManager: KTKEddystoneManager!
    
    // =========================================================================
    // MARK: - Initializer
    
    private override init() {
        super.init()
        
        self.beaconManager = KTKBeaconManager(delegate: self)
        self.eddystoneManager = KTKEddystoneManager(delegate: self)
    }
    
    // =========================================================================
    // MARK: - Scanning methods
    
    func resumeScanning() {
        let regionMonitored = UserDefaults.standard.bool(forKey: WakeUpRegionMonitoredKey)
        if regionMonitored {
            startScanning(forWakeUpRegion: restoreWakeUpRegion(), inEddystoneRegion: restoreEddystoneRegion())
        }
    }
    
    func startScanning(forWakeUpRegion region: KTKBeaconRegion?, inEddystoneRegion eddystoneRegion: KTKEddystoneRegion?) {
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
    
    func stopScanning(wakeUpRegion region: KTKBeaconRegion?) {
        if let region = region {
            beaconManager.stopMonitoring(for: region)
            eddystoneManager.stopEddystoneDiscoveryInAllRegions()
        }
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func restoreWakeUpRegion() -> KTKBeaconRegion? {
        // Get UUID and identifier from defaults
        let uuidString = UserDefaults.standard.string(forKey: WakeUpRegionProximityUuidKey)
        let identifier = UserDefaults.standard.string(forKey: WakeUpRegionIdentifierKey)
        
        // If not nil then create and return region, otherwise return nil
        if let uuidString = uuidString, let identifier = identifier {
            return KTKBeaconRegion(proximityUUID: UUID(uuidString: uuidString)!, identifier: identifier)
        }
        return nil
    }
    
    private func restoreEddystoneRegion() -> KTKEddystoneRegion? {
        // Get namespace and instance ID from defaults
        let namespaceID = UserDefaults.standard.string(forKey: EddystoneRegionNamespaceIdKey)
        let instanceID = UserDefaults.standard.string(forKey: EddystoneRegionInstanceIdKey)
        
        // If not nil then create and return region, otherwise return nil
        if let namespaceID = namespaceID {
            return KTKEddystoneRegion(namespaceID: namespaceID, instanceID: instanceID)
        }
        return nil
    }
}

// =========================================================================
// MARK: - KTKBeaconManagerDelegate

extension BeaconScanningManager: KTKBeaconManagerDelegate {
    
    func beaconManager(_ manager: KTKBeaconManager, monitoringDidFailFor region: KTKBeaconRegion?, withError error: Error?) {
        print("Monitoring did fail for region: \(region)")
        print("Error: \(error)")
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didStartMonitoringFor region: KTKBeaconRegion) {
        print("Did start monitoring for region: \(region)")
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didEnter region: KTKBeaconRegion) {
        print("Did enter region: \(region)")
        
        // Start eddystones scanning when wake-up region entered
        eddystoneManager.startEddystoneDiscovery(in: eddystoneRegion)
    }
    
    func beaconManager(_ manager: KTKBeaconManager, didExitRegion region: KTKBeaconRegion) {
        print("Did exit region \(region)")
    }
    
}

// =========================================================================
// MARK: - KTKEddystoneManagerDelegate

extension BeaconScanningManager: KTKEddystoneManagerDelegate {
    
    func eddystoneManagerDidFail(toStartDiscovery manager: KTKEddystoneManager, withError error: Error?) {
        print("Did fail to start discovery: \(error)")
    }
    
    func eddystoneManager(_ manager: KTKEddystoneManager, didDiscover eddystones: Set<KTKEddystone>, in region: KTKEddystoneRegion?) {
        print("Did discover \(eddystones.count) Eddystones")
    }
    
    func eddystoneManager(_ manager: KTKEddystoneManager, didUpdate eddystone: KTKEddystone, with frameType: KTKEddystoneFrameType) {
        sendEddystoneUpdatedNotification(updatedEddystone: eddystone)
    }
    
    private func sendEddystoneUpdatedNotification(updatedEddystone : KTKEddystone) {
        // Create notification
        let content = UNMutableNotificationContent()
        content.title = "Scan result"
        content.body = "Eddystone \(updatedEddystone.identifier) updated"
        content.sound = UNNotificationSound.default()
        content.categoryIdentifier = KontaktLocalNotificationCategoryID
        
        // Deliver the notification in five seconds.
        let trigger = UNTimeIntervalNotificationTrigger.init(timeInterval: 5.0, repeats: false)
        let request = UNNotificationRequest.init(identifier: "FiveSecond", content: content, trigger: trigger)
        
        // Schedule the notification
        UNUserNotificationCenter.current().add(request)
    }
}
