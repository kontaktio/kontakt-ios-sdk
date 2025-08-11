//  Copyright © 2024 Kontakt.io

@import Foundation;

@protocol KTKDeviceCCOperationDelegate <NSObject>

@property (nonatomic, assign, readonly) BOOL shouldStopReceivingCCData;

- (void)deviceDidStartReceivingCCData;
- (void)deviceDidFinishReceivingCCData:(NSArray<NSError*>* _Nullable)errors;
- (void)deviceDidReceiveCCLogs:(NSString * _Nonnull)message;

@end
