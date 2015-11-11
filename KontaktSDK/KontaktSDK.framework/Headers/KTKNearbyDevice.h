//
//  KontaktSDK
//  Version: 0.9.0
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
 *  Tranmission power. (read-only)
 */
@property (nonatomic, readonly, assign) KTKDeviceTransmissionPower transmissionPower;

/**
 *  Flag indicating if device is currently in Shuffle mode. (read-only)
 *  
 *  @see http://kontakt.io/blog/beacon-security/
 */
@property (nonatomic, readonly, assign, getter=isShuffled) BOOL shuffled;

/**
 *  Flag indicating if device is currently in DFU mode. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isDFU) BOOL DFU;

/**
 *  Flag indicating if device is locked/nonconnectable mode. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isLocked) BOOL locked;

/**
 *  Current advertising profile. (read-only)
 */
@property (nonatomic, readonly, assign) KTKDeviceAdvertisingProfile advertisingProfile;

/**
 *  CoreBluetooth Perihperal object assosiated with the device. (read-only)
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
