//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"

#import "KTKCloudModel.h"
#import "KTKDeviceConfiguration.h"

@interface KTKDevice : NSObject <KTKCloudModel>

@property (nonatomic, strong, readonly) NSString *uniqueID;

@property (nonatomic, strong, readonly) NSUUID *secureProximity;
@property (nonatomic, strong, readonly) NSString *secureNamespace;

@property (nonatomic, strong, readonly) KTKDeviceConfiguration *currentConfiguration;

@property (nonatomic, strong, readonly) NSString *alias;
@property (nonatomic, strong, readonly) NSDictionary *meta;
@property (nonatomic, strong, readonly) NSString *firmwareVersion;

@property (nonatomic, assign, readonly) KTKDeviceType type;
@property (nonatomic, assign, readonly) KTKDeviceSpecification specification;

@property (nonatomic, strong, readonly) NSUUID *managerID;
@property (nonatomic, assign, readonly) KTKDeviceAccess access;

@property (nonatomic, strong, readwrite) NSNumber *latitude;
@property (nonatomic, strong, readwrite) NSNumber *longitude;

@end
