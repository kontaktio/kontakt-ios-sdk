//
//  KontaktSDK
//  Version: 6.2.1
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

// Config Service
static NSString * const KTKDeviceServiceConfig                       = @"A1EA81F0-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicConfigRequest         = @"A1EA81F1-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicConfigResponse        = @"A1EA81F2-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicConfigToken           = @"A1EA81F3-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicConfigControlPoint    = @"A1EA81F4-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicConfigStream          = @"A1EA81F5-0E1B-D4A1-B840-63F88C8DA1EA";

// Kontakt.io DFU Profile
static NSString * const KTKDeviceServiceDFUProfile                   = @"1B314D70-6C97-43FC-B5DD-3D0E125E15FB";
static NSString * const KTKDeviceCharacteristicDFUCommand            = @"1B314D71-6C97-43FC-B5DD-3D0E125E15FB";
static NSString * const KTKDeviceCharacteristicDFUResponse           = @"1B314D72-6C97-43FC-B5DD-3D0E125E15FB";
static NSString * const KTKDeviceCharacteristicDFUData               = @"1B314D73-6C97-43FC-B5DD-3D0E125E15FB";

// Proximity Service
static NSString * const KTKDeviceServiceProximity                    = @"A1EA8110-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicProximityUUID         = @"A1EA8111-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicMajor                 = @"A1EA8112-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicMinor                 = @"A1EA8113-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicName                  = @"A1EA8114-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicUniqueID              = @"A1EA8115-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicTXPower1m             = @"A1EA8116-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicNamespaceID           = @"A1EA8117-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicInstanceID            = @"A1EA8118-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicURL                   = @"A1EA8119-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicTXPower0m             = @"A1EA811A-0E1B-D4A1-B840-63F88C8DA1EA";

// Timing Service
static NSString * const KTKDeviceServiceTiming                       = @"A1EA8120-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicAdvertisingInterval   = @"A1EA8121-0E1B-D4A1-B840-63F88C8DA1EA";

// Control Service
static NSString * const KTKDeviceServiceControl                      = @"A1EA8130-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicPassword              = @"A1EA8131-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicSetPassword           = @"A1EA8132-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicReset                 = @"A1EA8133-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicDefaults              = @"A1EA8134-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicBootloader            = @"A1EA8135-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicNonConnectable        = @"A1EA8136-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicMasterPassword        = @"A1EA8137-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicShuffleInterval       = @"A1EA8138-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicShufflePassword       = @"A1EA8139-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicActiveProfile         = @"A1EA813A-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicShuffleVector         = @"A1EA813B-0E1B-D4A1-B840-63F88C8DA1EA";

static NSString * const KTKDeviceCharacteristicMotionDetectMode      = @"A1EA913B-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicMotionDetectThreshold = @"A1EA913C-0E1B-D4A1-B840-63F88C8DA1EA";
static NSString * const KTKDeviceCharacteristicMotionCounter         = @"A1EA913D-0E1B-D4A1-B840-63F88C8DA1EA";

// TX Power Service
static NSString * const KTKDeviceServiceTXPower                      = @"1804";
static NSString * const KTKDeviceCharacteristicTXPowerLevel          = @"2A07";

// Device Information Service
static NSString * const KTKDeviceServiceDeviceInformation            = @"180A";
static NSString * const KTKDeviceCharacteristicManufacturer          = @"2A29";
static NSString * const KTKDeviceCharacteristicHardware              = @"2A27";
static NSString * const KTKDeviceCharacteristicFirmware              = @"2A26";
static NSString * const KTKDeviceCharacteristicMAC                   = @"2A25";

// Diagnostic service description
static NSString * const KTKDeviceServiceDeviceDiagnostic             = @"469DCA90-0C88-019F-1A4B-595F74CAA04F";
static NSString * const KTKDeviceCharacteristicDeviceDiagnostic      = @"469DCA91-0C88-019F-1A4B-595F74CAA04F";
static NSString * const KTKDeviceCharacteristicUserDescription       = @"0x2901";
static NSString * const KTKDeviceCharacteristicCommandAndControl     = @"469DCA93-0C88-019F-1A4B-595F74CAA04F";

// Battery Service
static NSString * const KTKDeviceServiceBattery                      = @"180F";
static NSString * const KTKDeviceCharacteristicBatteryLevel          = @"2A19";

// Time Service
static NSString * const KTKDeviceServiceTime                         = @"1805";
static NSString * const KTKDeviceCharacteristicCurrentTime           = @"2A2B";

// Seen Networks Service
static NSString * const KTKDeviceServiceWiFiNetworks                 = @"F533EF57-7ED3-4098-A926-A7F86024F0E4";
static NSString * const KTKDeviceCharacteristicWiFiNetworksCount     = @"F533EF58-7ED3-4098-A926-A7F86024F0E4";
static NSString * const KTKDeviceCharacteristicWiFiNetworksIndex     = @"F533EF59-7ED3-4098-A926-A7F86024F0E4";
static NSString * const KTKDeviceCharacteristicWiFiNetworksDetails   = @"F533EF5A-7ED3-4098-A926-A7F86024F0E4";

// Sensors Service
static NSString * const KTKDeviceServiceSensors                      = @"E04A8F70-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicSensorData            = @"E04A8F73-D020-FC8E-4F45-C2E225FCAF89";
// DEPRECATED
static NSString * const KTKDeviceCharacteristicSensorLight           = @"E04A8F71-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicSensorTemperature     = @"E04A8F72-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicSensorLoggerData      = @"E04A8F73-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicSensorLoggerCommand   = @"E04A8F74-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicSensorGPIOState       = @"E04A8F75-D020-FC8E-4F45-C2E225FCAF89";

// Downlading pictures
static NSString * const KTKDeviceServiceImage                        = @"E04A8F70-D020-FC8E-4F45-C2E225FCAF89";
static NSString * const KTKDeviceCharacteristicImage                 = @"E04A8F73-D020-FC8E-4F45-C2E225FCAF89";

// Accident Service
static NSString * const KTKDeviceServiceAccident                     = @"D03E2019-3F42-C596-AC46-53759AB7CE80";
static NSString * const KTKDeviceCharacteristicAccidentData          = @"D03E2020-3F42-C596-AC46-53759AB7CE80";
