//
//  SamplesTableViewController.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 12.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit

class SamplesTableViewController: UITableViewController {

    // =========================================================================
    // MARK: - Vars
    
    var samples:[(number: Int, name: String, storyboardID: String)] = []
    
    let sampleNameCellIdentifier = "SampleNameCell";
    
    // =========================================================================
    // MARK: - UIViewController
    
    override func viewDidLoad() {
        // Super
        super.viewDidLoad()
        
        // Set Title
        self.navigationItem.title = "Samples"
        
        // Initialize Samples
        samples += [(number: 0, name: "Ranging Beacons",            storyboardID: "RangingBeacons")]
        samples += [(number: 1, name: "Scanning Eddystones",        storyboardID: "ScanningEddystones")]
        samples += [(number: 2, name: "Monitoring Regions",         storyboardID: "MonitoringBeaconRegion")]
        samples += [(number: 3, name: "Nearby Scanning",            storyboardID: "NearbyDevicesScanning")]
        samples += [(number: 4, name: "Kontakt Cloud",              storyboardID: "KontaktCloudShowcase")]
        samples += [(number: 5, name: "Apply Config",               storyboardID: "ApplyDeviceConfig")]
        samples += [(number: 6, name: "Infinite Scan",              storyboardID: "InfiniteScan")]
    }

    // =========================================================================
    // MARK: - Table View Data Source

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return samples.count
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        // Set label for given cell
        let cell = tableView.dequeueReusableCell(withIdentifier: sampleNameCellIdentifier, for: indexPath)
        let row = indexPath.row
        cell.textLabel?.text = samples[row].name
        cell.textLabel?.textColor = UIColor.kontaktMainGray
        cell.accessoryType = .disclosureIndicator
        
        return cell
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        // Get row
        let row = indexPath.row
        
        // Create storyboard
        let storyboardID = samples[row].storyboardID;
        let storyboard = UIStoryboard(name: storyboardID, bundle: nil)
        let controller = storyboard.instantiateInitialViewController()!
        
        // Show storyboard with View Controller
        self.navigationController?.pushViewController(controller, animated: true)
    }

}
