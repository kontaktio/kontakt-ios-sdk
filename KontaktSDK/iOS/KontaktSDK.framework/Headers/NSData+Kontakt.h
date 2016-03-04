//
//  KontaktSDK
//  Version: 1.1.3
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

@end
