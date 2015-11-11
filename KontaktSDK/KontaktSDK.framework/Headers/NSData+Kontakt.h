//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - NSData (Kontakt)
@interface NSData (Kontakt)

#pragma mark - Hex Conversion Methods
///--------------------------------------------------------------------
/// @name Hex Conversion Methods
///--------------------------------------------------------------------

/**
 *  Converts data object to hex string object representation.
 *
 *  @return String object representation.
 */
- (NSString*)ktk_hexString;

/**
 *  Converts HEX string object to data object representation.
 *
 *  @param HEX string object.
 *
 *  @return Data object representation.
 */
+ (NSData*)ktk_dataFromHexString:(NSString*)hexString;

@end
