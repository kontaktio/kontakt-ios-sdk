Pod::Spec.new do |s|
  s.name                    = "KontaktSDK"
  s.version                 = "3.0.23"
  s.license                 = { :type => 'CC-ND', :file => 'LICENSE' }
  s.summary                 = "Kontakt.io SDK for iOS"
  s.homepage                = "http://kontakt.io"
  s.author                  = { "Kontakt.io" => "ios@kontakt.io" }

  s.module_name             = 'KontaktSDK'

  s.ios.deployment_target   = '9.0'

  s.ios.frameworks          = "UIKit", "Foundation", "SystemConfiguration", "MobileCoreServices", "CoreLocation", "CoreBluetooth"

  s.source = {
    :http    => "http://omg.kontakt.io.s3.amazonaws.com/ios/builds/kontakt-ios-sdk-#{s.version.to_s}.zip",
    :flatten => true
  }

  s.ios.vendored_frameworks = "Cocoapods/iOS/KontaktSDK.xcframework"

  s.requires_arc  = true
end
