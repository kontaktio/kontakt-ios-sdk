Pod::Spec.new do |s|
  s.name                    = "KontaktSDK"
  s.version                 = "1.1.0"
  s.license                 = { :type => 'CC-ND', :file => 'LICENSE' }
  s.summary                 = "Kontakt.io SDK for iOS, tvOS and OSX"
  s.homepage                = "http://kontakt.io"
  s.author                  = { "Kontakt.io" => "ios@kontakt.io" }

  s.module_name             = 'KontaktSDK'

  s.ios.deployment_target   = '8.0'
  s.osx.deployment_target   = '10.9'
  s.tvos.deployment_target  = '9.0'

  s.ios.frameworks          = "UIKit", "Foundation", "SystemConfiguration", "MobileCoreServices", "CoreLocation", "CoreBluetooth"
  s.tvos.frameworks         = "UIKit", "Foundation", "SystemConfiguration", "MobileCoreServices", "CoreLocation", "CoreBluetooth"
  s.osx.frameworks          = "AppKit", "Foundation", "SystemConfiguration", "CoreServices", "CoreBluetooth"

  s.ios.source = {
    :http    => "http://omg.kontakt.io.s3.amazonaws.com/ios/builds/kontakt-ios-sdk-#{s.version.to_s}-iOS.zip",
    :flatten => true
  }

  s.ios.vendored_frameworks = "Cocoapods/iOS/KontaktSDK.framework"
  s.ios.public_header_files = 'Cocoapods/iOS/KontaktSDK.framework/Headers/*.h'

  s.tvos.source = {
    :http    => "http://omg.kontakt.io.s3.amazonaws.com/ios/builds/kontakt-ios-sdk-#{s.version.to_s}-tvOS.zip",
    :flatten => true
  }

  s.tvos.vendored_frameworks = "Cocoapods/tvOS/KontaktSDK.framework"
  s.tvos.public_header_files = 'Cocoapods/tvOS/KontaktSDK.framework/Headers/*.h'

  s.osx.source = {
    :http    => "http://omg.kontakt.io.s3.amazonaws.com/ios/builds/kontakt-ios-sdk-#{s.version.to_s}-OSX.zip",
    :flatten => true
  }

  s.osx.vendored_frameworks = "Cocoapods/OSX/KontaktSDK.framework"
  s.osx.public_header_files = 'Cocoapods/OSX/KontaktSDK.framework/Versions/A/Headers/*.h'

  s.requires_arc  = true
end
