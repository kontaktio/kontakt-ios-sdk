Pod::Spec.new do |s|
  s.name                    = "KontaktSDK"
  s.version                 = "1.0.4"
  s.license                 = { :type => 'CC-ND', :file => 'LICENSE' }
  s.summary                 = "iOS library for Kontakt.io devices"
  s.homepage                = "http://kontakt.io"
  s.author                  = { "Kontakt.io" => "ios@kontakt.io" }
  s.platform                = :ios
  s.source                  = { :git => "https://github.com/kontaktio/kontakt-ios-sdk.git", :tag => "v#{s.version}" }
  s.source_files            = "KontaktSDK/KontaktSDK.framework/Headers/*.h"
  s.vendored_frameworks     = "KontaktSDK/KontaktSDK.framework"
  s.ios.deployment_target   = "8.0"
  s.frameworks              = "UIKit", "Foundation", "SystemConfiguration", "MobileCoreServices", "CoreLocation", "CoreBluetooth"
  s.requires_arc            = true
  s.xcconfig                = { "LIBRARY_SEARCH_PATHS" => '"$(PODS_ROOT)/KontaktSDK"',
                                "HEADER_SEARCH_PATHS"  => '"${PODS_ROOT}/Headers/KontaktSDK"' }
end
