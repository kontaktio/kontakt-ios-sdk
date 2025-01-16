//  Copyright © 2024 Kontakt.io

@import Foundation;

typedef NS_ENUM(NSInteger, KTKGatewayWiFiProtocol) {
    /**
     *  WPA_PSK Wifi protocol type.
     */
    KTKGatewayWifiProtocolWPAPSK = 10,
    /**
     *  WPA_EAP WiFi protocol type.
     */
    KTKGatewayWifiProtocolWPAEAP = 11
};

@protocol KTKDeviceGatewayConfigurationType <NSObject>

/**
 *  WiFi SSID.
 */
@property (nonatomic, copy) NSString * _Nullable wifiSSID;

/**
 *  WiFi login.
 */
@property (nonatomic, copy) NSString * _Nullable wifiLogin;

/**
 *  WiFi password.
 */
@property (nonatomic, copy) NSString * _Nullable wifiPassword;

/**
 *  WiFi protocol.
 */
@property (nonatomic, assign) KTKGatewayWiFiProtocol wifiProtocol;

/**
 *  Gateway's API Key.
 */
@property (nonatomic, copy) NSString * _Nullable apiKey;

@end
