//
//  KontaktSDK
//  Version: 6.2.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import CoreBluetooth;

#import "KTKOperation.h"
#import "KTKDeviceGATTDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

@protocol KTKDeviceGATTOperationDelegate;

#pragma mark - KTKDeviceCharacteristicOperation (Interface)
@interface KTKDeviceGATTOperation : KTKOperation

#pragma mark - Operation Properties
///--------------------------------------------------------------------
/// @name Operation Properties
///--------------------------------------------------------------------

@property (nonatomic, strong, readonly) CBUUID *serviceUUID;

@property (nonatomic, strong, readonly) CBUUID *characteristicUUID;

@property (nonatomic, weak, readwrite) CBCharacteristic * _Nullable characteristic;

@property (nonatomic, weak, readwrite) id<KTKDeviceGATTOperationDelegate> delegate;

@property (nonatomic, assign, readwrite, getter=isVerified) BOOL verified;

@property (nonatomic, strong, readwrite) id payload;

@property (nonatomic, assign, readwrite) BOOL shouldTransform;

@property (nonatomic, assign, readwrite) NSUInteger mtu;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

- (instancetype)initWithService:(NSString*)service characteristic:(NSString*)characteristic;

#pragma mark - Other Methods
///--------------------------------------------------------------------
/// @name Other Methods
///--------------------------------------------------------------------

- (NSValueTransformer* _Nullable)valueTransformer;

#pragma mark - Unavailable
- (instancetype)init __attribute__((unavailable("-init is not a valid initializer for the class KTKDeviceCharacteristicOperation")));

@end

#pragma mark - KTKDeviceGATTOperationDelegate
@protocol KTKDeviceGATTOperationDelegate <NSObject>

@optional
- (void)operationDidFinish:(__kindof KTKDeviceGATTOperation *)operation errors:(NSArray <NSError*> * _Nullable)errors;

@end

NS_ASSUME_NONNULL_END
