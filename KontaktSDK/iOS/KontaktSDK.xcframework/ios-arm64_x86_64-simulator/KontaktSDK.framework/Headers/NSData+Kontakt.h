//
//  KontaktSDK
//  Version: 6.0.0
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
 *  Returns data with payload type and data length as a header.
 *
 *  Payload type - @b u8 equal to 1
 *
 *  Payload size - @b u16be
 *
 *  @return Header + original data.
 */
- (NSData *)cborFrameFormat;

/**
 *  Extracts protocol version (revision) from BLE frame.
 *
 *  @return Payload type as Int8 value.
 */
- (char)bleFrameProtocolVersion;

/**
 *  Extracts flags value from BLE frame.
 *
 *  @return Flags value as binary mask.
 */
- (char)bleFrameFlags;

/**
 *  Extracts operation type from BLE frame.
 *
 *  @return Operation type as Int8 value.
 */
- (char)bleFrameOperation;

/**
 *  Extracts payload size from BLE frame.
 *
 *  @return Payload size/length as UInt16 value.
 */
- (uint16_t)bleFramePayloadLength;

/**
 *  Extracts payload type from CBOR payload.
 *
 *  @return Payload type as Int8 value.
 */
- (char)cborFramePayloadType;

/**
 *  Extracts payload size from CBOR payload.
 *
 *  @return Payload size/length as UInt16 value.
 */
- (uint16_t)cborFramePayloadLength;


#pragma mark - Extracting Primitives
///--------------------------------------------------------------------
/// @name Extracting Primitives
///--------------------------------------------------------------------

- (uint8_t)UInt8;

- (uint16_t)UInt16;

- (uint32_t)UInt32;


@end

NS_ASSUME_NONNULL_END
