//
//  KontaktSDK
//  Version: 6.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - KTKCloudClientResponseSerializer Protocol
@protocol KTKCloudClientResponseSerializer <NSObject>

#pragma mark - Parsing Methods
///--------------------------------------------------------------------
/// @name Parsing Methods
///--------------------------------------------------------------------

/**
 *  Serializes response with the specified URL response object, data object and error.
 *
 *  @param response The URL response from the cloud API.
 *  @param data     The data object received from the cloud API.
 *  @param error    An error pointer.
 *
 *  @return A serialized response object.
 */
@required
- (id)responseObjectForResponse:(NSURLResponse *)response
                           data:(NSData *)data
                          error:(NSError **)error;

- (id)responseObjectForResponse:(NSURLResponse *)response
                          error:(NSError **)error;

@end
