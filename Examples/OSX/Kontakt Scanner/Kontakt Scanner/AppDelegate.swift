//
//  AppDelegate.swift
//  Kontakt Scanner
//
//  Created by Marek Serafin on 02/03/16.
//  Copyright © 2016 Marek Serafin. All rights reserved.
//

import Cocoa
import KontaktSDK

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    func applicationDidFinishLaunching(aNotification: NSNotification) {
        // Insert code here to initialize your application
        
        // Set Kontakt.io API Key
        Kontakt.setAPIKey("<#API Key#>")
    }

    func applicationWillTerminate(aNotification: NSNotification) {
        // Insert code here to tear down your application
    }


}

