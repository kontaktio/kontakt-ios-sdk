//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKKontaktResponse.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKCloudClient (Interface)
/** 
 Kontakt.io's Cloud Client
  
    #import <KontaktSDK/KontaktSDK.h>
 
    [Kontakt setCloudAPIKey:@"API_KEY"];

    KTKCloudClient *client = [KTKCloudClient new];

    [client POST: @"path" parameters: @{} completionHandler:^(KTKKontaktResponse *response, NSError *error) {
        
    }];
 */

@interface KTKCloudClient : NSObject

#pragma mark - Generic API Request
///--------------------------------------------------------------------
/// @name Generic API Request
///--------------------------------------------------------------------

/**
 *  Sends Cloud request using GET HTTP Method
 *
 *  @param endpoint   Path of resource or endpoint from Cloud API
 *  @param dictionary Dictionary of parameters
 *  @param completion Completion Block
 * 
 *  @see KTKCloudClientCompletionHandler
 */
- (void)GET:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Sends Cloud request using POST HTTP Method
 *
 *  @param endpoint   Path of resource or endpoint from Cloud API
 *  @param dictionary Dictionary of parameters
 *  @param completion Completion Block
 *
 *  @see KTKCloudClientCompletionHandler
 */
- (void)POST:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock)completion;;

@end

NS_ASSUME_NONNULL_END
