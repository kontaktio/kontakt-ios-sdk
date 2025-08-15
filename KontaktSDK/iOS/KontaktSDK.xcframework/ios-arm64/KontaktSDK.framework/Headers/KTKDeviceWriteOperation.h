//
//  KontaktSDK
//  Version: 6.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceGATTOperation.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceWriteOperation (Interface)
@interface KTKDeviceWriteOperation : KTKDeviceGATTOperation

/**
 * When set to `true` and when payload size is bigger than MTU, the payload will be written in multiple chunks instead of a single queued write.
 * This flag is ignored when `withoutResponse` is set to `false`.
 */
@property (nonatomic, assign, readwrite) BOOL allowWriteInChunks;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns GATT write operation with the specified service UUID string, characteristic UUID string and payload object.
 *
 *  @param service        A service UUID string object.
 *  @param characteristic A characteristic UUID string object.
 *  @param payload        A payload object to be written.
 *
 *  @return An initialized GATT write operation.
 */
- (instancetype)initWithService:(NSString *)service characteristic:(NSString *)characteristic payload:(id)payload;

/**
 *  Initializes and returns GATT write operation with the specified service UUID string, characteristic UUID string and payload object.
 *
 *  @param service         A service UUID string object.
 *  @param characteristic  A characteristic UUID string object.
 *  @param payload         A payload object to be written.
 *  @param withoutResponse    When set to `true` the operation will be marked as verified right after writing payload.
 *
 *  @return An initialized GATT write operation.
 */
- (instancetype)initWithService:(NSString *)service characteristic:(NSString *)characteristic payload:(id)payload withoutResponse:(BOOL)withoutResponse;

@end

NS_ASSUME_NONNULL_END
