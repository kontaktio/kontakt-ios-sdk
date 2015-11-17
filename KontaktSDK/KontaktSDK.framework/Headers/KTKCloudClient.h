//
//  KontaktSDK
//  Version: 0.9.2
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKKontaktResponse.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKCloudClient (Interface)
@interface KTKCloudClient : NSObject

/**
 *  A shared instance of Cloud client, used by the low-level SDK methods, and suitable for use directly for any ad-hoc requests.
 *
 *  @return A shared instance of a Cloud client.
 */
+ (nonnull instancetype)sharedInstance;

#pragma mark - API Request Methods
///--------------------------------------------------------------------
/// @name API Request Methods
///--------------------------------------------------------------------

/**
 *  Runs a cloud API call with a GET request.
 *
 *  @param endpoint   The cloud API endpoint/resource.
 *  @param dictionary The parameters to be serialized for the request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 */
- (void)GET:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Runs a cloud API call with a POST request.
 *
 *  @param endpoint   The cloud API endpoint/resource.
 *  @param dictionary The parameters to be serialized for the request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 */
- (void)POST:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock)completion;;

@end

NS_ASSUME_NONNULL_END
