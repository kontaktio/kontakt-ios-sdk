//
//  KontaktSDK
//  Version: 0.9.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKCloudModel protocol
@protocol KTKCloudModel <NSObject, NSCopying, NSSecureCoding>

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

@required
/**
 *  Creates an instance of a model Class from the specified response object.
 *
 *  @param responseObject The response object from the Cloud API.
 *
 *  @return An instance of a model object.
 */
+ (instancetype)instanceFromResponseObject:(id)responseObject;

#pragma mark - Mapping Methods
///--------------------------------------------------------------------
/// @name Mapping Methods
///--------------------------------------------------------------------

/**
 *  Set of paths to map response to the specific model Class.
 *
 *  @return A set of string objects.
 */
+ (NSSet*)mappingPaths;

/**
 *  Key path string object to use for mapping collections of the objects.
 *
 *  @return A key path string object.
 */
+ (NSString*)collectionKeyPath;

@end

NS_ASSUME_NONNULL_END
