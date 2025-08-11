//
//  KontaktSDK
//  Version: 5.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "NSURLRequest+Kontakt.h"
#import "KTKCloudClientResponseSerializer.h"
#import "KTKCloudClientJSONResponseSerializer.h"

/**
 *  A block object to be executed when the data task finishes.
 *
 *  @param responseObject The response object.
 *  @param error          An error object.
 */
typedef void (^KTKCloudClientSessionManagerDefaultCompletionBlock)(id responseObject, NSError *error);

/**
 *  A block object to be executed when the download task finishes.
 *
 *  @param data  The downloaded data object.
 *  @param error An error object.
 */
typedef void (^KTKCloudClientSessionManagerDownloadCompletionBlock)(NSData *data, NSError *error);

#pragma mark - KTKCloudClientSessionManager (Interface)
@interface KTKCloudClientSessionManager : NSObject

#pragma mark - Session Manager Properties
///--------------------------------------------------------------------
/// @name Session Manager Properties
///--------------------------------------------------------------------

/**
 *  The base URL for the HTTP client.
 */
@property (nonatomic, strong, readwrite) NSURL *baseURL;

/**
 *  The URL session object.
 */
@property (nonatomic, strong, readonly) NSURLSession *URLSession;

/**
 *  Dispatch queue on which delegate call will be executed.
 */
@property (nonatomic, strong, readonly) NSOperationQueue *sessionDelegateQueue;

/**
 *  The response serializer.
 * 
 *  @see KTKCloudClientResponseSerializer
 */
@property (nonatomic, strong, readwrite) id<KTKCloudClientResponseSerializer> responseSerializer;

/**
 *  The array of the current tasks.
 */
@property (nonatomic, strong, readonly) NSArray *tasks;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a session manager object with the specified base URL and session configuration object.
 *
 *  @param baseURL       The base URL for the HTTP client.
 *  @param configuration The configuration used to create the managed session.
 *
 *  @return An initialized session manager object.
 */
- (instancetype)initWithBaseURL:(NSURL*)baseURL
                  configuration:(NSURLSessionConfiguration *)configuration;

#pragma mark - Sending Requests
///--------------------------------------------------------------------
/// @name Sending Requests
///--------------------------------------------------------------------

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a <code>POST</code> request.
 *
 *  @param path       The URL path used to create the request. Relative to the <code>baseURL</code>.
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)POST:(NSString*)path
                   parameters:(NSDictionary*)parameters
            completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a <code>POST</code> request.
 *
 *  @param path       The URL path used to create the request. Relative to the <code>url</code>.
 *  @param url        The URL set baseURL
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)POST:(NSString*)path
                          url:(NSURL*)url
                   parameters:(NSDictionary*)parameters
            completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a <code>POST</code> request encoded for JSON payload.
 *
 *  @param path       The URL path used to create the request. Relative to the <code>baseURL</code>.
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */

- (NSURLSessionDataTask*)JSON:(NSString*)path
                   parameters:(NSDictionary*)parameters
            completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a <code>POST</code> request encoded for JSON payload.
 *
 *  @param path       The URL path used to create the request.
 *  @param url        The URL set baseURL
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */

- (NSURLSessionDataTask*)JSON:(NSString*)path
                          url:(NSURL*)url
                   parameters:(NSDictionary*)parameters
            completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a <code>GET</code> request.
 *
 *  @param path       The URL path used to create the request. Relative to the <code>baseURL</code>.
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)GET:(NSString*)path
                  parameters:(NSDictionary*)parameters
           completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a specified method request.
 *
 *  @param method     The HTTP method used to create the request.
 *  @param path       The URL path used to create the request. Relative to the baseURL.
 *  @param parameters The parameters to be encoded according to the client request serializer.
 *  @param encoder    The encoder to use for request encoding.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)dataTaskWithMethod:(NSString*)method
                                       path:(NSString*)path
                                 parameters:(NSDictionary*)parameters
                                    encoder:(KTKCloudClientRequestEncoder)encoder
                          completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a specified URL request object.
 *
 *  @param request    The request to be used with the task.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)dataTaskWithRequest:(NSURLRequest*)request
                           completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion;

/**
 *  Creates an <code>NSURLSessionDataTask</code> with a specified URL request object.
 *
 *  @param request    The request to be used with the task.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized data task object.
 */
- (NSURLSessionDataTask*)dataTaskWithRequest:(NSURLRequest*)request
                           completionHandler:(KTKCloudClientSessionManagerDefaultCompletionBlock)completion
                                 shouldRetry:(BOOL)shouldRetry;

/**
 *  Creates an <code>NSURLSessionDownloadTask</code> with a specified URL request object.
 *
 *  @param request    The request to be used with the task.
 *  @param completion A block object to be executed when the task finishes.
 *
 *  @return An initialized download task object.
 */
- (NSURLSessionDownloadTask*)downloadTaskWithRequest:(NSURLRequest*)request
                                   completionHandler:(KTKCloudClientSessionManagerDownloadCompletionBlock)completion;
@end
