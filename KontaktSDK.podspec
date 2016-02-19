Pod::Spec.new do |s|
  s.name                    = "KontaktSDK"
  s.version                 = "1.0.8"
  s.license                 = { :type => 'CC-ND', :file => 'LICENSE' }
  s.summary                 = "Kontakt.io iOS SDK"
  s.homepage                = "http://kontakt.io"
  s.author                  = { "Kontakt.io" => "ios@kontakt.io" }

  s.source = {
    :http    => "http://omg.kontakt.io.s3.amazonaws.com/ios/builds/kontakt-ios-sdk-#{s.version.to_s}.zip",
    :flatten => true
  }

  s.vendored_frameworks     = "KontaktSDK.framework"
  s.module_name             = 'KontaktSDK'

  s.platform                = :ios
  s.ios.deployment_target   = "8.0"
  s.frameworks              = "UIKit", "Foundation", "SystemConfiguration", "MobileCoreServices", "CoreLocation", "CoreBluetooth"

  s.requires_arc            = true
end
