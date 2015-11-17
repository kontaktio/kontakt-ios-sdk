//
//  KontaktSDK
//  Version: 0.9.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"
#import "KTKCloudModel.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceConfiguration (Interface)
@interface KTKDeviceConfiguration : NSObject <KTKCloudModel>

#pragma mark - General Properties
///--------------------------------------------------------------------
/// @name General Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, copy, readonly) NSString *uniqueID;

/**
 *  Kontakt device local name.
 */
@property (nonatomic, copy, readwrite) NSString *name;

/**
 *  Kontakt device password. 
 *
 *  Please note pasword property is nil when accessing it trough currentConfiguration on KTKDevice.
 *  You should only use it to change the device password.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable password;

/**
 *  A Boolean indicating whether device is in shuffle mode.
 */
@property (nonatomic, assign, readwrite, getter=isShuffled) BOOL shuffled;

/**
 *  Transmission power.
 *
 *  @see KTKDeviceTransmissionPower
 */
@property (nonatomic, assign, readwrite) KTKDeviceTransmissionPower transmissionPower;

/**
 *  Advertising profile.
 *
 *  @see KTKDeviceAdvertisingProfile
 */
@property (nonatomic, assign, readwrite) KTKDeviceAdvertisingProfile profile;

/**
 *  Advertising interval in milliseconds.
 *
 *  @see https://support.kontakt.io/hc/en-gb/articles/201567802-Advertising-Interval-best-practise
 */
@property (nonatomic, strong, readwrite) NSNumber *advertisingInterval;

#pragma mark - iBeacon Properties
///--------------------------------------------------------------------
/// @name iBeacon Properties
///--------------------------------------------------------------------

/**
 *  An iBeacon proximity UUID.
 */
@property (nonatomic, copy, readwrite) NSUUID *proximityUUID;

/**
 *  An iBeacon major value.
 */
@property (nonatomic, strong, readwrite) NSNumber *major;

/**
 *  An iBeacon minor value.
 */
@property (nonatomic, strong, readwrite) NSNumber *minor;

#pragma mark - Eddystone Properties
///--------------------------------------------------------------------
/// @name Eddystone Properties
///--------------------------------------------------------------------

/**
 *  An Eddystone namespace ID.
 */
@property (nonatomic, copy, readwrite) NSString *namespaceID;

/**
 *  An Eddystone instance ID.
 */
@property (nonatomic, copy, readwrite) NSString *instanceID;

/**
 *  An Eddystone URL object.
 */
@property (nonatomic, copy, readwrite) NSURL * _Nullable URL;

@end

NS_ASSUME_NONNULL_END
