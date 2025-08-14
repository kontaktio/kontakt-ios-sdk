//
//  KontaktSDK
//  Version: 6.1.0
//
//  Copyright © 2018 Kontakt.io. All rights reserved.
//

#import "KTKDeviceGATTOperation.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceListenOperation (Interface)
@interface KTKDeviceListenOperation : KTKDeviceGATTOperation

@property (nonatomic, assign) NSTimeInterval listenUntilPayloadTimeout;
@property (nonatomic, copy) void (^listeningBlock)(id _Nullable payload, BOOL * _Nonnull stop);

@end

NS_ASSUME_NONNULL_END
