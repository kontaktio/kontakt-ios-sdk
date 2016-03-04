//
//  KontaktSDK
//  Version: 1.1.3
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceCredentials (Interface)
@interface KTKDeviceCredentials : NSObject <KTKCloudModel>

#pragma mark - Namespace Properties
///--------------------------------------------------------------------
/// @name Namespace Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *uniqueID;

/**
 *  A Kontakt device's password. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *password;

/**
 *  A Kontakt device's master password. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *masterPassword;

@end

NS_ASSUME_NONNULL_END
