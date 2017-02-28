//
//  ScanningEddystonesViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 12.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit
import KontaktSDK
import UserNotifications

class ScanningEddystonesViewController: UIViewController {

    // =========================================================================
    // MARK: - Outlets
    
    @IBOutlet weak var launchButton: LaunchButton!
    
    @IBOutlet weak var descriptionLabel: UILabel!
    
    // =========================================================================
    // MARK: - Vars
    
    var eddystoneManager: KTKEddystoneManager!
    
    var region: KTKEddystoneRegion!
    
    var backgroundMode: Bool!
    
    var trackingUrl: String!
    
    var notificationAlreadySent: Bool!
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Setup views
        setupView()
        
        // Add working mode observers
        observeOnAppWorkingModes()
        
        // Initialize Eddystone Manager
        eddystoneManager = KTKEddystoneManager(delegate: self)
        
        // Create Eddystone Region
        region = KTKEddystoneRegion(namespaceID: KontaktEddystoneNamespaceID)
        
        // Set URL value - if any Eddystone beacon will broadcast URL with the same value, 
        // the notification will be shown (only in case when app is in background mode)
        trackingUrl = "http://kontakt.io"
        
        // Initial states for bool flags
        notificationAlreadySent = false
        backgroundMode = false
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        if self.navigationController?.viewControllers.index(of: self) == nil {
            // Back button pressed because self is no longer in the navigation stack.
            // Stop scanning if needed
            eddystoneManager.stopEddystoneDiscovery(in: region)
            notificationAlreadySent = false
            
        }
        super.viewWillDisappear(animated)
    }
    
    // =========================================================================
    // MARK: - Actions
    
    @IBAction func launchButtonClicked(_ sender: Any) {
        // Determine action based on button state
        switch (launchButton.currentState) {
        case .Start:
            eddystoneManager.startEddystoneDiscovery(in: region)
            launchButton.currentState = .Stop
        case .Stop:
            eddystoneManager.stopEddystoneDiscovery(in: region)
            launchButton.currentState = .Start
            
            // Set flag to false to show notification again when app enters background mode
            notificationAlreadySent = false
        }
    }
    
    // =========================================================================
    // MARK: - Helper methods
    
    func sendEddystoneUrlNotification(url: String!) {
        // Create notification
        let content = UNMutableNotificationContent()
        content.title = "Eddystone URL discovered"
        content.body = url
        content.sound = UNNotificationSound.default()
        content.categoryIdentifier = KontaktLocalNotificationCategoryID
        
        // Deliver the notification in five seconds.
        let trigger = UNTimeIntervalNotificationTrigger.init(timeInterval: 5.0, repeats: false)
        let request = UNNotificationRequest.init(identifier: "FiveSecond", content: content, trigger: trigger)
        
        // Schedule the notification
        UNUserNotificationCenter.current().delegate = self
        UNUserNotificationCenter.current().add(request)
    }
    
    // =========================================================================
    // MARK: - Private
    
    private func setupView() {
        // Title
        navigationItem.title = "Scanning Eddystones"
        
        // Setup description label
        descriptionLabel.textColor = UIColor.kontaktMediumGray
    }
    
    private func observeOnAppWorkingModes() {
        // Observe on entering background mode
        NotificationCenter.default.addObserver(forName: NSNotification.Name.UIApplicationDidEnterBackground, object: nil, queue:nil) {
            notification in
            // App enter foreground mode - set background mode flag to true
            self.backgroundMode = true
        }
        
        // Observe on entering foreground mode
        NotificationCenter.default.addObserver(forName: NSNotification.Name.UIApplicationWillEnterForeground, object: nil, queue:nil) {
            notification in
            // App enter foreground mode - set background mode flag to false
            self.backgroundMode = false
        }
    }
    
}

// =========================================================================
// MARK: - KTKEddystoneManagerDelegate

extension ScanningEddystonesViewController: KTKEddystoneManagerDelegate {
    
    func eddystoneManagerDidFail(toStartDiscovery manager: KTKEddystoneManager, withError error: Error?) {
        print("Did fail to start discovery: \(error)")
    }
    
    func eddystoneManager(_ manager: KTKEddystoneManager, didDiscover eddystones: Set<KTKEddystone>, in region: KTKEddystoneRegion?) {
        print("Did discover \(eddystones.count) Eddystones")
        
        // Check Eddystone URLs
        for eddystone in eddystones {
            if let eddystoneUrl = eddystone.eddystoneURL?.url {
                // Check if eddystone URL is the same as your tracking URL
                // If true and app is in background mode then show notification to user
                // Check also if notification wasn't sent already
                if trackingUrl == eddystoneUrl.absoluteString && backgroundMode && !notificationAlreadySent {
                    // Send notification
                    sendEddystoneUrlNotification(url: trackingUrl)
                    
                    // Set flag to true to stop the spam in background mode
                    notificationAlreadySent = true
                }
                
                // Print URL in logs
                print("Eddystone URL: \(eddystoneUrl)")
            }
        }
    }
    
    func eddystoneManager(_ manager: KTKEddystoneManager, didUpdate eddystone: KTKEddystone, with frameType: KTKEddystoneFrameType) {
        // Uncomment this if you want to react on Eddystone updates
        // print("Did update Eddystone: \(eddystone)")
    }
    
}

// =========================================================================
// MARK: - UNUserNotificationCenterDelegate

extension ScanningEddystonesViewController: UNUserNotificationCenterDelegate {
    
    func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
        let content = response.notification.request.content
        if content.categoryIdentifier == KontaktLocalNotificationCategoryID {
            let body = content.body
            
            if let url = URL(string: body) {
                UIApplication.shared.open(url, options: [:], completionHandler: nil)
            }
        }
        completionHandler()
    }
    
}
