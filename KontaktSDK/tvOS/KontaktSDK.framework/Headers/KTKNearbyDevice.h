//
//  KontaktSDK
//  Version: 1.1.3
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;

#import "KTKDeviceDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKNearbyDevice (Interface)
@interface KTKNearbyDevice : NSObject <NSCopying>

#pragma mark - Nearby Device Properties
///--------------------------------------------------------------------
/// @name Nearby Device Properties
///--------------------------------------------------------------------

/**
 *  Advertised device name. (read-only)
 */
@property (nonatomic, readonly, strong) NSString * _Nullable name;

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, readonly, strong) NSString * _Nullable uniqueID;

/**
 *  Device firmware version. (read-only)
 */
@property (nonatomic, readonly, strong) NSString *firmwareVersion;

/**
 *  Battery level percentage. (read-only)
 */
@property (nonatomic, readonly, assign) NSUInteger batteryLevel;

/**
 *  Transmission power. (read-only)
 *  
 *  @see KTKDeviceTransmissionPower
 */
@property (nonatomic, readonly, assign) KTKDeviceTransmissionPower transmissionPower;

/**
 *  A Boolean indicating whether the device is currently in Shuffle mode. (read-only)
 *  
 *  @see http://kontakt.io/blog/beacon-security/
 */
@property (nonatomic, readonly, assign, getter=isShuffled) BOOL shuffled;

/**
 *  A Boolean indicating whether the device is currently in DFU mode. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isDFU) BOOL DFU;

/**
 *  A Boolean indicating whether the device is locked/non-connectable mode. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isLocked) BOOL locked;

/**
 *  Current advertising profile. (read-only)
 *
 *  @see KTKDeviceAdvertisingProfile
 */
@property (nonatomic, readonly, assign) KTKDeviceAdvertisingProfile advertisingProfile;

/**
 *  CoreBluetooth Peripheral object associated with the device. (read-only)
 */
@property (nonatomic, readonly, strong) CBPeripheral *peripheral;

/**
 *  Current RSSI value for the device. (read-only)
 */
@property (nonatomic, readonly, strong) NSNumber *RSSI;

/**
 *  Last discovery update timestamp. (read-only) 
 */
@property (nonatomic, readonly, assign) double updatedAt;

@end

NS_ASSUME_NONNULL_END
