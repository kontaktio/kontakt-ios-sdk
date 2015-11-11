//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKNearbyDevice.h"

@protocol KTKDevicesManagerDelegate;

#pragma mark - External Constants
extern NSTimeInterval const KTKDeviceInvalidationAgeNever;

#pragma mark - Type Definition
typedef NS_ENUM(NSUInteger, KTKDevicesManagerDiscoveryMode) {
    KTKDevicesManagerDiscoveryModeAuto = 0,
    KTKDevicesManagerDiscoveryModeInterval
};

#pragma mark - KTKDevicesManager (Interface)
@interface KTKDevicesManager : NSObject

/**
 *  Flag indicating if manager is currently scanning for eddystones.
 */
@property (nonatomic, assign, readonly, getter=isDiscovering) BOOL discovering;

/**
 *  The delegate object that will receive events.
 */
@property (nonatomic, weak, readonly) id<KTKDevicesManagerDelegate> delegate;

/**
 *  <#Description#>
 *
 *  @param delegate <#delegate description#>
 *
 *  @return <#return value description#>
 */
- (instancetype)initWithDelegate:(id<KTKDevicesManagerDelegate>)delegate;

/**
 *  <#Description#>
 */
@property (nonatomic, assign, readwrite) NSTimeInterval invalidationAge;

/**
 *  <#Description#>
 */
@property (nonatomic, assign, readwrite) KTKDevicesManagerDiscoveryMode discoveryMode;

/**
 *  <#Description#>
 */
@property (nonatomic, assign, readwrite) NSTimeInterval discoveryInterval;

/**
 *  <#Description#>
 */
- (void)startDevicesDiscovery;

/**
 *  <#Description#>
 *
 *  @param interval <#interval description#>
 */
- (void)startDevicesDiscoveryWithInterval:(NSTimeInterval)interval;

/**
 *  <#Description#>
 */
- (void)stopDevicesDiscovery;

/**
 *  <#Description#>
 *
 *  @param completion <#completion description#>
 */
- (void)restartDeviceDiscoveryWithCompletion:(void(^)( NSError * ))completion;

@end

#pragma mark - KTKDevicesManagerDelegate
@protocol KTKDevicesManagerDelegate <NSObject>

- (void)devicesManagerDidFailToStartDiscovery:(KTKDevicesManager*)manager withError:(NSError*)error;

@required
- (void)devicesManager:(KTKDevicesManager*)manager didDiscoverDevices:(NSArray*)devices;

@end