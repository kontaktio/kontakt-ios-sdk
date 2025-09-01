//
//  KontaktSDK
//  Version: 6.2.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000 || __TV_OS_VERSION_MAX_ALLOWED >= 100000
#else
#define CBManagerState CBCentralManagerState
#define CBManagerStateUnknown CBCentralManagerStateUnknown
#define CBManagerStateResetting CBCentralManagerStateResetting
#define CBManagerStateUnsupported CBCentralManagerStateUnsupported
#define CBManagerStateUnauthorized CBCentralManagerStateUnauthorized
#define CBManagerStatePoweredOff CBCentralManagerStatePoweredOff
#define CBManagerStatePoweredOn CBCentralManagerStatePoweredOn
#endif

/**
 *  Device Connection Operation Types
 */
typedef NS_ENUM(NSInteger, KTKDeviceConnectionOperationType) {
    /**
     *  Type Unknown.
     */
    KTKDeviceConnectionOperationTypeUnknown = -1,
    /**
     *  Read Operation.
     */
    KTKDeviceConnectionOperationTypeRead    = 1,
    /**
     *  Write Operation.
     */
    KTKDeviceConnectionOperationTypeWrite   = 2,
    /**
     *  DFU Operation.
     */
    KTKDeviceConnectionOperationTypeDFU     = 3,
    /**
     *  Notification Operation.
     */
    KTKDeviceConnectionOperationTypeNotify     = 4
};

/**
 *  Method for writing/reading Secure Configuration Profile.
 */
typedef NS_ENUM(NSInteger, KTKConfigProfileReadWriteMethod) {
    /**
     *  Default method that uses stream characteristic.
     */
    KTKConfigProfileReadWriteMethodStreaming = 1,
    /**
     *  Legacy method for devices that don't support (or have problem with) stream characteristic.
     */
    KTKConfigProfileReadWriteMethodLegacy = 2
};

/**
 *  A Kontakt device type.
 */
typedef NS_ENUM(NSInteger, KTKDeviceType) {
    /**
     *  Invalid device type.
     */
    KTKDeviceTypeInvalid     = -1,
    /**
     *  Beacon device type.
     */
    KTKDeviceTypeBeacon      = 1,
    /**
     *  Cloud Beacon device type.
     */
    KTKDeviceTypeCloudBeacon = 2,
    /**
     *  Gateway device type.
     */
    KTKDeviceTypeGateway = 3

};

/**
 *  A Kontakt image type.
 */
typedef NS_ENUM(uint16_t, KTKKontaktImageType) {
    KTKKontaktImageRAW                     ,
    KTKKontaktImageRAWContinuous           ,
    KTKKontaktImageCalibration             ,
    KTKKontaktImageRecalibration
};

/**
 *  Legacy devices Advertising Profile
 */
typedef NS_ENUM(NSInteger, KTKDeviceAdvertisingProfile) {
    /**
     *  Invalid Profile.
     */
    KTKDeviceAdvertisingProfileInvalid   = -1,
    /**
     *  iBeacon Profile.
     */
    KTKDeviceAdvertisingProfileIBeacon   = 1,
    /**
     *  Eddystone Profile.
     */
    KTKDeviceAdvertisingProfileEddystone = 2
};

/**
 *  A device Advertising Packets
 */
