//
//  KontaktSDK
//  Version: 1.1.3
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import CoreBluetooth;
@import Foundation;

#if TARGET_OS_IOS
@import UIKit;
#endif

#import "KTKEddystone.h"
#import "KTKEddystoneRegion.h"
#import "KTKSecureEddystoneRegion.h"

NS_ASSUME_NONNULL_BEGIN

@protocol KTKEddystoneManagerDelegate;

#pragma mark - KTKEddystoneManager (Interface)
@interface KTKEddystoneManager : NSObject

#pragma mark - Other Properties
///--------------------------------------------------------------------
/// @name Other Properties
///--------------------------------------------------------------------

/**
 *  A Boolean indicating whether the eddystone manager is currently discovering eddy stones.
 */
@property (nonatomic, assign, readonly, getter=isDiscovering) BOOL discovering;

/**
 *  The current state of the bluetooth central.
 */
@property (nonatomic, assign, readonly) CBCentralManagerState centralState;

/**
 *  The delegate object that will receive events.
 *  
 *  @see KTKEddystoneManagerDelegate
 */
@property (nonatomic, weak, readonly) id<KTKEddystoneManagerDelegate> delegate;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns an eddystone manager object with the specified delegate.
 *
 *  @param delegate The delegate object that will receive events.
 *
 *  @return An initialized eddystone manager object.
 *
 *  @see KTKEddystoneManagerDelegate
 */
- (instancetype)initWithDelegate:(id<KTKEddystoneManagerDelegate>)delegate;

#pragma mark - Eddystone Discovery
///--------------------------------------------------------------------
/// @name Eddystone Discovery
///--------------------------------------------------------------------

/**
 *  Set of regions currently being tracked using discovery. (read-only)
 */
@property (nonatomic, strong, readonly) NSSet *discoveryRegions;

/**
 *  Starts the delivery of discovery notifications for eddystones in the specified region.
 *
 *  @param region The region that identifies the eddystones.
 *
 *  @see KTKEddystoneRegion
 */
- (void)startEddystoneDiscoveryInRegion:(__kindof KTKEddystoneRegion * _Nullable)region;

/**
 *  Stops the delivery of discovery notifications for eddystones in the specified region.
 *
 *  @param region The region that identifies the eddystones.
 * 
 *  @see KTKEddystoneRegion
 */
- (void)stopEddystoneDiscoveryInRegion:(__kindof KTKEddystoneRegion * _Nullable)region;

/**
 *  Stops the delivery of all discovery notifications for eddystones.
 */
- (void)stopEddystoneDiscoveryInAllRegions;

@end

#pragma mark - KTKEddystoneManagerDelegate
@protocol KTKEddystoneManagerDelegate <NSObject>

#pragma mark - Required Methods
///--------------------------------------------------------------------
/// @name Required Methods
///--------------------------------------------------------------------

/**
 *  Tells the delegate that one or more eddystones were discovered.
 *
 *  @param manager    The eddystone manager object reporting the event.
 *  @param eddystones Set of KTKEddystone objects representing eddystones currently discovered in the specified region.
 *  @param region     The region object containing the parameters that were used to locate the eddystones.
 *
 *  @see KTKEddystoneManager
 */
@required
- (void)eddystoneManager:(KTKEddystoneManager *)manager didDiscoverEddystones:(NSSet <KTKEddystone*>*)eddystones inRegion:(__kindof KTKEddystoneRegion* _Nullable)region;

#pragma mark - Optional Methods
///--------------------------------------------------------------------
/// @name Optional Methods
///--------------------------------------------------------------------

/**
 *  Tells the delegate that an error occurred while gathering discovery information for a set of eddystones.
 *
 *  @param manager The eddystone manager object reporting the event.
 *  @param error   An error object containing the error code that indicates why discovery failed.
 *
 *  @see KTKEddystoneManager
 */
@optional
- (void)eddystoneManagerDidFailToStartDiscovery:(KTKEddystoneManager*)manager withError:(NSError* _Nullable)error;

/**
 *  Tells the delegate that eddystone's frame was updated.
 *
 *  @param manager   The eddystone manager object reporting the event.
 *  @param eddystone Eddystone object of which frame was updated.
 *  @param frameType Frame type of the updated frame.
 *
 *  @see KTKEddystoneManager
 */
@optional
- (void)eddystoneManager:(KTKEddystoneManager*)manager didUpdateEddystone:(KTKEddystone*)eddystone withFrame:(KTKEddystoneFrameType)frameType;

@end

NS_ASSUME_NONNULL_END
