# iOS SDK Quickstart

## Important Note
Please make sure before updating to SDK `3.0.0` that you don't need to support devices with firmware **`< 4.0`**. 
As of version `3.0.0` only devices with firmware **`4.0`** or higher will be supported. 

## Administration App

To configure Kontakt.io Devices please use our new [iOS Administration App](https://itunes.apple.com/pl/app/kontakt.io-administration/id1067320511) or [iOS Kio Gateway Installer](https://apps.apple.com/gb/app/kio-gateway-installer/id1540964088).

![screen](https://kontakt-mobile.s3.amazonaws.com/stich.png?4)

## Sample Code
You can find our demos and sample code in [Examples folder](https://github.com/kontaktio/kontakt-ios-sdk/tree/master/Examples).

## Overview

This document shows you a quick way to start using the Kontakt.io SDK in location-aware apps. You will find code examples for core features and best practices that we recommend developers follow.

You can find more detailed information in the [Appledocs](http://developer.kontakt.io/ios-sdk/appledocs/).

## Installing the iOS SDK

To use the Kontakt.io SDK in your project, the minimum deployment target must be iOS 9.0.

### CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Cocoa projects. You can install it with the following command:

``` bash
$ gem install cocoapods
```

To integrate the Kontakt.io iOS SDK into your Xcode project using CocoaPods, specify it in your `Podfile`:

``` ruby
platform :ios, '9.0'
use_frameworks!

pod 'KontaktSDK', '~> 3.0'
```

Then, run the following command:

``` bash
$ pod install
```

---

### Manually

- Open up Terminal, `cd` into your top-level project directory, and run the following command *if* your project is not initialized as a git repository:

``` bash
$ git init
```

- Add Kontakt.io SDK as a git [submodule](http://git-scm.com/docs/git-submodule) by running the following command:

``` bash
$ git submodule add https://github.com/kontaktio/kontakt-ios-sdk.git
```

- Open the new `kontakt-ios-sdk` folder, and drag the `KontaktSDK.framework` into the Project Navigator of your application's Xcode project.

    * Make sure your target is checked in `Add to targets` section.

- Next, select your application project in the Project Navigator (blue project icon) to navigate to the target configuration window and select the application target under the "Targets" heading in the sidebar.
- In the tab bar at the top of that window, open the "General" panel.
- Click on the `+` button under the "Embedded Binaries" section.
    
- Select the `KontaktSDK.framework` and click `Add` button.

- In the Build Phases tab, click the + button at the top and select “New Run Script Phase”. Enter the following code into the script text field:

```bash
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/KontaktSDK.framework/strip-frameworks.sh"
```

(The last step, courtesy of [Realm](https://github.com/realm/realm-cocoa/), is required for working around an [iOS App Store bug](http://www.openradar.me/radar?id=6409498411401216) when archiving universal binaries.)

---

### Swift

#### Generics and Nullability

Our SDK uses nullability and generics annotations added in Xcode 13 which means that the Kontakt.io iOS SDK is very easy to use with swift.

#### Bridging Header
Create a new header file from the **File** menu and name it **<i>YourProjectName</i>-Bridging-Header.h**.

Add the following import to your **<i>YourProjectName</i>-Bridging-Header.h**:

``` Objective-C
    #import <KontaktSDK/KontaktSDK.h>
```


###Further information
> For your app to work correctly you have to add a new key to your project's plist file. 

1.  In the project navigator, select your project. 
2.  Select your projects **Info.plist** file 
3.  Add the following key string pair to the file.

``` Objective-C
<key>NSLocationAlwaysUsageDescription</key>
<string>Required for ios 8 compatibilty</string>
```

The string can be empty, the content is not important.

## First steps

New SDK requires API Key to be specified. You can get it by registering a free account at [https://panel.kontakt.io](http://panel.kontakt.io/signin).



**Objective-C**

``` Objective-C
#import <KontaktSDK/KontaktSDK.h>
```

``` Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

	// Set API Key
	[Kontakt setAPIKey:@"Your API Key"];
	
    return YES;
}
```

**Swift**

``` Swift
import KontaktSDK
```

``` Swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
	
	// Set API Key
	Kontakt.setAPIKey("Your API Key")
	
	return true
}
```


## Interacting with Beacons - monitoring a region
In the following example we'll show you how to can create a simple application to monitor beacons for a specific region using the Kontakt.io SDK.

---

### Basic Setup
In our example, we have used the **AppDelegate.m** class for simplicity. You would probably want to create your own class in a real application. 

First we'll import the Kontakt.io SDK.

``` Objective-C
#import <KontaktSDK/KontaktSDK.h>
```

We'll add the [KTKBeaconManager](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKBeaconManager.html) object as a property. 

KTKBeaconManager informs its delegates when a device enters or exits a region, and when beacons are ranged.

``` Objective-C
@property KTKBeaconManager *beaconManager;
```

---

Make sure `AppDelegate` conforms to `KTKBeaconManagerDelegate` protocol.

``` Objective-C
@interface AppDelegate () <KTKBeaconManagerDelegate>
```

---

We will use `application:didFinishLaunchingWithOptions:` to initiate beacon manager and start monitoring for region.

``` Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

	// Set API Key
	[Kontakt setAPIKey:@"Your API Key"];
	
	// Initiate Beacon Manager
	self.beaconManager = [[KTKBeaconManager alloc] initWithDelegate:self];
	
	// Request Location Authorization
	[self.beaconManager requestLocationAlwaysAuthorization];
	
	...
	
    return YES;
}
```

---

You can test if the current device is capable of monitoring beacons using:

``` Objective-C
if ([KTKBeaconManager isMonitoringAvailable]) {
	
}
```

or check authorization status using:

``` Objective-C
if ([KTKBeaconManager locationAuthorizationStatus] == kCLAuthorizationStatusAuthorizedAlways) {
	
}
```

### Beacon Region

Now we'll start monitoring a specific region.

For more information on [KTKBeaconRegion](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKBeaconRegion.html) see Appledoc.

> Regions define a set of beacons that your application is aware of, so the beacon manager will interact only with those beacons.

``` Objective-C
// Kontakt.io proximity UUID
NSUUID *proximityUUID = [[NSUUID alloc] initWithUUIDString:@"f7826da6-4fa2-4e98-8024-bc5b71e0893e"]; 

// Create region instance
KTKBeaconRegion *region = [[KTKBeaconRegion alloc] initWithProximityUUID: proximityUUID identifier:@"identifier"];

// Start Monitoring
[self.beaconManager startMonitoringForRegion: region];

// You can also start ranging ...
[self.beaconManager startRangingBeaconsInRegion: region];
```

### Secure Beacon Region

Secure beacon region is very similar to standard beacon region.
For more information on [KTKSecureBeaconRegion](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKSecureBeaconRegion.html) see Appledoc.

Read more about security and shuffling on our [support page](https://support.kontakt.io/hc/en-gb/sections/201612029).

> You can find your beacon's Secure Proximity UUID in Kontakt.io Web Panel (in the Security Section).

``` Objective-C
// Your secure proximity UUID
NSUUID *secureProximityUUID = [[NSUUID alloc] initWithUUIDString:@"00000000-0000-0000-0000-00000000"]; 

// Create secure region instance
KTKSecureBeaconRegion *region = [[KTKSecureBeaconRegion alloc] initWithSecureProximityUUID:secureProximityUUID identifier:@"identifier_secure"];
```

You can also use an unsecure proximity UUID and it will be translated to the secure proximity by calling Cloud API under the hood.

``` Objective-C
// Kontakt.io proximity UUID
NSUUID *proximityUUID = [[NSUUID alloc] initWithUUIDString:@"f7826da6-4fa2-4e98-8024-bc5b71e0893e"]; 

// Create secure region instance with your non secure proximity 
KTKSecureBeaconRegion *region = [[KTKSecureBeaconRegion alloc] initWithProximityUUID: proximityUUID identifier:@"identifier"];
```

### Delegate Calls

Now we'll add the the delegate methods for beaconManager, and get them to log some output.
All delegate methods can be found in [KTKBeaconManagerDelegate](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Protocols/KTKBeaconManagerDelegate.html) documentation.

``` Objective-C
- (void)beaconManager:(KTKBeaconManager*)manager didChangeLocationAuthorizationStatus:(CLAuthorizationStatus)status;
{
	// ...
}

- (void)beaconManager:(KTKBeaconManager*)manager didEnterRegion:(__kindof KTKBeaconRegion*)region
{
    NSLog(@"Enter region %@", region);
}

- (void)beaconManager:(KTKBeaconManager*)manager didExitRegion:(__kindof KTKBeaconRegion*)region
{
    NSLog(@"Exit region %@", region);
}

- (void)beaconManager:(KTKBeaconManager*)manager didRangeBeacons:(NSArray <CLBeacon *>*)beacons inRegion:(__kindof KTKBeaconRegion*)region
{
    NSLog(@"Ranged beacons count: %lu", [beacons count]);
}
```

---

When using **Swift** the final class should look like the following:

``` Swift
import UIKit
import KontaktSDK

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    
    var beaconManager: KTKBeaconManager!
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        // Set API Key
        Kontakt.setAPIKey("API Key")
        
        // Initiate Beacon Manager
        beaconManager = KTKBeaconManager(delegate: self)
        beaconManager.requestLocationAlwaysAuthorization()
        
        // Region
        let proximityUUID = NSUUID(UUIDString: "f7826da6-4fa2-4e98-8024-bc5b71e0893e")
        let region = KTKBeaconRegion(proximityUUID: proximityUUID!, identifier: "region")
        
        // Start Monitoring and Ranging
        beaconManager.startMonitoringForRegion(region)
        beaconManager.startRangingBeaconsInRegion(region)
        
        return true
    }
}

extension AppDelegate: KTKBeaconManagerDelegate {
    
    func beaconManager(manager: KTKBeaconManager, didChangeLocationAuthorizationStatus status: CLAuthorizationStatus) {
        
    }
    
    func beaconManager(manager: KTKBeaconManager, didEnterRegion region: KTKBeaconRegion) {
        print("Enter region \(region)")
    }
    
    func beaconManager(manager: KTKBeaconManager, didExitRegion region: KTKBeaconRegion) {
        print("Exit region \(region)")
    }
    
    func beaconManager(manager: KTKBeaconManager, didRangeBeacons beacons: [CLBeacon], inRegion region: KTKBeaconRegion) {
        print("Ranged beacons count: \(beacons.count)")
    }
}
```

### Run the project
> You won't be able to run apps that use Apple Core Location services (that includes our SDK) on the Simulator, so first, you'll need to connect a physical iOS device to run your app.

1.  Connect an iOS device to your Mac.
2.  In the project navigator, choose your device from the scheme pop-up menu.
    Xcode assumes you intend to use the selected device for development and automatically registers it for you.
3.  Click the Run button.

Check out Apple's guide to [Launching Your App on Devices](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/LaunchingYourApponDevices/LaunchingYourApponDevices.html) for more details.

## Eddystone support

**KTKEddystoneManager** is key to retrieving Eddystone format beacon information. 
`KTKEddystoneManager` can discover nearby Eddystone format devices using regions/filters to narrow results.

``` Objective-C

@interface ViewController () <KTKEddystoneManagerDelegate>

@property KTKEddystoneManager *eddystoneManager;

@property KTKEddystoneRegion *namespaceRegion;
@property KTKEddystoneRegion *domainRegion;
@property KTKSecureEddystoneRegion *secureNamespaceRegion;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	// Eddystone Manager	        
   	self.eddystoneManager = [[KTKEddystoneManager alloc] initWithDelegate:self];
}
```

### Discover Eddystone devices
In this example we will start discovering Eddystone devices in `viewWillAppear:` method and stop in `viewWillDisappear:`.

``` Objective-C
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
 	 	
 	// If should scan for all nearby Eddystones
 	// Passing nil will look for all regions
    [self.eddystoneManager startEddystoneDiscoveryInRegion:nil];
    
    // Scan for Eddystones with specific namespace ID
    self.namespaceRegion = [[KTKEddystoneRegion alloc] initWithNamespaceID:@"namespaceID"];
    [self.eddystoneManager startEddystoneDiscoveryInRegion: self.namespaceRegion];
    
    // Scan for Eddystone with specific domain in url
    self.domainRegion = [[KTKEddystoneRegion alloc] initWithURLDomain:@"github.com"];    
    [self.eddystoneManager startEddystoneDiscoveryInRegion: self.domainRegion];
    
    // Scan for Secure Namespace Region
    self.secureNamespaceRegion = [[KTKSecureEddystoneRegion alloc] initWithSecureNamespaceID:@"secure_namespace_id"];    
    [self.eddystoneManager startEddystoneDiscoveryInRegion: self.secureNamespaceRegion];
}

- (void)viewWillDisappear:(BOOL)animated
{    
    [super viewWillDisappear:animated];

    // Stop 
    [self.eddystoneManager stopEddystoneDiscoveryInAllRegions];
    
    // ... or you can just stop for one specific region by using
    [self.eddystoneManager stopEddystoneDiscoveryInRegion: self.domainRegion];
}
```

Read more about security and shuffling on our [support page](https://support.kontakt.io/hc/en-gb/sections/201612029).

### KTKEddystoneManagerDelegate
All delegate methods can be found in [KTKEddystoneManagerDelegate](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Protocols/KTKEddystoneManagerDelegate.html) documentation.

``` Objective-C
- (void)eddystoneManager:(KTKEddystoneManager *)manager didDiscoverEddystones:(NSSet <KTKEddystone*>*)eddystones inRegion:(__kindof KTKEddystoneRegion* _Nullable)region
{
	if ([region isEqual:self.domainRegion]) {
		// Eddystone discovered with URL in `github.com` domain ...
	}
}
```

---

## Communicating with the Kontakt.io Rest API

The [Kontakt.io Rest API](/rest-api/stable/quickstart/) provides a series of resources to query/update our cloud platform and allow you to manage your venues and beacons, and retrieve beacon actions.

Class responsible for communication with API is [KTKCloudClient](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html). 

You can initialize it by calling ...

``` Objective-C
KTKCloudClient *client = [KTKCloudClient new];
```

or use shared instance (singleton) used by the SDK API calls ...

``` Objective-C
KTKCloudClient *client = [KTKCloudClient sharedInstance];
```

If specific `NSURLSessionConfiguration` configuration is required you can use:

``` Objective-C
KTKCloudClient *client = [[KTKCloudClient alloc] initWithSessionConfiguration: ...];
```

API Key must be provided before calling any method from `KTKCloudClient`.

``` Objective-C
[Kontakt setAPIKey:@"Your API Key"];
```

[Get your API key](/rest-api/stable/quickstart#get-your-api-key)

### Using KTKCloudClient

After initialization; `KTKCloudClient` object acts as a facade between your app and Kontakt.io services. You can use it to get actions, beacons, and venues assigned to your company (and much more).

Getting list of devices is as simple as ...

**Objective-C**

``` Objective-C
[[KTKCloudClient sharedInstance] getObjects:[KTKDevice class] completion:^(KTKKontaktResponse * _Nullable response, NSError * _Nullable error) {
	NSLog(@"%@". [response objects]);
}];
```

or in **Swift**

``` Objective-C
KTKCloudClient.sharedInstance().getObjects(KTKDevice.self) { response, error in
	print(response?.objects)
}

// Get Venues
KTKCloudClient.sharedInstance().getObjects(KTKVenue.self) { response, error in
	print(response?.objects)
}
```

To create, update or delete objects you can use one of provided methods:

* [createObject:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/createObject:completion:)
* [updateObject:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/updateObject:completion:)
* [deleteObject:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/deleteObject:completion:) or [deleteObject:primaryKey:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/deleteObject:primaryKey:completion:)

All classes representing objects from the API conforms to protocol `KTKCloudModel`.

### Responses from KTKCloudClient

All Cloud Client responses are wrapped with [KTKKontaktResponse](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKKontaktResponse.html). `KTKKontaktResponse` provides more context for the result. You can for example get next set of the results using `nextResultsURL` property like:

``` Objective-C
// Get Device by unique ID ...
NSDictionary *parameters = @{ @"uniqueId": @"K0nT" };

[[KTKCloudClient sharedInstance] getObjects:[KTKDevice class] parameters:parameters completion:^(KTKKontaktResponse * _Nullable response, NSError * _Nullable error) {
		// Check for errors etc ...
		
		// Call next result set ..
        [[KTKCloudClient sharedInstance] GET:response.nextResultsURL completion:^(KTKKontaktResponse * _Nullable response, NSError * _Nullable error) {
        	// ... more results ?
        }];
    }];
```

### Custom calls to the API

If there is a custom call you would like to make to the API you can use:

* [GET:parameters:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/GET:parameters:completion:)
* [POST:parameters:completion:](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html#//api/name/POST:parameters:completion:)

Both methods take endpoint name parameter and HTTP parameters dictionary. 

You can find more information in the Appledocs [KTKCloudClient](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKCloudClient.html) class reference.

---

## Bluetooth Device Management

The Kontakt.io iOS SDK contains classes and methods that let you easily connect to a Kontakt.io device, read its parameters, and modify some of them. First however, you need to scan for nearby devices.

``` Objective-C
@property KTKDevicesManager *devicesManager;
...
self.devicesManager = [[KTKDevicesManager alloc] initWithDelegate: self];

// Calling `startDevicesDiscoveryWithInterval:` will report devices every `interval` value you specify.
[self.devicesManager startDevicesDiscoveryWithInterval:2.0];

// Calling `startDevicesDiscovery` will report devices in real time.
[self.devicesManager startDevicesDiscovery];
```

[KTKDevicesManager](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKDevicesManager.html) informs its delegate about devices currently in range.

All delegate methods can be found in [KTKDevicesManagerDelegate](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Protocols/KTKDevicesManagerDelegate.html) documentation.

``` Objective-C
#pragma mark - KTKDevicesManagerDelegate method

- (void)devicesManager:(KTKDevicesManager*)manager didDiscoverDevices:(NSArray <KTKNearbyDevice*>* _Nullable)devices;
    // Do something with devices.
}
```

Nearby Devices discovered by [KTKDevicesManager](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKDevicesManager.html) are of [KTKNearbyDevice](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKNearbyDevice.html) class.

Changing [KTKNearbyDevice](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKNearbyDevice.html) configuration requires [KTKDeviceConnection](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/Classes/KTKDeviceConnection.html) and it is as simple as:

**Objective-C**

``` Objective-C
// Create Configuration
KTKDeviceConfiguration *configuration = [KTKDeviceConfiguration new];
configuration.name = @"Disco Beacon";
configuration.advertisingInterval = @350;
configuration.major = @123;

// Connection
KTKDeviceConnection *connection = [[KTKDeviceConnection alloc] initWithNearbyDevice: nearbyDevice];

// Write Cofiguration
[connection writeConfiguration:configuration completion:^(BOOL synchronized, KTKDeviceConfiguration * _Nullable configuration, NSError * _Nullable error) {
	// Process response
}];
```

**Swift**

``` Swift
// Create Configuration
let configuration = KTKDeviceConfiguration()
        
configuration.name = "Disco Beacon"
configuration.advertisingInterval = 350
configuration.major = 123

// Connection
let deviceConnection = KTKDeviceConnection(nearbyDevice: device)

// Write Cofiguration
deviceConnection.writeConfiguration(configuration) { synchronized, configuration, error in
	// Process response
}
```

More code samples and scenarios will be covered in our sample project on [github](https://github.com/kontaktio/kontakt-ios-sdk).

## Microlocating vs Bluetooth

Kontakt.io iOS SDK makes extensive use of two native iOS frameworks: [Core Location](https://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CoreLocation_Framework/_index.html "Core Location Framework Reference") and [Core Bluetooth](https://developer.apple.com/library/ios/documentation/CoreBluetooth/Reference/CoreBluetooth_Framework/_index.html "Core Bluetooth Framework Reference"). It is important to understand that although both of them use Bluetooth Low Energy, they are separate technologies and do not have much in common. 
	
