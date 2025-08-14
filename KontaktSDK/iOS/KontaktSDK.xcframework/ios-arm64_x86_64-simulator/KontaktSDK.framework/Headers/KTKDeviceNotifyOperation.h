//
//  KontaktSDK
//  Version: 6.1.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

#import "KTKDeviceGATTOperation.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceReadOperation (Interface)
@interface KTKDeviceNotifyOperation : KTKDeviceGATTOperation

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns GATT notify operation with the specified service UUID string, characteristic UUID string and value.
 *
 *  @param service        A service UUID string object.
 *  @param characteristic A characteristic UUID string object.
 *  @param value          A notify value to be set.
 *
 *  @return An initialized GATT notify operation.
 */
- (instancetype)initWithService:(NSString *)service characteristic:(NSString *)characteristic value:(BOOL)value;

@end

NS_ASSUME_NONNULL_END

