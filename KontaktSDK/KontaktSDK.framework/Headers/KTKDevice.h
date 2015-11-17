//
//  KontaktSDK
//  Version: 0.9.2
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"
#import "KTKCloudModel.h"
#import "KTKDeviceConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDevice (Interface)
@interface KTKDevice : NSObject <KTKCloudModel>

#pragma mark - Device Object Properties
///--------------------------------------------------------------------
/// @name Device Object Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *uniqueID;

/**
 *  Secure iBeacon proximity UUID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *secureProximity;

/**
 *  Secure Eddystone namespace ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *secureNamespace;

/**
 *  The current device configuration object. (read-only)
 */
@property (nonatomic, strong, readonly) KTKDeviceConfiguration *currentConfiguration;

/**
 *  An alias of the device. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable alias;

/**
 *  Meta dictionary object. (read-only)
 */
@property (nonatomic, strong, readonly) NSDictionary * _Nullable meta;

/**
 *  The current firmware version. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *firmwareVersion;

/**
 *  Device type. (read-only)
 *
 *  @see KTKDeviceType
 */
@property (nonatomic, assign, readonly) KTKDeviceType type;

/**
 *  Device specification. (read-only)
 *
 *  @see KTKDeviceSpecification
 */
@property (nonatomic, assign, readonly) KTKDeviceSpecification specification;

/**
 *  Device manager's ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *managerID;

/**
 *  Device venue ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID * _Nullable venueID;

/**
 *  The number of actions assigned to the device.
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable actionsCount;

/**
 *  Device access rights. (read-only)
 *
 *  @see KTKDeviceAccess
 */
@property (nonatomic, assign, readonly) KTKDeviceAccess access;

/**
 *  The latitude of the device.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable latitude;

/**
 *  The longitude of the device.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable longitude;

@end

NS_ASSUME_NONNULL_END
