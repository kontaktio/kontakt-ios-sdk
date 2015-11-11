//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

typedef NS_ENUM(NSInteger, KTKDeviceType) {
    KTKDeviceTypeInvalid     = -1,
    KTKDeviceTypeBeacon      = 1,
    KTKDeviceTypeCloudBeacon = 2
};

typedef NS_ENUM(NSInteger, KTKDeviceAdvertisingProfile) {
    KTKDeviceAdvertisingProfileInvalid   = -1,
    KTKDeviceAdvertisingProfileIBeacon   = 1,
    KTKDeviceAdvertisingProfileEddystone = 2
};

typedef NS_ENUM(NSInteger, KTKDeviceAccess) {
    KTKDeviceAccessInvalid   = -1,
    KTKDeviceAccessOwner      = 1,
    KTKDeviceAccessSupervisor = 2,
    KTKDeviceAccessEditor     = 3,
    KTKDeviceAccessViewer     = 4
};

typedef NS_ENUM(NSInteger, KTKDeviceSpecification) {
    KTKDeviceSpecificationInvalid  = -1,
    KTKDeviceSpecificationStandard = 1
};

typedef NS_ENUM(NSInteger, KTKDeviceTransmissionPower) {
    KTKDeviceTransmissionPowerInvalid = -1,
    KTKDeviceTransmissionPower0, // -30,
    KTKDeviceTransmissionPower1, // -20,
    KTKDeviceTransmissionPower2, // -16,
    KTKDeviceTransmissionPower3, // -12,
    KTKDeviceTransmissionPower4, // -8,
    KTKDeviceTransmissionPower5, // -4,
    KTKDeviceTransmissionPower6, // 0,
    KTKDeviceTransmissionPower7, // 4
};
