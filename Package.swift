// swift-tools-version: 5.4
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "kontakt-ios-sdk",
    platforms: [.iOS(.v12)],
    products: [
        .library(
            name: "KontaktSDK",
            targets: ["KontaktSDK"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "KontaktSDK",
            path: "KontaktSDK/iOS/KontaktSDK.xcframework"
        ),
    ]
)