typedef NS_OPTIONS(NSInteger, KTKDeviceAdvertisingPackets) {
    /**
     *  Invalid packet.
     */
    KTKDeviceAdvertisingPacketsInvalid         = 0,
    /**
     *  Eddystone UID packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneUID    = 1 << 0,
    /**
     *  Eddystone URL packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneURL    = 1 << 1,
    /**
     *  Eddystone Telemetry packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneTLM    = 1 << 2,
    /**
     *  iBeacon packet.
     */
    KTKDeviceAdvertisingPacketsIBeacon         = 1 << 3,
    /**
     *  Kontakt identification packet.
     */
    KTKDeviceAdvertisingPacketsKontakt         = 1 << 4,
    /**
     *  Eddystone ID packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneEID    = 1 << 5,
    /**
     *  Eddystone Telemetry packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneETLM   = 1 << 6,
    /**
     *  Kontakt identification packet.
     */
    KTKDeviceAdvertisingPacketsKontaktTLM      = 1 << 7,
    /**
     *  iBeacon Button packet.
     */
    KTKDeviceAdvertisingPacketsIBeaconButton   = 1 << 8,
    /**
     *  Kontakt Location packet.
     */
    KTKDeviceAdvertisingPacketsKontaktLocation = 1 << 9,
    /**
     *  Quuppa packet.
     */
    KTKDeviceAdvertisingPacketsQuuppa          = 1 << 10,
    /**
     *  TT Frame packet.
     */
    KTKDeviceAdvertisingPacketsTTFrame         = 1 << 11,
    /**
     *  Kontakt People Detection Frame packet.
     */
    KTKDeviceAdvertisingPacketsKontaktPeopleDetectionFrame   = 1 << 12,
    /**
     *  Signify / Phillips Beacon Broadcast packet.
     */
    KTKDeviceAdvertisingPacketsSignifyBeacon   = 1 << 14,
    
    /**
     *  All supprted Eddystone packets.
     */
    KTKDeviceAdvertisingPacketsEddystoneAll    = KTKDeviceAdvertisingPacketsEddystoneUID | KTKDeviceAdvertisingPacketsEddystoneURL | KTKDeviceAdvertisingPacketsEddystoneTLM,
    /**
     *  All supprted Eddystone Secure (EID + ETLM).
     */
    KTKDeviceAdvertisingPacketsEddystoneSecure = KTKDeviceAdvertisingPacketsEddystoneEID | KTKDeviceAdvertisingPacketsEddystoneETLM,
    /**
     *  All Kontakt packets
     */
    KTKDeviceAdvertisingPacketsKontaktAll = KTKDeviceAdvertisingPacketsKontakt | KTKDeviceAdvertisingPacketsKontaktLocation | KTKDeviceAdvertisingPacketsKontaktTLM,
    /**
     *  All supported packets.
     */
    KTKDeviceAdvertisingPacketsAll             = (NSInteger)0b111111111111111 // 15 flags
};

/**
 *  A device Telemetry Fields
 */
typedef NS_OPTIONS(uint32_t, KTKDeviceTelemetryFields) {
    /**
     *  Raw Accelerometer.
     */
    KTKDeviceTelemetryFieldsRawAccelerometer                = 1 << 0,
    /**
     *  Movement Threshold Event.
     */
    KTKDeviceTelemetryFieldsMovementThresholdEvent          = 1 << 1,
    /**
     *  Double Tap Event.
     */
    KTKDeviceTelemetryFieldsDoubleTapEvent                  = 1 << 2,
    /**
     *  Tap Event.
     */
    KTKDeviceTelemetryFieldsTapEvent                        = 1 << 3,
    /**
     *  Light Level.
     */
    KTKDeviceTelemetryFieldsLightLevel                      = 1 << 4, //
    /**
     *  Temperature.
     */
    KTKDeviceTelemetryFieldsTemperature                     = 1 << 5,
    /**
     *  Battery.
     */
    KTKDeviceTelemetryFieldsBattery                         = 1 << 6,
    /**
     *  Button Click.
     */
    KTKDeviceTelemetryFieldsButtonClick                     = 1 << 7,
    /**
     *  Button Double Click.
     */
    KTKDeviceTelemetryFieldsButtonDoubleClick               = 1 << 8,
    /**
     *  UTC Time.
     */
    KTKDeviceTelemetryFieldsUTCTime                         = 1 << 9,
    /**
     *  Logging Enabled.
     */
    KTKDeviceTelemetryFieldsLoggingEnabled                  = 1 << 10,
    /**
     *  Identified Button Click.
     */
    KTKDeviceTelemetryFieldsIdentifiedButtonClick           = 1 << 11,
    /**
     *  Humidity.
     */
    KTKDeviceTelemetryFieldsHumidity                        = 1 << 12,
    /**
     *  Temperature 16 bits.
     */
    KTKDeviceTelemetryFieldsTemperature16bits               = 1 << 13,
    /**
     *  BLE channel.
     */
    KTKDeviceTelemetryFieldsBLEChannel                      = 1 << 14,
    /**
     *  Gpio. - depricate
     */
    KTKDeviceTelemetryFieldsGpio                            = 1 << 15,
    /**
     *  Movement event.
     */
    KTKDeviceTelemetryFieldsMovementEvent                   = 1 << 16,
    /**
     *  Air Pressure.
     */
    KTKDeviceTelemetryFieldsAirPressure                     = 1 << 17,
    /**
     *  PIR detection.
     */
    KTKDeviceTelemetryFieldsPIRDetection                    = 1 << 18,
    /**
     *  Two button info.
     */
    KTKDeviceTelemetryFieldsTwoButtonInfo                   = 1 << 19, //
    /**
     *  Air Quality.
     */
    KTKDeviceTelemetryFieldsAirQuality                      = 1 << 20,
    /**
     *  Room number.
     */
    KTKDeviceTelemetryFieldsRoomNumber                      = 1 << 21,
    /**
     *  Occupancy.
     */
    KTKDeviceTelemetryFieldsOccupancy                       = 1 << 22,
    /**
     *  BLE scan result.
     */
    KTKDeviceTelemetryFieldsBLEScanResult                   = 1 << 23,

    /**
     *  Proximity report.
     */
    KTKDeviceTelemetryFieldsProximityReport                 = 1 << 24,

    /**
     *  Gas Sensor.
     */
    KTKDeviceTelemetryFieldsGasSensor                       = 1 << 25,

    /**
     *  Light level lux.
     */
    KTKDeviceTelemetryFieldsLightLevelLux                   = 1 << 26,

    /**
     *  Inout counter.
     */
    KTKDeviceTelemetryFieldsInOutCount                      = 1 << 27,

    /**
     *  Soap dispenser.
     */
    KTKDeviceTelemetryFieldsSoapDispenser                   = 1 << 28,

    /**
     *  People Detection.
     */
    KTKDeviceTelemetryFieldsPeopleDetection                 = 1 << 29,

    /**
     *  RSSI Scan.
     */
    KTKDeviceTelemetryFieldsRSSIScan                        = 1 << 30,

    /**
     *  IR scan statistics.
     */
    KTKDeviceTelemetryFieldsIRStats                         = 1 << 31,

    /**
     *  All supported packets.
     */
    KTKDeviceTelemetryFieldsAll                             = 0b01111111111111111111111111111111
};

