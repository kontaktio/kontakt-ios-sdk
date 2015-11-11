//
//  KontaktSDK
//  Version: 0.9.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"

typedef NS_ENUM(NSUInteger, KTKManagerRole) {
    KTKManagerRoleUnknown,
    KTKManagerRoleSuperuser,
    KTKManagerRoleAdmin,
    KTKManagerRoleOperator,
};

@interface KTKManager : NSObject <KTKCloudModel>

@property (nonatomic, strong, readonly) NSUUID *managerID;
@property (nonatomic, strong, readonly) NSUUID *supervisorID;
@property (nonatomic, strong, readonly) NSString *firstName;
@property (nonatomic, strong, readonly) NSString *lastName;
@property (nonatomic, strong, readonly) NSString *email;
@property (nonatomic, strong, readonly) NSString *apiKey;
@property (nonatomic, assign, readonly) KTKManagerRole role;

@end
