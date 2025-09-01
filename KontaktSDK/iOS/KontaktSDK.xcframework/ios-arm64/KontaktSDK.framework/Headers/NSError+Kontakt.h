//
//  KontaktSDK
//  Version: 6.2.0
//
//  Copyright © 2016 Kontakt.io. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - NSError (Kontakt)
@interface NSError (Kontakt)

#pragma mark - Kontakt SDK Error Generators
///--------------------------------------------------------------------
/// @name Kontakt SDK Error Generators
///--------------------------------------------------------------------

+ (instancetype)ktk_errorWithKey:(NSString*)key;

+ (instancetype)ktk_errorWithKey:(NSString*)key moreInfo:(NSDictionary * _Nullable)moreInfo;

@end

NS_ASSUME_NONNULL_END
