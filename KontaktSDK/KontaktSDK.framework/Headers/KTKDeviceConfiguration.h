//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"
#import "KTKCloudModel.h"

#pragma mark - KTKDeviceConfiguration (Interface)
@interface KTKDeviceConfiguration : NSObject <KTKCloudModel>

@property (nonatomic, copy, readonly) NSString *uniqueID;
@property (nonatomic, copy, readwrite) NSString *name;
@property (nonatomic, copy, readwrite) NSString *password;

@property (nonatomic, assign, readwrite, getter=isShuffled) BOOL shuffled;

@property (nonatomic, assign, readwrite) KTKDeviceTransmissionPower transmissionPower;
@property (nonatomic, assign, readwrite) KTKDeviceAdvertisingProfile profile;
@property (nonatomic, strong, readwrite) NSNumber *advertisingInterval;

/* iBeacon */
@property (nonatomic, copy, readwrite) NSUUID *proximityUUID;
@property (nonatomic, strong, readwrite) NSNumber *major;
@property (nonatomic, strong, readwrite) NSNumber *minor;

/* Eddystone */
@property (nonatomic, copy, readwrite) NSString *instanceID;
@property (nonatomic, copy, readwrite) NSString *namespaceID;
@property (nonatomic, copy, readwrite) NSURL *URL;

@end
