# Kontakt iOS SDK

## Breaking changes notes

### 6.0.0
* `writeConfiguration` and `synchronizeInternalState` connection methods now have additional completion paramater `isTimeSynced`.
* `KTKDeviceGatewayLogsOperation` has been renamed to `KTKDeviceCCOperation` with `mode` parameter set to `KTKDeviceCCOperationModeGatewayLogs`.
* Removed unused `KTKDeviceConnectionSensorsUpdate` block type.
* Changed minimum iOS version requirement from 12.0 to 13.0

### 5.1.0
This version has been re-released as 6.0.0 beacuse it contains breaking changes. To ensure API stability please use 5.0.2 version.

### 5.0.0
* This version removes `KTKDeviceCredentials` and all code related to 'offline' configuration. All operations are set to use `KTKConfigProfileGeneratorUsingCloud` - this value cannot be changed anymore.
* Added support for streaming secure config (for both read and write config operations). Streaming method will be used as default for Portal Light v3.0.0+, Portal Light 2 v1.3.0+ (since SDK version 5.0.2), non-legacy beacon devices with firmware 2.11.0+.<br/>
This feature can be turned off by setting `preferredConfigProfileReadWriteMethod` property to `KTKConfigProfileReadWriteMethodLegacy` in `KTKDeviceConnection`.

### 4.0.0
* Version `4.0.0` removes support for `tvOS` and `macOS`.
* `KTKDeviceSymbol` has been removed. `KTKDeviceModel` should be used instead.
* `KTKDeviceGatewayConfiguration` code has been merged with its superclass - `KTKDeviceConfiguration`. Gateway specific properties and methods are declared in `KTKDeviceGatewayConfigurationType.h`.
* `KTKConfigProfileGeneratorUsingCloud` is now a default value in device connection operations.

### 3.0.0
This version doesn't support older devices with firmware **`< 4.0`**. Newer devices with new firmware might generate a false negative error `This firmware version does not yet support (...) operation`. To avoid issues consider upgrading the SDK to version 4.x.x.

## Administration App

