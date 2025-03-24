//
//  KontaktSDK
//  Version: 5.0.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
@import CoreLocation;

#import "KTKNearbyDevice.h"
#import "KTKFirmware.h"
#import "KTKDeviceConfiguration.h"
#import "KTKDeviceDataLoggerReading.h"
#import "KTKDeviceKontaktRecognitionBox.h"

@class KTKOperationQueue;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Completion Blocks
/**
 *  A completion block object to be executed when the write operation finishes.
 *
 *  @param synchronized  A Boolean indicating whether the configuration was synchronized to the Cloud API.
 *  @param configuration The configuration object containing write operation details. Please not that configuration object will be nil for devices with firmware < 4.0.
 *                       If <code>synchronized</code> is false you have to keep copy of the configuration and synchronize it with the cloud when possible.
 *                       When the device firmware is 4.0 or higher configuration object will contain <code>secureResponse</code> and <code>secureResponseTime</code>.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceConnectionWriteCompletion)(BOOL synchronized, KTKDeviceConfiguration * _Nullable configuration, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the read operation finishes.
 *
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceConnectionReadCompletion)(__kindof KTKDeviceConfiguration * _Nullable configuration, NSError * _Nullable error);

/**
 *  A block object to be executed when the sensors readings are updated.
 *
 *  @param reading  A sensors reading object. Result of the operation.
 *  @param error    An error object containing the error that indicates why the operation failed.
 *  @param stop     A reference to a Boolean value. The block can set the value to YES to stop further updates of the sensors readings otherwise connection and updates will be running indefinitely. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the block.
 */
typedef void (^KTKDeviceConnectionSensorsUpdate)(KTKDeviceDataLoggerReading * _Nullable reading, NSError * _Nullable error, BOOL * _Nonnull stop);

/**
 *  A completion block object to be executed when the update operation finishes.
 *
 *  @param synchronized A Boolean indicating whether the configuration was synchronized to the Cloud API.
 *  @param error        An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceConnectionUpdateCompletion)(BOOL synchronized, NSError * _Nullable error);

@protocol KTKDeviceConnectionDelegate;

#pragma mark - KTKDeviceConnection (Interface)
@interface KTKDeviceConnection : NSObject

#pragma mark - Connection Properties
///--------------------------------------------------------------------
/// @name Connection Properties
///--------------------------------------------------------------------

/**
*  A nearby device of this connection instance.
*/
@property (nonatomic, strong, readonly) KTKNearbyDevice *nearbyDevice;

/**
 *  A timeout interval for the connection.
 */
@property (nonatomic, assign, readwrite) NSTimeInterval connectionTimeout;

/**
 *  A number of maxium connection attempts if one failed.
 */
@property (nonatomic, assign, readwrite) NSUInteger connectionAttempts;

/**
 *  The delegate object that will receive events.
 */
@property (nonatomic, weak, readwrite) id<KTKDeviceConnectionDelegate> delegate;

/**
 *  Queue used for connection operations.
 */
@property (nonatomic, weak, readonly) KTKOperationQueue *sharedQueue;

/**
*  Most recently read configuration from connected device.
*/
@property (nonatomic, strong, readonly, nullable) KTKDeviceConfiguration *lastReadConfiguration;

#pragma mark - Configuration Profile Properties
///--------------------------------------------------------------------
/// @name Configuration Profile Properties
///--------------------------------------------------------------------

/**
 *  Preferred method for reading and writing Secure Configuration Profile.
 *  The actual method is selected based on device model and firmware version.
 */
@property (nonatomic, assign) KTKConfigProfileReadWriteMethod preferredConfigProfileReadWriteMethod;

#pragma mark - Other Properties
///--------------------------------------------------------------------
/// @name Other Properties
///--------------------------------------------------------------------

/**
 *  A Boolean value indicating whether the operation is currently executing.
 */
@property (nonatomic, readonly, getter=isExecuting) BOOL executing;

/**
 *  A Boolean value indicating whether the connection to the device should be kept alive.
 *  
 *  If any operation is scheduled and keepAlive flag is set to `YES` this class will keep connection alive even after scheduled operation is completed.
 *  To close the connection you have to either call `cancel` method or change `keepalive` to NO and if no more operations are scheduled connection will be closed immediately.
 */
@property (nonatomic, readwrite, getter=isKeepAlive) BOOL keepAlive;

/**
 *  A Boolean value indicating whether the devices rtc time should be updated automatically. Defaults to `YES`.
 */
@property (nonatomic, readwrite, getter=isUpdateTimeAutomatically) BOOL updateTimeAutomatically;

#pragma mark - Static Methods
///--------------------------------------------------------------------
/// @name Static Methods
///--------------------------------------------------------------------

