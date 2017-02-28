//
//  AppDelegate.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 12.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK
import UserNotifications

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        // Set your API key
        Kontakt.setAPIKey(<#T##key: String!##String!#>)
        
        // Register User Notifications
        UNUserNotificationCenter.current().requestAuthorization(options: [.alert, .sound, .badge]) {
            (granted, error) in
            // Parse errors and track state
        }
        
        // Check if app was launched by location event triggered by iBeacon
        if launchOptions?[UIApplicationLaunchOptionsKey.location] != nil {
            // Start scanning beacons if true
            BeaconScanningManager.sharedInstance.resumeScanning()
        }
        
        return true
    }
    
}

