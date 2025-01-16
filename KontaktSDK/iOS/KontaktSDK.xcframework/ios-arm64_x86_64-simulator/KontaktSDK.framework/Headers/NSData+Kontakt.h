//
//  KontaktSDK
//  Version: 4.0.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - NSData (Kontakt)
@interface NSData (Kontakt)

#pragma mark - Hex Conversion Methods
///--------------------------------------------------------------------
/// @name Hex Conversion Methods
///--------------------------------------------------------------------

/**
 *  Converts a data object to a hex string object representation.
 *
 *  @return A string object representation.
 */
- (NSString*)ktk_hexString;

/**
 *  Converts a HEX string object to a data object representation.
 *
 *  @param hexString The string object.
 *
 *  @return A data object representation.
 */
+ (NSData*)ktk_dataFromHexString:(NSString*)hexString;

#pragma mark - Other Methods
///--------------------------------------------------------------------
/// @name Other Methods
///--------------------------------------------------------------------

- (NSData *)ktk_dataSwapInt16;

- (NSData *)ktk_dataSwapInt32;

- (uint16_t)CRC16Modbus;

/**
 *  Adds payload type and data length as a header.
 *
 *  Payload type - @b u8 equal to 1
 *
 *  Payload size - @b u16be
 *
 *  @return Header + original data.
 */
- (NSData *)bleFrameFormat;

/**
 *  Extracts payload type from BLE frame.
 *
 *  @return Payload type as UInt8 value.
 */
- (char)bleFramePayloadType;

/**
 *  Extracts BLE frame's payload size.
 *
 *  @return Payload size/length as UInt16 value.
 */
- (uint16_t)bleFramePayloadLength;


#pragma mark - Extracting Primitives
///--------------------------------------------------------------------
/// @name Extracting Primitives
///--------------------------------------------------------------------

- (uint8_t)UInt8;

- (uint16_t)UInt16;

- (uint32_t)UInt32;


@end

NS_ASSUME_NONNULL_END
