//  Copyright © 2024 Kontakt.io

@import Foundation;

@protocol KTKDeviceGatewayLogsOperationDelegate <NSObject>

@property (nonatomic, assign, readonly) BOOL shouldStopLogging;

- (void)gatewayDeviceDidStartReceivingLogs;
- (void)gatewayDeviceDidFinishReceivingLogs:(NSArray<NSError*>* _Nullable)errors;
- (void)gatewayDeviceDidReceiveLogs:(NSString * _Nonnull)message;

@end