/**
 *  A device access rights.
 */
typedef NS_ENUM(NSInteger, KTKDeviceAccess) {
    /**
     *  Invalid value.
     */
    KTKDeviceAccessInvalid   = -1,
    /**
     *  Owner
     */
    KTKDeviceAccessOwner      = 1,
    /**
     *  Supervisor
     */
    KTKDeviceAccessSupervisor = 2,
    /**
     *  Editor
     */
    KTKDeviceAccessEditor     = 3,
    /**
     *  Viewer
     */
    KTKDeviceAccessViewer     = 4
};

/**
 *  A kontakt device specification.
 */
typedef NS_ENUM(NSInteger, KTKDeviceSpecification) {
    /**
     *  Invalid value.
     */
    KTKDeviceSpecificationInvalid  = -1,
    /**
     *  Standard specification.
     */
    KTKDeviceSpecificationStandard = 1,
    /**
     *  Tough Beacon specification.
     */
    KTKDeviceSpecificationTough = 2
};

/**
 *  Known device models. For legacy devices, symbol is included in parenthesis
 */
typedef NS_ENUM(NSInteger, KTKDeviceModel) {
    /**
     *  Invalid value / unsupported, outdated model
     */
    KTKDeviceModelInvalid  = -1,
    /**
     *  Cloud Beacon (GW14-1)
     */
    KTKDeviceModelCloudBeacon = -1,
    /**
     *  Unknown model
     */
    KTKDeviceModelUnknown  = 0,
    /**
     *  Smart Beacon (SB16-2)
     */
    KTKDeviceModelSmartBeacon = 1,
    /**
     *  Tough Beacon, Mini Tag (TB15-1)
     */
    KTKDeviceModelToughBeacon = 1,
    /**
     *  Smart Sensor Beacon, Accelerometer Beacon for Blueanker (SB13-1, AB15-1)
     */
    KTKDeviceModelSmartSensorBeacon = 2,
    /**
     *  USB Beacon (UB16-2)
     */
    KTKDeviceModelUSBBeacon = 3,
    /**
     *  Card Tag (CT16-2)
     */
    KTKDeviceModelCardBeacon = 4,
    /**
     *  Gateway (GW16-2)
     */
    KTKDeviceModelGateway = 5,
    /**
     *  Beacon Pro (BP16-3)
     */
    KTKDeviceModelProBeacon = 6,
    /**
     *  Probe
     */
    KTKDeviceModelProbe = 7,
    /**
     *  Asset Tag, Tag Beacon (S18-3)
     */
    KTKDeviceModelAssetTag = 8,
    /**
     *  Anchor Beacon, Smart Beacon 3 (SB18-3)
     */
    KTKDeviceModelAnchorBeacon = 9,
    /**
     *  Heavy Duty Beacon (HD18-3)
     */
    KTKDeviceModelHeavyDutyBeacon = 10,
    /**
     *  Card Tag, Card Beacon 2 (CT18-3)
     */
    KTKDeviceModelCardBeacon2 = 11,
    /**
     *  Coin Tag, Coin Beacon (C18-3)
     */
    KTKDeviceModelCoinTag = 12,
    /**
     *  Humidity Beacon, Smart Beacon 3H (SB18-3H)
     */
    KTKDeviceModelSmartBeacon3H = 13,
    /**
     * Tough Beacon 2 (TB18-2)
     */
    KTKDeviceModelToughBeacon2 = 14,
    /**
     *  Bracelet Tag (BT18-3)
     */
    KTKDeviceModelBraceletTag = 15,
    /**
     *  Universal Tag (UT19-1)
     */
    KTKDeviceModelUniversalTag = 16,
    /**
     *  Bracelet Tag 2 (BT19-4)
     */
    KTKDeviceModelBraceletTag2 = 17,
    /**
     *  Mobile devices (emulated beacon)
     */
    KTKDeviceModelMobileDevices = 18,
    /**
     *  TT Beacon, Custom Beacon, Puck Beacon (TT20-1)
     */
    KTKDeviceModelTT20 = 19,
    /**
     *  Minew E5 (M-E5)
     */
    KTKDeviceModelMinewE5 = 20,
    /**
     *  Minew E7 (M-E7)
     */
    KTKDeviceModelMinewE7 = 21,
    /**
     *  Minew E8 (M-E8)
     */
    KTKDeviceModelMinewE8 = 22,
    /**
     *  Minew i3 (M-i3)
     */
    KTKDeviceModelMinewI3 = 23,
    /**
     *  Minew i7 (M-i7)
     */
    KTKDeviceModelMinewI7 = 24,
    /**
     *  Minew S1 (M-S1)
     */
    KTKDeviceModelMinewS1 = 25,
    /**
     *  Lanyard Tag (LB20-1)
     */
    KTKDeviceModelLanyardTag = 26,
    /**
     *  Nano Tag, Wristband Tag (BT20-1)
     */
    KTKDeviceModelNanoTag = 27,
    /**
     *  Puck Beacon, Puck Tag (PB20-1)
     */
    KTKDeviceModelPuckBeacon = 28,
    /**
     *  Portal Light (GW20-1)
     */
    KTKDeviceModelPortalLight = 29,
    /**
     *  Smart Badge
     */
    KTKDeviceModelSmartBadge = 30,
    /**
     *  Portal Beam
     */
    KTKDeviceModelPortalBeam = 31,
    /**
     *  Nano Series
     */
    KTKDeviceModelNanoSeries = 32,
    /**
     *  Asset Tag 2
     */
    KTKDeviceModelAssetTag2 = 33,
    /**
     *  Anchor Beacon 2
     */
    KTKDeviceModelAnchorBeacon2 = 34,
    /**
     *  Beam Mini
     */
    KTKDeviceModelMiniBeam = 35,
    /**
     *  Portal Beam IR
     */
    KTKDeviceModelPortalBeamIR = 36,
    /**
     *  Dispenser Beacon
     */
    KTKDeviceModelDispenserBeacon = 37,
    /**
     *  Portal Light 2 IR
     */
    KTKDeviceModelPortalLight2S = 38,
    /**
     *  Portal Light 2
     */
    KTKDeviceModelPortalLight2 = 39,
    /**
     *  Asset Tag 2 Mini
     */
    KTKDeviceModelAssetTag2Mini = 40,
    /**
     *  Blueberry dongle
     */
    KTKDeviceModelBlueberryDongle = 41,
    /**
     *  Sticker Tag
     */
    KTKDeviceModelStickerTag = 42,
    /**
     * Nano Tag IR
     */
    KTKDeviceModelNanoTagIR = 43,
    /**
     * Autoclave beacon
     */
    KTKDeviceModelAutoclaveBeacon = 44,
    /**
     *  Nano Tag 2
     */
    KTKDeviceModelNanoTag2 = 45,
    /**
     *  Beam Mini 2
     */
    KTKDeviceModelMiniBeam2 = 46,
    /**
     *  Temperature Monitor Pro
     */
    KTKDeviceModelTemperatureMonitorPro = 47,
    /**
     *  Smart Badge 3 Mini
     */
    KTKDeviceModelSmartBadge3Mini = 48,
    /**
     *  Temperature Monitor Lite
     */
    KTKDeviceModelTemperatureMonitorLite = 49,

    /**
     *  A special 'model' used internally to check supported models number range.
     *  This case should always have a higher value by 1 than the last supported model.
     */
    KTKDeviceModelUnsupported = 50,

    /**
     *  Partner devices
     */
    KTKDeviceModelPartnerDevice = 128
};

