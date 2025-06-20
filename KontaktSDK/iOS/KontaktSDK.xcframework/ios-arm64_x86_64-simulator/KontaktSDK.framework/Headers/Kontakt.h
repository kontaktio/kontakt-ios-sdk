//
//  KontaktSDK
//  Version: 5.0.2
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

@end
