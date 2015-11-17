//
//  KontaktSDK
//  Version: 0.9.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
@import CoreLocation;

#import "KTKNearbyDevice.h"
#import "KTKDeviceConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString * const KTKDeviceConnectionErrorDomain;

typedef NS_ENUM(NSInteger, KTKDeviceConnectionErrorCode) {
    KTKDeviceConnectionErrorCodeUnknown = -1,
    KTKDeviceConnectionErrorCodeTimeout = 10
};

#pragma mark - KTKDeviceConnection (Interface)
@interface KTKDeviceConnection : NSObject

/**
 *  <#Description#>
 */
@property (nonatomic, assign, readwrite) NSTimeInterval connectionTimeout;

/**
 *  <#Description#>
 */
@property (nonatomic, assign, readwrite) NSUInteger connectionAttempts;

/**
 *  Creates instance of KTKDeviceConnection with given KTKNearbyDevice
 *
 *  @param device KTKNearbyDevice Object
 *
 *  @return New instance of KTKDeviceConnection
 */
- (instancetype)initWithBeacon:(CLBeacon*)beacon;

/**
 *  Creates instance of KTKDeviceConnection with given KTKNearbyDevice
 *
 *  @param device KTKNearbyDevice Object
 *
 *  @return New instance of KTKDeviceConnection
 */
- (instancetype)initWithNearbyDevice:(KTKNearbyDevice*)device;

/**
 *  <#Description#>
 *
 *  @param configuration <#configuration description#>
 *  @param completion    <#completion description#>
 */
- (void)writeConfiguration:(KTKDeviceConfiguration*)configuration completion:(void(^)(NSError * _Nullable))completion;

/**
 *  <#Description#>
 *
 *  @param completion <#completion description#>
 */
- (void)readConfigurationWithCompletion:(void(^)(KTKDeviceConfiguration *configuration, NSError * _Nullable))completion;

/**
 *  <#Description#>
 *
 *  @param completion <#completion description#>
 */
- (void)checkFirmwareUpdateWithCompletion:(void(^)(BOOL isAvailable, NSString * _Nullable firmwareVersion, NSError * _Nullable))completion;

/**
 *  <#Description#>
 *
 *  @param progress   <#progress description#>
 *  @param completion <#completion description#>
 */
- (void)updateFirmwareWithProgress:(void(^)(double))progress completion:(NSError * _Nullable)completion;

@end

NS_ASSUME_NONNULL_END
