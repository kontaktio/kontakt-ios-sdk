//
//  KontaktSDK
//  Version: 1.0.5
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

/**
 *  A Kontakt device type.
 */
typedef NS_ENUM(NSInteger, KTKDeviceType) {
    /**
     *  Invalid device type.
     */
    KTKDeviceTypeInvalid     = -1,
    /**
     *  Beacon device type.
     */
    KTKDeviceTypeBeacon      = 1,
    /**
     *  Cloud Beacon device type.
     */
    KTKDeviceTypeCloudBeacon = 2
};

/**
 *  A device Advertising Profile
 */
typedef NS_ENUM(NSInteger, KTKDeviceAdvertisingProfile) {
    /**
     *  Invalid Profile.
     */
    KTKDeviceAdvertisingProfileInvalid   = -1,
    /**
     *  iBeacon Profile.
     */
    KTKDeviceAdvertisingProfileIBeacon   = 1,
    /**
     *  Eddystone Profile.
     */
    KTKDeviceAdvertisingProfileEddystone = 2
};

/**
 *  A device access rights.
 */
typedef NS_ENUM(NSInteger, KTKDeviceAccess) {
    /**
     *  Invalid value.
     */
    KTKDeviceAccessInvalid   = -1,
    /**
     *  Owner
     */
    KTKDeviceAccessOwner      = 1,
    /**
     *  Supervisor
     */
    KTKDeviceAccessSupervisor = 2,
    /**
     *  Editor
     */
    KTKDeviceAccessEditor     = 3,
    /**
     *  Viewer
     */
    KTKDeviceAccessViewer     = 4
};

/**
 *  A kontakt device specification.
 */
typedef NS_ENUM(NSInteger, KTKDeviceSpecification) {
    /**
     *  Invalid value.
     */
    KTKDeviceSpecificationInvalid  = -1,
    /**
     *  Standard specification.
     */
    KTKDeviceSpecificationStandard = 1
};

/**
 *  A kontakt device shuffle status.
 */
typedef NS_ENUM(NSInteger, KTKDeviceShuffleStatus) {
    /**
     *  Status is unknown.
     */
    KTKDeviceShuffleStatusUknown        = -1,
    /**
     *  Device shuffle is not supported.
     */
    KTKDeviceShuffleStatusNotSupported  = 0,
    /**
     *  Device shuffle status is ON.
     */
    KTKDeviceShuffleStatusON            = 1,
    /**
     *  Device shuffle status is OFF.
     */
    KTKDeviceShuffleStatusOFF           = 2
};

/**
 *  A device transmission power level.
 *
 *  @see https://support.kontakt.io/hc/en-gb/articles/201621521-Transmission-power-settings
 */
typedef NS_ENUM(NSInteger, KTKDeviceTransmissionPower) {
    /**
     *  Invalid value
     */
    KTKDeviceTransmissionPowerInvalid = -1,
    /**
     *  Transmission power level 0 (-30dBm).
     */
    KTKDeviceTransmissionPower0,
    /**
     *  Transmission power level 1 (-20dBm).
     */
    KTKDeviceTransmissionPower1,
    /**
     *  Transmission power level 2 (-16dBm).
     */
    KTKDeviceTransmissionPower2,
    /**
     *  Transmission power level 3 (-12dBm).
     */
    KTKDeviceTransmissionPower3,
    /**
     *  Transmission power level 4 (-8dBm).
     */
    KTKDeviceTransmissionPower4,
    /**
     *  Transmission power level 5 (-4dBm).
     */
    KTKDeviceTransmissionPower5,
    /**
     *  Transmission power level 6 (0dBm).
     */
    KTKDeviceTransmissionPower6,
    /**
     *  Transmission power level 7 (4dBm).
     */
    KTKDeviceTransmissionPower7,
};