To configure Kontakt.io Devices we recommend using our [Kio Setup Manager App](https://apps.apple.com/pl/app/kio-setup-manager/id1067320511).

![screen](https://is1-ssl.mzstatic.com/image/thumb/PurpleSource126/v4/53/f8/3a/53f83a32-8d35-dc02-8195-fbb8d235e2d1/f37e9edd-62f7-4fb7-a994-c1e295d7e36f_IMG_0334.PNG/460x0w.webp)

## Sample Code
You can find our demos and sample code in [Examples folder](https://github.com/kontaktio/kontakt-ios-sdk/tree/master/Examples).

## Overview

This document shows you a quick way to start using the Kontakt.io SDK in location-aware apps. You will find code examples for core features and best practices that we recommend developers follow.

You can find more detailed information on our [Developer Portal](https://developer.kontakt.io/docs/dev-ctr-sdks/e4ecea94e246f-what-are-kontakt-io-sd-ks).

API documentation can be found on [Github Pages](http://kontaktio.github.io/kontakt-ios-sdk/)

## Installing the iOS SDK

To use the Kontakt.io SDK in your project, the minimum deployment target must be iOS 13.0.
You must also manually integrate [CBORCoding dependency](https://github.com/SomeRandomiOSDev/CBORCoding.git) v1.4.0 to fix linking errors.

### SPM

You can add Kontakt.io SDK to an Xcode project by adding it as a package dependency.

1. From the File menu, select Add Packages...
2. Enter "https://github.com/kontaktio/kontakt-ios-sdk" into the package repository URL text field
3. Add KontaktSDK directly to your application.
4. Add `CBORCoding` dependency https://github.com/SomeRandomiOSDev/CBORCoding.git v1.4.0+

### Manually

- Open up Terminal, `cd` into your top-level project directory, and run the following command *if* your project is not initialized as a git repository:

```bash
$ git init
```

- Add Kontakt.io SDK as a git [submodule](http://git-scm.com/docs/git-submodule) by running the following command:

```bash
$ git submodule add https://github.com/kontaktio/kontakt-ios-sdk.git
```

- Open the new `kontakt-ios-sdk` folder, and drag the `KontaktSDK.xcframework` into the Project Navigator of your application's Xcode project.

    * Make sure your target is checked in `Add to targets` section.

- Next, select your application project in the Project Navigator (blue project icon) to navigate to the target configuration window and select the application target under the "Targets" heading in the sidebar.
- In the tab bar at the top of that window, open the "General" panel.
- Click on the `+` button under the "Embedded Binaries" section.
    
- Select the `KontaktSDK.xcframework` and click `Add` button.

- Add [CBORCoding](https://github.com/SomeRandomiOSDev/CBORCoding.git) dependency (either manually or using SPM) to fix linking errors.

- (OPTIONAL) In the Build Phases tab, click the + button at the top and select “New Run Script Phase”. Enter the following code into the script text field:

```bash
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/KontaktSDK.xcframework/ios-arm64/KontaktSDK.framework/strip-frameworks.sh"
```

(The last step, courtesy of [Realm](https://github.com/realm/realm-cocoa/), is required for working around an [iOS App Store bug](http://www.openradar.me/radar?id=6409498411401216) when archiving universal binaries.)

---

### Further information
The SDK utilizes `CoreLocation` and `CoreBluetooth` system frameworks.
> Your project's Info.plist must contain following keys for your app to work correctly: 

```Objective-C
<key>NSLocationAlwaysAndWhenInUseUsageDescription</key>
<string>Kontakt SDK would like to use your current location to monitor and range your devices and to update their last known location.</string>
<key>NSBluetoothAlwaysUsageDescription</key>
<string>Kontakt SDK would like to use bluetooth to configure and manage your devices.</string>
```

Adjust the string value to your app's context.

## First steps

SDK requires API authorization keys/tokens that must be specified. There are two authentication methods - API Key and SSO Authentication token. We recommend using the latter as the most secure option.

### Option 1 - API key authorization
* Register a free account at [https://panel.kontakt.io](https://panel.kontakt.io/signin).
* Click on your account icon in the top right corner and choose "Security"
* Use the Server API Key value in your SDK setup code:

**Objective-C**

```Objective-C
#import <KontaktSDK/KontaktSDK.h>
```

```Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

	// Set API Key
	[Kontakt setAPIKey:@"Your API Key"];

    return YES;
}
```

**Swift**

```Swift
import KontaktSDK
```

```Swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
	
	// Set API Key
	Kontakt.setAPIKey("Your API Key")
	
	return true
}
```

⚠️ Avoid hardcoding API key value directly in your code. Treat it as a secret password.

### Option 2 - SSO Authentication token

* Register a free account at [https://panel.kontakt.io](https://panel.kontakt.io/signin).
* Contact our support to register your app and obtain dedicated client ID, issuer URL and redirect URL.
* Create a new SSO session with Kio Cloud (See example below)
* Extract authentication token from the session and use it in your SDK setup code:

**Objective-C**

```Objective-C
#import <KontaktSDK/KontaktSDK.h>
```

```Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Set Auth headers provider
    [Kontakt setAuthHeadersProvider:^(NSURLSession * _Nonnull urlSession, void (^ _Nonnull completion)(NSDictionary * _Nullable)) {
        NSDictionary *headers = @{@"Authorization": @"Bearer <accessToken>"};
        completion(headers);
    }];

    return YES;
}
```

**Swift**

```Swift
import KontaktSDK
```

```Swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
    
    // Set Auth headers provider
    Kontakt.setAuthHeadersProvider { urlSession, completion in
        var headers = ["Authorization": "Bearer <accessToken>"]
        completion(headers as [AnyHashable: Any])
    }
    
    return true
}
```

#### Obtaining Authentication token example
The example code relies on [AppAuth](https://github.com/openid/AppAuth-iOS) framework.

```Swift
import AppAuth
import Foundation

func authorizeWithSSO(presenter: UIViewController) async throws -> String {
    let issuer = "<your dedicated issuer URL>"

    // discovers endpoints
    let configuration: OIDServiceConfiguration
    do {
        configuration = try await OIDAuthorizationService.discoverConfiguration(forIssuer: issuer)
    } catch {
        throw error
    }

    // authentication request
    let request = OIDAuthorizationRequest(
        configuration: configuration,
        clientId: "<your dedicated client ID>",
        scopes: [OIDScopeOpenID, OIDScopeProfile, "offline_access"],
        redirectURL: "<your dedicated redirect URL>",
        responseType: OIDResponseTypeCode,
        additionalParameters: nil
    )

    return try await withCheckedThrowingContinuation { [weak self] continuation in
        DispatchQueue.main.async { [weak self] in
            let authSession = OIDAuthState.authState(byPresenting: request, presenting: presenter, prefersEphemeralSession: true) { authState, error in
                if let authState,
                   let accessToken = authState.lastTokenResponse?.accessToken {
                    continuation.resume(returning: accessToken)
                } else {
                    continuation.resume(throwing: error)
                }
            }
        }
    }
}
```

## Interacting with Beacons - monitoring a region
In the following example we'll show you how to can create a simple application to monitor beacons for a specific region using the Kontakt.io SDK.

---

### Basic Setup
In our example, we have used the **AppDelegate.swift** class for simplicity. You would probably want to create your own class in a real application. 

First we'll import the Kontakt.io SDK.

```Swift
import KontaktSDK
```

We'll add the [KTKBeaconManager](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKBeaconManager.html) object as a property. 

KTKBeaconManager informs its delegates when a device enters or exits a region, and when beacons are ranged.

Make sure `AppDelegate` conforms to `KTKBeaconManagerDelegate` protocol.

---

We will use `application:didFinishLaunchingWithOptions:` to initiate beacon manager and start monitoring for region.

```Swift
var beaconManager: KTKBeaconManager!

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {

    // Set API Key
    Kontakt.setAPIKey("Your API Key")

    // OR set Auth headers provider
    Kontakt.setAuthHeadersProvider { urlSession, completion in
        var headers = ["Authorization": "Bearer <accessToken>"]
        completion(headers as [AnyHashable: Any])
    }

    // Initiate Beacon Manager
    self.beaconManager = KTKBeaconManager(delegate: self)

    // Request Location Authorization
    self.beaconManager.requestLocationAlwaysAuthorization()

    return true
}
```

---

You can test if the current device is capable of monitoring beacons using:

```Swift
if KTKBeaconManager.isMonitoringAvailable {
	
}
```

or check authorization status using:

```Swift
if KTKBeaconManager.locationAuthorizationStatus == .authorizedAlways {
	
}
```

### Beacon Region

Now we'll start monitoring a specific region.

For more information on [KTKBeaconRegion](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKBeaconRegion.html) see Appledoc.

> Regions define a set of beacons that your application is aware of, so the beacon manager will interact only with those beacons.

```Swift
// Kontakt.io proximity UUID
let proximityUUID = try! UUID(value: "f7826da6-4fa2-4e98-8024-bc5b71e0893e") // KTKKontaktProximityUUID

// Create region instance
let region = KTKBeaconRegion(proximityUUID: proximityUUID, identifier:"identifier")

// Start Monitoring
self.beaconManager.startMonitoring(for: region)

// You can also start ranging ...
self.beaconManager.startRangingBeacons(in: region)
```

### Secure Beacon Region

Secure beacon region is very similar to standard beacon region.
For more information on [KTKSecureBeaconRegion](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKSecureBeaconRegion.html) see Appledoc.

Read more about security and shuffling on our [support page](https://support.kontakt.io/hc/en-gb/articles/4413258529554-About-Secure-Shuffling).

> You can find your beacon's Secure Proximity UUID in Kontakt.io Device Management Web Panel (in the beacon's Security Tab).

```Swift
// Your secure proximity UUID
let secureProximityUUID = try! UUID(value: "00000000-0000-0000-0000-00000000")

// Create secure region instance
let region = KTKSecureBeaconRegion(secureProximityUUID: secureProximityUUID, identifier:"identifier_secure")
```

You can also use an unsecure proximity UUID and it will be translated to the secure proximity by calling Cloud API under the hood.

```Swift
// Kontakt.io proximity UUID
let proximityUUID = try! UUID(value: "f7826da6-4fa2-4e98-8024-bc5b71e0893e") // KTKKontaktProximityUUID

// Create secure region instance with your non secure proximity 
let region = KTKSecureBeaconRegion(proximityUUID: proximityUUID, identifier:"identifier")
```

### Delegate Calls

Now we'll add the the delegate methods for beaconManager, and get them to log some output.
All delegate methods can be found in [KTKBeaconManagerDelegate](https://kontaktio.github.io/kontakt-ios-sdk/docs/Protocols/KTKBeaconManagerDelegate.html) documentation.

```Swift
func beaconManager(_ manager: KTKBeaconManager, didChangeLocationAuthorizationStatus status: CLAuthorizationStatus) {
	// ...
}

func beaconManager(_ manager: KTKBeaconManager, didEnter region: KTKBeaconRegion) {
    print("Enter region \(region)")
}

func beaconManager(_ manager: KTKBeaconManager, didExit region: KTKBeaconRegion) {
    print("Exit region \(region)")
}

func beaconManager(_ manager: KTKBeaconManager, didRangeBeacons beacons: [CLBeacon], in region: KTKBeaconRegion) {
    print("Ranged beacons count: \(beacons.count)"
}
```

---

## Eddystone support

**KTKEddystoneManager** is key to retrieving Eddystone format beacon information. 
`KTKEddystoneManager` can discover nearby Eddystone format devices using regions/filters to narrow results.

```Swift
import UIKit
import KontaktSDK

class ViewController: UIViewController, KTKEddystoneManagerDelegate {
    
    var eddystoneManager: KTKEddystoneManager!
    
    var namespaceRegion: KTKEddystoneRegion!
    var domainRegion: KTKEddystoneRegion!
    var secureNamespaceRegion: KTKSecureEddystoneRegion!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Eddystone Manager
        eddystoneManager = KTKEddystoneManager(delegate: self)
    }
}
```

### Discover Eddystone devices
In this example we will start discovering Eddystone devices in `viewWillAppear:` method and stop in `viewWillDisappear:`.

```Swift
override func viewWillAppear(_ animated: Bool) {
    super.viewWillAppear(animated)
    
    // If should scan for all nearby Eddystones
    // Passing nil will look for all regions
    eddystoneManager.startEddystoneDiscovery(in: nil)
    
    // Scan for Eddystones with specific namespace ID
    namespaceRegion = KTKEddystoneRegion(namespaceID: "namespaceID")
    eddystoneManager.startEddystoneDiscovery(in: namespaceRegion)
    
    // Scan for Eddystone with specific domain in URL
    domainRegion = KTKEddystoneRegion(urlDomain: "github.com")
    eddystoneManager.startEddystoneDiscovery(in: domainRegion)
    
    // Scan for Secure Namespace Region
    secureNamespaceRegion = KTKSecureEddystoneRegion(secureNamespaceID: "secure_namespace_id")
    eddystoneManager.startEddystoneDiscovery(in: secureNamespaceRegion)
}

override func viewWillDisappear(_ animated: Bool) {
    super.viewWillDisappear(animated)
    
    // Stop
    eddystoneManager.stopEddystoneDiscoveryInAllRegions()
    
    // ... or you can just stop for one specific region
    eddystoneManager.stopEddystoneDiscovery(in: domainRegion)
}
```

Read more about security and shuffling on our [support page](https://support.kontakt.io/hc/en-gb/articles/4413258529554-About-Secure-Shuffling).

### KTKEddystoneManagerDelegate
All delegate methods can be found in [KTKEddystoneManagerDelegate](https://kontaktio.github.io/kontakt-ios-sdk/docs/Protocols/KTKEddystoneManagerDelegate.html) documentation.

```Objective-C
func eddystoneManager(_ manager: KTKEddystoneManager, didDiscoverEddystones eddystones: Set<KTKEddystone>, inRegion region: KTKEddystoneRegion?) {
	if region == self.domainRegion {
		// Eddystone discovered with URL in `github.com` domain ...
	}
}
```

---

## Communicating with the Kontakt.io Rest API

⚠️ **DEPRECATION:** All Cloud communication will be moved to a separate package in future versions.

The [Kontakt.io Rest API](https://developer.kontakt.io/docs/dev-ctr-device-api/a09dcbf0d03de-device-management-api-introduction) provides a series of resources to query/update our cloud platform and allow you to manage your venues and beacons, and retrieve beacon actions.

Class responsible for communication with API is [KTKCloudClient](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html). 

You can initialize it by calling ...

```Objective-C
KTKCloudClient *client = [KTKCloudClient new];
```

or use shared instance (singleton) used by the SDK API calls ...

```Objective-C
KTKCloudClient *client = [KTKCloudClient sharedInstance];
```

If specific `NSURLSessionConfiguration` configuration is required you can use:

```Objective-C
KTKCloudClient *client = [[KTKCloudClient alloc] initWithSessionConfiguration: ...];
```

API Key must be provided before calling any method from `KTKCloudClient`.

```Objective-C
[Kontakt setAPIKey:@"Your API Key"];
```

Alternatively, if you use other authentication method like SSO, you can set a block in `Konktat.setAuthHeadersProvider` that obtains up-to-date token and calls `completion` with a dictionary containing HTTP headers that will be uses in each request made by `KTKCloudClient`. (See `First steps` section)

```Objective-C
[Kontakt setAuthHeadersProvider:^(NSURLSession * _Nonnull urlSession, void (^ _Nonnull completion)(NSDictionary * _Nullable)) {
    NSDictionary *headers = @{@"Authorization": @"Bearer <accessToken>"};
    completion(headers);
}];
```

### Using KTKCloudClient

After initialization; `KTKCloudClient` object acts as a facade between your app and Kontakt.io services. You can use it to get actions, beacons, and venues assigned to your company (and much more).

Getting list of devices is as simple as ...

**Objective-C**

```Objective-C
[[KTKCloudClient sharedInstance] getObjects:[KTKDevice class] completion:^(KTKKontaktResponse * _Nullable response, NSError * _Nullable error) {
	NSLog(@"%@". [response objects]);
}];
```

or in **Swift**

```Objective-C
KTKCloudClient.sharedInstance().getObjects(KTKDevice.self) { response, error in
	print(response?.objects)
}

// Get Venues
KTKCloudClient.sharedInstance().getObjects(KTKVenue.self) { response, error in
	print(response?.objects)
}
```

To create, update or delete objects you can use one of provided methods:

* [createObject:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/createObject:completion:)
* [updateObject:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/updateObject:completion:)
* [deleteObject:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/deleteObject:completion:) or [deleteObject:primaryKey:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/deleteObject:primaryKey:completion:)

All classes representing objects from the API conforms to protocol `KTKCloudModel`.

### Responses from KTKCloudClient

All Cloud Client responses are wrapped with [KTKKontaktResponse](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKKontaktResponse.html). `KTKKontaktResponse` provides more context for the result. You can for example get next set of the results using `nextResultsURL` property like:

```Objective-C
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

* [GET:parameters:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/GET:parameters:completion:)
* [POST:parameters:completion:](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html#//api/name/POST:parameters:completion:)

Both methods take endpoint name parameter and HTTP parameters dictionary. 

You can find more information in the Appledocs [KTKCloudClient](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKCloudClient.html) class reference.

---

## Bluetooth Device Management

The Kontakt.io iOS SDK contains classes and methods that let you easily connect to a Kontakt.io device, read its parameters, and modify some of them. First however, you need to scan for nearby devices.

```Swift
let devicesManager = KTKDevicesManager(delegate: self)

// Enable automatic device telemetry uploads (optional)
devicesManager.uploadingTelemetry = true

// Calling `startDevicesDiscovery(interval:)` will report devices every `interval` value (in seconds) you specify.
devicesManager.startDevicesDiscovery(interval: 2.0)

// Calling `startDevicesDiscovery()` instead will report devices in real time.
devicesManager.startDevicesDiscovery()
```

[KTKDevicesManager](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKDevicesManager.html) informs its delegate about devices currently in range.

All delegate methods can be found in [KTKDevicesManagerDelegate](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKDevicesManagerDelegate.html) documentation.

```Swift
// MARK: - KTKDevicesManagerDelegate method

func devicesManager(_ manager: KTKDevicesManager, didDiscover devices: [KTKNearbyDevice]) {
    // Do something with devices.
}
```

Nearby Devices discovered by [KTKDevicesManager](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKDevicesManager.html) are of [KTKNearbyDevice](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKNearbyDevice.html) class.

Changing [KTKNearbyDevice](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKNearbyDevice.html) configuration requires [KTKDeviceConnection](https://kontaktio.github.io/kontakt-ios-sdk/docs/Classes/KTKDeviceConnection.html) and it is as simple as:

**Objective-C**

```Objective-C
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

```Swift
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

More code samples and scenarios is covered in our sample project on [github](https://github.com/kontaktio/kontakt-ios-sdk).

---

## Troubleshooting

Kontakt SDK provides some API methods that can help troubleshoot issues related to SDK functionality. They can also be used to forward additional debug information to 3rd party bug reporting tools (like Luciq or Sentry). The following methods report SDK's interal messages and data that can provide more context for troubleshooting process. These infomation, however, should be used as a **secondary source** after inspecting errors reported by main API's callbacks and delegate methods.

### Debug logs

Use `Kontakt.setDebugLogsProxy` to get debug level messages from the SDK.  
Use `Kontakt.setErrorLogsProxy` to get error level messages from the SDK.  


```Swift
Kontakt.setDebugLogsProxy { logMessage, fileName, functionName, lineNumber in
    let formattedMessage = "KontaktSDK >>> [DEBUG][\(fileName)|\(lineNumber)] ➡ \(logMessage)"
    print(formattedMessage)
}
Kontakt.setErrorLogsProxy { logMessage, fileName, functionName, lineNumber in
    let formattedMessage = "KontaktSDK >>> [ERROR][\(fileName)|\(lineNumber)] ➡ \(logMessage)"
    print(formattedMessage)
}
```

### Cloud API events

`Kontakt.setNetworkEventHandler` can be used to read requests and responses sent to Kontakt.io Cloud API by the SDK.

```Swift
Kontakt.setNetworkEventHandler { response, data, request, duration in
    guard let httpResponse = response as? HTTPURLResponse else {
        return
    }

    print("[\(request.httpMethod)](\(httpResponse.statusCode)) \(request.url?.absoluteString ?? "")")
}

```

## Microlocating vs Bluetooth

Kontakt.io iOS SDK makes extensive use of two native iOS frameworks: [Core Location](https://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CoreLocation_Framework/_index.html "Core Location Framework Reference") and [Core Bluetooth](https://developer.apple.com/library/ios/documentation/CoreBluetooth/Reference/CoreBluetooth_Framework/_index.html "Core Bluetooth Framework Reference"). It is important to understand that although both of them use Bluetooth Low Energy, they are separate technologies and do not have much in common. 
	
