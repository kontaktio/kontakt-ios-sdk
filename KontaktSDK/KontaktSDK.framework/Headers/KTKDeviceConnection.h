//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
@import CoreLocation;

#import "KTKNearbyDevice.h"
#import "KTKDeviceConfiguration.h"

extern NSString * const KTKDeviceConnectionErrorDomain;

typedef NS_ENUM(NSInteger, KTKDeviceConnectionErrorCode) {
    KTKDeviceConnectionErrorCodeUnknown = -1,
    KTKDeviceConnectionErrorCodeTimeout = 10
};

#pragma mark - KTKDeviceConnection (Interface)
@interface KTKDeviceConnection : NSObject

@property (nonatomic, assign, readwrite) NSTimeInterval connectionTimeout;
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
- (void)start;

- (void)writeDeviceConfiguration:(KTKDeviceConfiguration*)configuration completion:(void(^)(NSError *))completion;

- (void)readDeviceConfigurationWithCompletion:(void(^)(KTKDeviceConfiguration *configuration, NSError *))completion;

@end
