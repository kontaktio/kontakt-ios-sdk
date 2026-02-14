# kontakt-ios-sdk — Architecture

## Overview
This is the public distribution repository for the KontaktSDK iOS framework. It contains the pre-built KontaktSDK.xcframework binary, SPM Package.swift manifest, example projects, and documentation. Developers integrate this package to add Kontakt.io BLE beacon monitoring, device management, and cloud API capabilities to their iOS apps. This repo does not contain source code — the SDK is built from the `ios-sdk` source repository.

## Status
Active — last commit 2025-09-05. Regularly updated with new SDK releases (current major version 6.x). This is the public-facing distribution channel.

## Tech Stack
- Distribution: Swift Package Manager (Package.swift with binaryTarget)
- Binary: KontaktSDK.xcframework (iOS arm64)
- Minimum deployment: iOS 12.0 (per Package.swift), iOS 13.0 (per documentation)
- External dependency: CBORCoding v1.4.0 (must be manually integrated to fix linking errors)

## Components / Modules
- **KontaktSDK/iOS/KontaktSDK.xcframework** — Pre-built binary framework
- **Examples/** — Sample code demonstrating SDK usage
- **Documentation/** — Appledocs for API reference

## Interfaces
- **Exposes:**
  - `KTKBeaconManager` — iBeacon monitoring and ranging with secure beacon support
  - `KTKEddystoneManager` — Eddystone BLE format discovery
  - `KTKDevicesManager` — Nearby BLE device scanning with telemetry upload
  - `KTKDeviceConnection` — Bluetooth device configuration (read/write)
  - `KTKCloudClient` — REST API client for Kontakt.io cloud platform
  - `Kontakt` — Global SDK configuration (API key, auth headers, monitoring options)
- **Consumes:**
  - Kontakt.io REST API (device management, actions, venues, firmware)
  - Apple CoreBluetooth and CoreLocation frameworks
- **Data Stores:** None directly (consumers manage their own persistence)

## Architecture Notes
- Distributed exclusively as a binary XCFramework — no source code in this repo
- SPM integration via `binaryTarget` pointing to the local xcframework path
- Supports both Objective-C and Swift consumers via bridging header
- Breaking changes tracked in README with migration guidance per major version
- Current version 6.0.0 introduced streaming secure config, renamed gateway operations

## Known Issues / Risks
- CBORCoding v1.4.0 must be manually integrated — not declared as an SPM dependency in Package.swift, which can cause linking errors
- iOS Simulator not supported for CoreLocation-dependent features (beacon monitoring/ranging)
- Legacy firmware (< 4.0) not supported since SDK 3.0.0
