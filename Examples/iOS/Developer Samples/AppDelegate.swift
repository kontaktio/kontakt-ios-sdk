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

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Set your API key - Replace with your actual API key from https://panel.kontakt.io
        Kontakt.setAPIKey("Your API Key")

        // Register User Notifications
        UNUserNotificationCenter.current().requestAuthorization(options: [.alert, .sound, .badge]) { granted, error in
            if let error = error {
                print("Notification permission error: \(error.localizedDescription)")
            } else {
                print("Notification permission granted: \(granted)")
            }
        }
        
        // Check if app was launched by location event triggered by iBeacon
        if launchOptions?[UIApplication.LaunchOptionsKey.location] != nil {
            // Start scanning beacons if true
            BeaconScanningManager.sharedInstance.resumeScanning()
        }
        
        return true
    }
    
}

