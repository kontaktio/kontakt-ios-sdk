//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class KTKKontaktResponse;
typedef void (^KTKKontaktResponseCompletionBlock)(KTKKontaktResponse * _Nullable response, NSError * _Nullable error);

#pragma mark - KTKKontaktResponse (Interface)
@interface KTKKontaktResponse: NSObject

@property (nonatomic, assign, readonly) NSUInteger startIndex;
@property (nonatomic, assign, readonly) NSUInteger maxResult;

@property (nonatomic, assign, readonly) NSUInteger objectsCount;
@property (nonatomic, strong, readonly) NSArray *objects;

@property (nonatomic, strong, readwrite) NSURL *previousResultsURL;
@property (nonatomic, strong, readwrite) NSURL *nextResultsURL;

- (void)moreResultsWithCompletion:(KTKKontaktResponseCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