/**
 *  Returns number of all connection operations scheduled in internal connection queue.
 *
 *  @return Number of all connection operations scheduled.
 */
+ (NSUInteger)connectionOperationsCount;

/**
 *  Cancels all connection operations scheduled in internal connection queue.
 */
+ (void)cancelAllOperations;
    
#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Creates instance of KTKDeviceConnection with given KTKNearbyDevice
 *
 *  @param nearbyDevice KTKNearbyDevice Object
 *
 *  @return New instance of KTKDeviceConnection
 */
- (instancetype)initWithNearbyDevice:(KTKNearbyDevice*)nearbyDevice;

#pragma mark - Connection Methods
///--------------------------------------------------------------------
/// @name Connection Methods
///--------------------------------------------------------------------

/**
 *  Writes the specified configuration to the connection device.
 *
 *  @param configuration The configuration object to write.
 *  @param completion    A block object to be executed when the write operation finishes.
 */
- (void)writeConfiguration:(KTKDeviceConfiguration*)configuration completion:(KTKDeviceConnectionWriteCompletion)completion;

/**
 *  Reads the configuration from the connection device.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)readConfigurationWithCompletion:(KTKDeviceConnectionReadCompletion)completion;

/**
 *  Send the current time to the connected device.
 *  
 *  @param completion A block object to be executed when the write operation finishes.
 */
- (void)syncTimeWithCompletion: (void (^)(NSError * _Nullable))completion;

/**
 *  Synchronize beacon state, including time.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)synchronizeInternalStateWithCompletion: (void (^)(__kindof KTKDeviceConfiguration * _Nullable, NSString *firmware, NSError * _Nullable))completion;

/**
 *  Updates a device to the latest available firmware.
 *
 *  @param firmware   The firmware object you want to update device to. <code>Has to be equal or grater than current firmware version.</code>
 *  @param progress   A block object to be executed when the progress of an update operation is recieved.
 *  @param completion A block object to be executed when the update operation finishes.
 */
- (void)updateWithFirmware:(KTKFirmware*)firmware progress:(void (^)(double))progress completion:(KTKDeviceConnectionUpdateCompletion)completion;

/**
 *  Get image from a device.
 *
 *  @param type   The type object you want to update device to. <code>Has to be equal or grater than current firmware version.</code>
 *  @param completion A block object to be executed when the update operation finishes download configuration, image and error.
 */
- (void)getImage:(KTKKontaktImageType)type completion:(void (^)(NSData * _Nullable, NSArray<KTKDeviceKontaktRecognitionBox *> * _Nullable, KTKDeviceConfiguration * _Nullable configuration, NSError * _Nullable))completion;

/**
 *  Blink device
 *
 *  @param completion A block object to be executed when the operation finishes.
 */
- (void)getBlinkDevice:(void (^)(NSError * _Nullable error))completion;

/**
 *  Cancels all operations on this connection.
 */
- (void)cancel;

@end

#pragma mark - KTKDeviceConnectionDelegate Protocol
/**
 *  It is possible if read and/or write operations are scheduled one after another that connection will happen only once,
 *  so any delegate's methods would be called just once, even with few configuration operations scheduled.
 */
@protocol KTKDeviceConnectionDelegate <NSObject>

#pragma mark - Connection Delegate Methods
///--------------------------------------------------------------------
/// @name Connection Delegate Methods
///--------------------------------------------------------------------

/**
 *  Tells the delegate that a device connection was successful.
 *
 *  @param connection The device connection object reporting the event.
 */
@optional
- (void)deviceConnectionDidConnect:(KTKDeviceConnection *)connection;

/**
 *  Tells the delegate what is the progress of a read or write operation.
 *
 *  @param connection The device connection object reporting the event.
 *  @param operation  An operation type.
 *  @param progress   An operation type.
 */
@optional
- (void)deviceConnection:(KTKDeviceConnection *)connection operation:(KTKDeviceConnectionOperationType)operation progress:(double)progress;

/**
 *  Tells the delegate that a device connection error occurred.
 *
 *  @param connection   The device connection object reporting the event.
 *  @param error        An error object containing the error that indicates why the connection failed.
 *  @param attemptsLeft A number of reconnection attempts left. If <code>attemptsLeft</code> is 0, it will report final error.
 */
@optional
- (void)deviceConnection:(KTKDeviceConnection *)connection didFailWithError:(NSError * _Nullable)error connectionAttemptsLeft:(NSInteger)attemptsLeft;

/**
 *  Tells the delegate that a devices connection was ended.
 *
 *  @param connection The device connection object reporting the event.
 *  @param error      An error object containing the error that indicates why the device disconnected.
 */
@optional
- (void)deviceConnectionDidDisconnect:(KTKDeviceConnection *)connection withError:(NSError * _Nullable)error;

@end

NS_ASSUME_NONNULL_END
