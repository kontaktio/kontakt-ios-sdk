//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - External Constants
extern double        KTKSDKVersion;
extern unsigned long KTKAPIVersion;

/**
 *  Devices monitoring options
 */
typedef NS_OPTIONS(NSUInteger, KTKMonitoringOptions) {
    /**
     *  Battery Status monitoring
     */
    KTKMonitoringOptionsBatteryStatus = 1 << 0,
    /**
     *  Devices GPS Position/Location monitoring
     */
    KTKMonitoringOptionsGPSLocation   = 1 << 1
};

#pragma mark - Kontakt
@interface Kontakt : NSObject

#pragma mark - Configuration
///--------------------------------------------------------------------
/// @name Configuration
///--------------------------------------------------------------------

/**
 *  Sets the Cloud API Key.
 *
 *  @param key API Key string.
 *
 *  @see APIKey
 */
+ (void)setAPIKey:(NSString*)key;

/**
 *  Returns a string value of the Cloud API Key.
 *
 *  @return String value of API Key.
 *
 *  @see setAPIKey:
 */
+ (NSString*)APIKey;

/**
 *  Sets devices monitoring options.
 *
 *  @param options Devices monitoring options.
 */
+ (void)setMonitoringOptions:(KTKMonitoringOptions)options;

/**
 *  Returns devices monitoring options.
 * 
 *  Default value is KTKMonitoringOptionsBatteryStatus
 *
 *  @return Devices monitoring options.
 */
+ (KTKMonitoringOptions)monitoringOptions;

@end
