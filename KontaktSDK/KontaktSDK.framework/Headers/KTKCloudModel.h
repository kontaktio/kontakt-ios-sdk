//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - KTKCloudModel protocol
@protocol KTKCloudModel <NSObject, NSCopying, NSSecureCoding>

+ (instancetype)instanceFromResponseObject:(id)responseObject;

+ (NSSet*)mappingPaths;

+ (NSString*)collectionKeyPath;

@end
