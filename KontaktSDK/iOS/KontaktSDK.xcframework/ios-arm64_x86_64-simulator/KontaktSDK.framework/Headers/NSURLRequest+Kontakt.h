//
//  KontaktSDK
//  Version: 5.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - NSURLRequest (Kontakt)
@interface NSURLRequest (Kontakt)

/**
 *  Request Encoder
 */
typedef NS_ENUM(NSInteger, KTKCloudClientRequestEncoder) {
    /**
     *  Default POST request encoder.
     */
    KTKCloudClientRequestEncoderDefault = 0,
    /**
     *  POST JSON request encoder.
     */
    KTKCloudClientRequestEncoderJSON
};

#pragma mark - Serialization Methods
///--------------------------------------------------------------------
/// @name Serialization Methods
///--------------------------------------------------------------------

/**
 *  Serializes a request with the specified parameters object.
 *
 *  @param request    The request to be serialized for the session manager.
 *  @param parameters The parameters object.
 *
 *  @return A serialized request to be used by the session manager.
 */
+ (NSURLRequest *)ktk_HTTPRequestBySerializingRequest:(NSURLRequest *)request
                                              encoder:(KTKCloudClientRequestEncoder)encoder
                                       withParameters:(id)parameters;

@end
