//
//  KontaktSDK
//  Version: 0.9.2
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class KTKKontaktResponse;

/**
 *  A block object to be executed when the cloud API request finishes.
 *
 *  @param response The cloud API response object.
 *  @param error    An error object.
 */
typedef void (^KTKKontaktResponseCompletionBlock)(KTKKontaktResponse * _Nullable response, NSError * _Nullable error);

#pragma mark - KTKKontaktResponse (Interface)
@interface KTKKontaktResponse: NSObject

#pragma mark - Properties
///--------------------------------------------------------------------
/// @name Properties
///--------------------------------------------------------------------

/**
 *  The index of which the result objects start from.
 */
@property (nonatomic, assign, readonly) NSUInteger startIndex;

/**
 *  The limit of the objects in the response.
 */
@property (nonatomic, assign, readonly) NSUInteger maxResult;

/**
 *  The count of the received objects.
 */
@property (nonatomic, assign, readonly) NSUInteger objectsCount;

/**
 *  The array of the objects received from the cloud API.
 */
@property (nonatomic, strong, readonly) NSArray * _Nullable objects;

/**
 *  The URL of the previous result set.
 */
@property (nonatomic, strong, readwrite) NSURL * _Nullable previousResultsURL;

/**
 *  The URL of the next result set.
 */
@property (nonatomic, strong, readwrite) NSURL * _Nullable nextResultsURL;

#pragma mark - Pagination Methods
///--------------------------------------------------------------------
/// @name Pagination Methods
///--------------------------------------------------------------------

/**
 *  Performs following request if there are more objects to get from the cloud API.
 *
 *  @param completion A block object to be executed when the cloud API request finishes.
 */
- (void)moreResultsWithCompletion:(KTKKontaktResponseCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