/**
 *  A kontakt device channels status.
 */
typedef NS_ENUM(NSInteger, KTKDeviceBLEChannel) {
    /**
     *  Channel is unknown.
     */
    KTKDeviceBLEChannelUnknown        = -1,
    /**
     *  Device supported all channels.
     */
    KTKDeviceBLEChannelALL          = 0,
    /**
     *  Device status is channel 37.
     */
    KTKDeviceBLEChannel37            = 37,
    /**
     *  Device status is channel 38.
     */
    KTKDeviceBLEChannel38            = 38,

    /**
     *  Device status is channel 39.
     */
    KTKDeviceBLEChannel39            = 39
};

/**
 *  A kontakt device filtering Class.
 */
typedef NS_ENUM(NSInteger, KTKDeviceFilteringClass) {
    /**
     *  Class is unknown.
     */
    KTKDeviceFilteringClassUnknown        = -1,
    /**
     *  Device status flitering class  Kontakt.
     */
    KTKDeviceFilteringClassKtk           = 1,
    /**
     *  Device status flitering class  iBeacon, Eddystone, Kontakt .
     */
    KTKDeviceFilteringClassIbEidKtk      = 7,
    /**
     *  Device supported all classes.
     */
    KTKDeviceFilteringClassALL           = 15
};

