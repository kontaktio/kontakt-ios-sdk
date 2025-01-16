// swift-tools-version: 5.4
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "kontakt-ios-sdk",
    platforms: [.iOS(.v12)],
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "KontaktSDK",
            targets: ["KontaktSDKWrapper"]
        ),
    ],
    dependencies: [
        .package(url: "https://github.com/SomeRandomiOSDev/CBORCoding.git", from: "1.4.0")
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .target(
            name: "KontaktSDKWrapper",
            dependencies: [
                .target(name: "KontaktSDK"),
                .product(name: "CBORCoding", package: "CBORCoding"),
            ]),
        .binaryTarget(
            name: "KontaktSDK",
            path: "KontaktSDK/iOS/KontaktSDK.xcframework"
        ),
    ]
)
