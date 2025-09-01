//
//  KontaktSDK
//  Version: 6.2.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

#import "KTKDeviceConnection.h"
#import "KTKDeviceGatewayWiFiNetwork.h"
#import "KTKDeviceConfiguration.h"
#import "KTKDeviceGatewayDiagnostic.h"
#import "KTKDeviceCCOperationDelegate.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Completion Blocks

/**
 *  A completion block object to be executed when the reading WiFi networks operation finishes.
 *
 *  @param networks Set of WiFi networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetWiFiBlock)(NSSet <KTKDeviceGatewayWiFiNetwork *>* _Nullable networks, __kindof KTKDeviceConfiguration * _Nullable configuration, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the reading mac networks operation finishes.
 *
 *  @param networks Set of mac networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetMACBlock)(NSString * _Nullable mac, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the reading diagnostic networks operation finishes.
 *
 *  @param networks Set of diagnostic networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetDiagnosticBlock)(KTKDeviceGatewayDiagnostic * _Nullable gatewayDiagnostic, NSError * _Nullable error);

/**
 *  A handler block object executed when a log message is received from the device.
 *
 *  @param logsMessage A message receviced from the Gateway device.
 *  @param error An error object containing the error that indicates why the operation failed.
 *  @param stop Set to @c true to stop the operation.
 */
typedef void (^KTKDeviceGatewayConnectionBLELogsHandlerBlock)(NSString* _Nullable logsMessage, NSError* _Nullable, BOOL* _Nullable stop);

#pragma mark - KTKDeviceGatewayConnection (Interface)
@interface KTKDeviceGatewayConnection : KTKDeviceConnection

#pragma mark - Connection Methods
///--------------------------------------------------------------------
/// @name Connection Methods
///--------------------------------------------------------------------

- (void)writeUsingCloudConfiguration:(KTKDeviceConfiguration *)configuration completion:(KTKDeviceConnectionWriteCompletion)completion;

/**
 *  Reads the configuration from the connection device.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getWiFiNetworks:(KTKDeviceGatewayConnectionGetWiFiBlock)completion;

/**
 *  Reads the configuration from the connection device using MAC.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getMacDevice:(KTKDeviceGatewayConnectionGetMACBlock)completion;

/**
 *  Reads the configuration from the connection device using MAC.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getDiagnosticDevice:(KTKDeviceGatewayConnectionGetDiagnosticBlock)completion;

/**
 *  Starts BLE logging mode in the device and delegates all events to provided delegate object.
 *
 *  @param delegate A delegate object responsible for receiving log messages and stopping logging mode.
 */
- (void)startBLEDeviceLogging:(id<KTKDeviceCCOperationDelegate>)delegate;

/**
 *  Reboot the device.
 *
 *  @param completion A block object to be executed when write operation finishes.
 */
- (void)rebootDevice:(void (^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
