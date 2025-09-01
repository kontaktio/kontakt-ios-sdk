//
//  KontaktSDK
//  Version: 6.2.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#define NETLOG 1

#if NETLOG == 1
    #define NetDebugLog(fmt, ...)  NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
    #define NetDebugLog(...)
#endif

#pragma mark - External Constants
extern double        KTKSDKVersion;
extern unsigned long KTKAPIVersion;

/**
 *  Devices monitoring options
 */
typedef NS_OPTIONS(NSUInteger, KTKMonitoringOptions) {
    /**
     *  The battery Status monitoring
     */
    KTKMonitoringOptionsBatteryStatus = 1 << 0,
    /**
     *  The devices GPS Position/Location monitoring
     */
    KTKMonitoringOptionsGPSLocation   = 1 << 1
};

/**
 *  Calculates distance to device from specified TX Power and RSSI.
 *
 *  @param TXPower Transmission power.
 *  @param RSSI    RSSI value.
 *
 *  @return Distance in meters as double value.
 */
extern double KTKCalculateDistanceFrom(int TXPower, double RSSI);

/**
 *  A block that takes 2 parameters:
 *  @param urlSession A `URLSession` object.
 *  @param completion Completion block that takes a dictionary object as parameter.
 */
typedef void (^_Nullable AuthHeadersProviderBlock)(NSURLSession *_Nonnull, void(^_Nonnull)(NSDictionary *_Nullable));

/**
 *  A block that takes 4 parameters:
 *  @param logMessage The log message.
 *  @param fileName Name of the file from which log message was sent.
 *  @param functionName Name of the function from which log message was sent.
 *  @param lineNumber Line number that contains log function.
 */
typedef void (^_Nullable DebugLogsProxyBlock)(NSString *_Nonnull, NSString *_Nonnull, NSString *_Nonnull, NSInteger);

/**
 *  A block that takes 4 parameters:
 *  @param response Received URL response.
 *  @param data Received response data (can be `nil` or empty).
 *  @param request Sent URL request.
 *  @param duration Duration of the request.
 */
typedef void (^_Nullable NetworkEventHandlerBlock)(NSURLResponse *_Nullable, NSData *_Nullable, NSURLRequest *_Nonnull, NSTimeInterval);

#pragma mark - Kontakt
@interface Kontakt : NSObject

#pragma mark - Configuration
///--------------------------------------------------------------------
/// @name Configuration
///--------------------------------------------------------------------

/**
 *  Sets the Cloud API Key.
 *
 *  @param key The API Key string.
 *
 *  @see APIKey
 */
+ (void)setAPIKey:(NSString *_Nullable)key;

/**
 *  Returns a string value of the Cloud API Key.
 *
 *  @return A string value of the API Key.
 *
 *  @see setAPIKey:
 */
+ (NSString *_Nullable)APIKey;

/**
 *  Sets authorization provider block used to inject authorization parameters into requests made by the SDK.
 *  The block has a completion handler parameter that should return a dictionary of request header parameters necessary for authorizing the request.
 *  @b IMPORTANT Calling this method with a non-nil value will disable `APIKey` value.
 *
 *  @param headersProvider A block called before each HTTP request with `URLSession` parameter used to send the request.
 */
+ (void)setAuthHeadersProvider:(AuthHeadersProviderBlock)headersProvider;

/**
 *  Returns authorization headers provider block.
 *
 *  @return A block value to be called with a `URLSession` object.
 */
+ (AuthHeadersProviderBlock)AuthHeadersProvider;

/**
 *  Removes caches created by the SDK.
 * 
 *  Cache should be removed every time <code>APIKey</code> is changed.
 */
+ (void)removeCaches;

/**
 *  Sets the devices monitoring options.
 *
 *  @param options The devices monitoring options.
 */
+ (void)setMonitoringOptions:(KTKMonitoringOptions)options;

/**
 *  Returns a devices monitoring options.
 * 
 *  Default value is KTKMonitoringOptionsBatteryStatus
 *
 *  @return A devices monitoring options.
 */
+ (KTKMonitoringOptions)monitoringOptions;

/**
 *  Sets the CBCentralManagerOptionShowPowerAlertKey option for internal Central Manager.
 *
 *  @param alert A Boolean value that specifies whether the system should display a warning dialog to the user if Bluetooth is powered off when the central manager is instantiated.
 */
+ (void)setCentralManagerPowerAlert:(BOOL)alert;

/**
 *  Sets debug logs proxy block.
 *  Can be used to intercept debug log messages and send them to your bug tracker (i.e. Instabug).
 *
 *  @param logsProxy A block called when external debug log is received.
 */
+ (void)setDebugLogsProxy:(DebugLogsProxyBlock)logsProxy;

/**
 *  A block value called automatically when using `DebugLog` function.
 *
 *  @return A debug logs proxy block.
 */
+ (DebugLogsProxyBlock)DebugLogsProxy;

/**
 *  Sets error logs proxy block.
 *  Can be used to intercept error log messages and send them to your bug tracker (i.e. Instabug).
 *
 *  @param logsProxy A block called when external error log is received.
 */
+ (void)setErrorLogsProxy:(DebugLogsProxyBlock)errorLogsProxy;

/**
 *  A block value called automatically when using `ErrorLog` function.
 *
 *  @return An error logs proxy block.
 */
+ (DebugLogsProxyBlock)ErrorLogsProxy;

/**
 *  Sets network event handler block.
 *
 *  @param networkEventHandler A block which is called when URL response is received.
 */
+ (void)setNetworkEventHandler:(NetworkEventHandlerBlock)networkEventHandler;

/**
 *  A block value to be called when URL response is received.
 *
 *  @return A network event handler block.
 */
+ (NetworkEventHandlerBlock)NetworkEventHandler;

@end
