//
//  UIColor+Kontakt.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 24.01.2017.
//  Copyright © 2017 kontakt.io. All rights reserved.
//

import UIKit

public extension UIColor {

    fileprivate class func RGB(_ r: CGFloat, _ g: CGFloat, _ b: CGFloat) -> UIColor {
        return UIColor(red: (r/255.0), green: (g/255.0), blue: (b/255.0), alpha:1.0)
    }
    
    /* Main Brand Colors */
    public class var kontaktMainGreen: UIColor {
        return .RGB(96, 187, 70)
    }
    
    public class var kontaktMainGray: UIColor {
        return .RGB(50, 54, 64)
    }
    
    public class var kontaktMainDarkBlue: UIColor {
        return .RGB(16, 35, 102)
    }
    
    /* Reds */
    public class var kontaktLightRed: UIColor {
        return .RGB(239, 75, 75)
    }
    
    public class var kontaktRed: UIColor {
        return .RGB(207, 36, 42)
    }
    
    public class var kontaktDarkRed: UIColor {
        return .RGB(177, 25, 29)
    }
    
    /* Gray */
    public class var kontaktUltraLightGray: UIColor {
        return .RGB(246, 247, 248)
    }
    
    public class var kontaktLightGray: UIColor {
        return UIColor(red:0.93, green:0.93, blue:0.93, alpha:1)
    }
    
    public class var kontaktMediumGray: UIColor {
        return UIColor(red:0.59, green:0.60, blue:0.66, alpha:1.0)
    }
    
    public class var kontaktDarkGray: UIColor {
        return UIColor(red:0.51, green:0.51, blue:0.51, alpha:1.0)
    }
    
    public class var kontaktDarkestGray: UIColor {
        return UIColor(red:0.4, green:0.4, blue:0.4, alpha:1.0)
    }
    
}
