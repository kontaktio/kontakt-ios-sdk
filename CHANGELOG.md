## Changelog

### v6.1.0 - 14 Aug 2025
- Added `MonitorState` to storage data parser
- Added support for tracking live accelerometer and accident data

### v6.0.0 - 12 Aug 2025
- Added automatic telemetry upload
- Improved gateway logs formatting
- Refactored C&C operations
- Fixed secure streaming writes (MTU check)
- Added forwarding debug and error logs to external handler
- Added support for IR stats telemetry field
- Added `SMART_BADGE_3_MINI` string model
- Added operations to write and read encrypted config directly to/from the device
- Added support and data operations for Temperature Monitor devices
- Added support for optional operations (e.g. time sync)
- Other fixes and improvements

### v5.1.0 - 11 Aug 2025
- Same as 6.0.0 but with a wrong version number

### v5.0.2 - 11 Jun 2025
- Recompiled binary to work with Xcode 16.4

### v5.0.1 - 24 Mar 2025
- Fixed crash in `KTKNearbyDeviceLegacyParser`

### v5.0.0 - 21 Mar 2025
- Added support for streaming secure config
- Added support for Gateway info telemetry frame
- Added `rawData` field to device telemetry
- Made `getBlinkDevice` function available for all devices
- Removed `KTKDeviceCredentials` and code related to offline configuration
- Removed deprecated functions
- Deleted unnecesary API requests
- Removed telemetry reports related to an obsolete endpoint
- Fixed errors in `KTKDeviceConfiguration` JSON parsing
- Fixed crashes
- Fixed and updated DFU process
- Fixed race condition in sync and write config operations
- Fixed an issue with writing configuration to gateways

### v4.0.0 - 16 Jan 2025
- Added support for new devices
- Fixed device identification
- Added option to inject HTTP headers (SSO token support)
- Added gateway bluetooth logging
- Added gateway reboot command
- Removed `KTKDeviceSymbol`
- Removed tvOS and macOS support
- Fixed sync internal state operation
- Using online secure profile generation by default

### v3.0.26 - 4 Nov 2022
- Added support for new devices
- Added Diagnostic service for Portal Light
- Added device count
- Added RSSI scan telemetry files
- Added new UK environment
- Fix telemetry logic
- Added config for Portal Beam IR

### v3.0.23 - 13 Apr 2022
- Refactor code
- Update documentation

### v3.0.22 - 12 Apr 2022
- Added support for new devices
- Added support for XCFramework

### v3.0.4 - 21 Sep 2020
- Added support for new devices

### v3.0.1 - 29 Jan 2019
- Added support for new devices
- New naming convention for devices
- Bug fixes

### v2.0.1 - 30 Jul 2018
- Fixing GPS location cache
- Support longer unique IDs
- Fixing Gateway configuration
- Fixing TLM packet for Gateway devices

### v2.0.0 - 20 Jul 2018
- Dropping support for devices with firmware <4.0
- SDK will now support all new devices like HD or Tag
- Full support for Kontakt Telemetry Frame
- Optimizing many of SDK's operations for better performance
- Many small Bug Fixes

### v1.5.1 - 29 Sep 2017
- Added option to set CBCentralManagerOptionShowPowerAlertKey

### v1.5.0 - 29 Sep 2017
- Added Gateway Support
- Added Gateway WiFi configuration
- Changed Devices Manager nullability of delegate methods
- Kontakt Telemetry Support
- Better Errors Reporting
- Many Bug Fixes

### v1.4.4 - 29 March 2017
- Turning Off Power Saving
- Bug fixes and other improvements

### v1.4.3 - 21 March 2017
- Secure regions fixes for large deployments
- New API models for Kontakt.io Triggers
- Other fixes and improvements

### v1.4.2 - 2 March 2017
- Fixing `KTKDeviceManager` random crashing when Gateway is around.
- Fixing Github Issue [#40](https://github.com/kontaktio/kontakt-ios-sdk/issues/40)

### v1.4.1 - 28 February 2017
- Device Connection will be more stable now
- Faster firmware updates
- Bug fixes and other improvements

### v1.4.0 - 16 January 2017
- Device Connection improvements
- Beacon PRO Firmware Update
- Localized Errors
- Other Fixes and improvements

### v1.3.3 - 13 December 2016
- Fixes and stability improvements
- keepAlive flag added to KTKDeviceConnection
- Improve events collection

### v1.3.2 - 15 November 2016
- Making distance calculation method public
- Fixing EID and ETLM packets definitions

### v1.3.1 - 15 November 2016
- Beacon Pro Support
- Power Saving features support (Card, Beacon Pro)
- Connection and beacons configuration will be 50% more stable now
- Requesting state for specified region is working again
- Remove warnings on iOS 10
- macOS Fixes

### v1.2.2 - 31 August 2016
- Added support for Kontakt.io's new products
- KTKDeviceConnection instance doesnt require assigning to class var anymore
- Added support to read device configuration from devices with firmware >= 4.0
- Rewritten firmware update
- Added support for USB Beacon Firmware update
- Added sensored beacon basic support (Specific Devices Only)
- KTKDeviceConfiguration can be now used without uniqueID when using with KTKDeviceConnection
- Cloud client fixes
- Added Tough Beacon specification
- Battery monitoring fix
- Other minor bug-fixes and stability improvements

### ~~iOS~~ iOS/tvOS/macOS SDK V1.1.0-V1.1.1 - Released 25 February 2016
* We have added support to our SDK for iOS/tvOS/macOS

### iOS SDK V1.0.9 - Released 22 February 2016
* Added model property to KTKDevice (USB beacon support)
* SDK now uses API version 9
* KTKDevice minor improvements    
* USB beacon management support

### iOS SDK V1.0.8 - Released 19 February 2016
* Secure beacon region fix

### iOS SDK V1.0.7 - Released 18 February 2016
* Eddystone URL fix

### iOS SDK V1.0.6 - Released 15 February 2016
* Regions monitoring fix

### iOS SDK V1.0.2-1.0.5 - Released 12 February 2016
* Bitcode Fixes
* Fixes around an [App Store submission bug](http://www.openradar.me/radar?id=6409498411401216).

### iOS SDK V1.0.1 - Released 26 January 2016
* First release of the new iOS SDK