/**
 *  A kontakt device shuffle status.
 */
typedef NS_ENUM(NSInteger, KTKDeviceShuffleStatus) {
    /**
     *  Status is unknown.
     */
    KTKDeviceShuffleStatusUnknown        = -1,
    /**
     *  Device shuffle is not supported.
     */
    KTKDeviceShuffleStatusNotSupported  = 0,
    /**
     *  Device shuffle status is ON.
     */
    KTKDeviceShuffleStatusON            = 1,
    /**
     *  Device shuffle status is OFF.
     */
    KTKDeviceShuffleStatusOFF           = 2
};

/**
 *  A device transmission power level.
 *
 *  @see https://support.kontakt.io/hc/en-gb/articles/201621521-Transmission-power-settings
 */
typedef NS_ENUM(NSInteger, KTKDeviceTransmissionPower) {
    /**
     *  Invalid value
     */
    KTKDeviceTransmissionPowerInvalid = -1,
    /**
     *  Transmission power level 0 (-30dBm).
     */
    KTKDeviceTransmissionPower0,
    /**
     *  Transmission power level 1 (-20dBm).
     */
    KTKDeviceTransmissionPower1,
    /**
     *  Transmission power level 2 (-16dBm).
     */
    KTKDeviceTransmissionPower2,
    /**
     *  Transmission power level 3 (-12dBm).
     */
    KTKDeviceTransmissionPower3,
    /**
     *  Transmission power level 4 (-8dBm).
     */
    KTKDeviceTransmissionPower4,
    /**
     *  Transmission power level 5 (-4dBm).
     */
    KTKDeviceTransmissionPower5,
    /**
     *  Transmission power level 6 (0dBm).
     */
    KTKDeviceTransmissionPower6,
    /**
     *  Transmission power level 7 (4dBm).
     */
    KTKDeviceTransmissionPower7,
};

