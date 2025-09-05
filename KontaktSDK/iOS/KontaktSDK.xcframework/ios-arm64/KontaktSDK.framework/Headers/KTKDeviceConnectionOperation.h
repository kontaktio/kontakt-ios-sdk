//
//  KontaktSDK
//  Version: 6.2.1
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

@import CoreBluetooth;

#import "KTKGroupOperation.h"
#import "KTKNearbyDevice.h"
#import "KTKDeviceGATTOperation.h"

NS_ASSUME_NONNULL_BEGIN

@protocol KTKDeviceConnectionOperationDelegate;

#pragma mark - KTKDeviceConnectionOperationProtocol
@protocol KTKDeviceConnectionOperationProtocol <NSObject>

@property (nonatomic, weak, readwrite) KTKNearbyDevice * _Nullable device;

@end

#pragma mark - KTKDeviceConfigurationOperation (Interface)
@interface KTKDeviceConnectionOperation : KTKGroupOperation <KTKDeviceConnectionOperationProtocol, KTKDeviceGATTOperationDelegate, CBPeripheralDelegate>

#pragma mark - Operation Properties
///--------------------------------------------------------------------
/// @name Operation Properties
///--------------------------------------------------------------------

@property (nonatomic, weak, readwrite) id<KTKDeviceConnectionOperationDelegate> _Nullable delegate;

@property (nonatomic, copy, readwrite) void (^connectionCompletion)(BOOL indicator, id _Nullable, NSArray<NSError*>* _Nullable);

@property (nonatomic, copy, readwrite) void (^connectionCompletionMTU)(BOOL indicator, NSInteger mtu, NSString *firmware, id _Nullable, NSArray<NSError*>* _Nullable);

@property (nonatomic, weak, readwrite) __kindof KTKOperation * _Nullable GATTOperationsDependency;

@property (nonatomic, assign, readwrite) KTKDeviceConnectionOperationType type;
@property (nonatomic, assign, readwrite) BOOL syncTime;

#pragma mark - Operation Methods
///--------------------------------------------------------------------
/// @name Operation Methods
///--------------------------------------------------------------------

- (void)createOperations;

- (void)addGATTOperation:(__kindof KTKDeviceGATTOperation *)operation;
/// Optional operation does not cancel the connection when its characteristic couldn't be discovered.
- (void)addGATTOperation:(__kindof KTKDeviceGATTOperation *)operation asOptional:(BOOL)optional;
- (void)registerAdHocOperation:(__kindof KTKDeviceGATTOperation *)operation;

@end

#pragma mark - KTKDeviceConnectionOperationDelegate
@protocol KTKDeviceConnectionOperationDelegate <NSObject>

- (void)connectionOperation:(KTKDeviceConnectionOperation *)operation progress:(double)progress;

@end

NS_ASSUME_NONNULL_END
