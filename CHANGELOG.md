## Changelog

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