/**
 *  A device motion detection modes.
 */
typedef NS_ENUM(NSInteger, KTKDeviceMotionDetectionMode) {
    /**
     *  Invalid mode.
     */
    KTKDeviceMotionDetectionModeInvalid  = -1,
    /**
     *  Motion detection is off.
     */
    KTKDeviceMotionDetectionModeOff      = 0,
    /**
     *  Motion detection is set in counting mode.
     *
     *  You can access counter value by reading device configuration.
     *
     *  @see [KTKDeviceConfiguration motionCounter]
     */
    KTKDeviceMotionDetectionModeCounting = 1,
    /**
     *  Motion detection is set in alarm mode.
     *
     *  When motion is detected device will advertise `4b6f6e74-616b-742e-696f-4d6f74696f6e` proximity UUID.
     *  Major and minor values will remain the same.
     */
    KTKDeviceMotionDetectionModeAlarm    = 2
};

typedef NS_ENUM(NSInteger, KTKDeviceOccupancyModel) {
    /**
     *  Invalid mode.
     */
    KTKDeviceOccupancyModeInvalid  = -1,
    /**
     *  Occupancy Mode is occupancy 1.
     */
    KTKDeviceOccupancyModeOccupancy1     = 0,
    /**
     *  Occupancy Mode is occupancy 2.
     */

    KTKDeviceOccupancyModeOccupancy2    =  1,
    /**
     *  MOccupancy Mode is footfall door.
     */

    KTKDeviceOccupancyModeFootfallDoor = 2,
    /**
     *  Occupancy Mode is footfall corridor.
     */
    KTKDeviceOccupancyModeFootfallCorridor    = 3
};

/**
 *  A device data logger fields.
 */
typedef NS_OPTIONS(uint32_t, KTKDeviceDataLoggerFields) {
    KTKDeviceDataLoggerFieldsTemperature8   = 1 << 0,
    KTKDeviceDataLoggerFieldsTemperature16  = 1 << 1,
    KTKDeviceDataLoggerFieldsHumidity       = 1 << 2,
    KTKDeviceDataLoggerFieldsLightLevel     = 1 << 3,
    KTKDeviceDataLoggerFieldsAccelerometer  = 1 << 4,
    KTKDeviceDataLoggerFieldsDebugCounter   = 1 << 5,
    KTKDeviceDataLoggerFieldsTimestamp      = 1 << 6,
    KTKDeviceDataLoggerFieldsBattery        = 1 << 7,
};

/**
 *  A kontakt GPIO state options.
 */
typedef NS_ENUM(int8_t, KTKGPIOState) {
    KTKGPIOStateOff = -1,
    KTKGPIOStateLow,
    KTKGPIOStateHigh,
    KTKGPIOStateInput,
};

/**
 *  A kontakt device GPIOs states.
 */
struct KTKNearbyDeviceGPIOStates {
    KTKGPIOState pin[8];
};

/**
 *  A device acceleration structure.
 */
typedef struct {
    int8_t x;
    int8_t y;
    int8_t z;
} KTKDeviceAcceleration;

/**
 *  Gateway properties bitmask
 */
typedef NS_OPTIONS(uint16_t, KTKGatewayProperties) {
    KTKGatewayPropertyWiFi        = 1 << 0,
    KTKGatewayPropertyIP          = 1 << 1,
    KTKGatewayPropertyNTP         = 1 << 2,
    KTKGatewayPropertyProvisioned = 1 << 3,
    KTKGatewayPropertyDMConn      = 1 << 4,
    KTKGatewayPropertyDataConn    = 1 << 5,
    KTKGatewayPropertyFallback    = 1 << 6,
    KTKGatewayPropertyOTA         = 1 << 7,
    KTKGatewayPropertyError       = 1 << 8,
    KTKGatewayPropertyBusy        = 1 << 9
};

/**
 *  Gateway info frame
 */
typedef struct {
    int8_t bleRSSIMin;
    int8_t bleRSSIAvg;
    int8_t bleRSSIMax;
    uint8_t bleInRate;
    int8_t wifiRSSI;
    uint8_t wifiChannel;
    KTKGatewayProperties gwProperties;
    uint8_t uptime;
    uint8_t noConnTime;
} KTKGatewayInfo;
