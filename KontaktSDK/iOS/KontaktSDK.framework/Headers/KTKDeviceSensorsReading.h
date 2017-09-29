//
//  KontaktSDK
//  Version: 1.5.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceSensorsReading (Interface)
@interface KTKDeviceSensorsReading : NSObject <NSCopying>

@property (nonatomic, assign, readonly) NSUInteger lightPercentage;

@end

NS_ASSUME_NONNULL_END
