//
//  KontaktSDK
//  Version: 6.0.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
#import "KTKCloudClientResponseSerializer.h"

#pragma mark - External Constants
extern NSString * const KTKResponseSerializerErrorDomain;
extern NSString * const KTKResponseSerializerFailingURLResponseErrorKey;
extern NSString * const KTKResponseSerializerFailingURLResponseDataErrorKey;
extern NSString * const KTKResponseSerializerFailingURLResponseServerErrorKey;

#pragma mark - KTKCloudClientJSONResponseSerializer (Interface)
@interface KTKCloudClientJSONResponseSerializer : NSObject <KTKCloudClientResponseSerializer>

@end