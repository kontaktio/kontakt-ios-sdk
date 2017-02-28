//
//  DualStateButton.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 25.01.2017.
//  Copyright © 2017 kontakt.io. All rights reserved.
//

import UIKit

typealias KVOContext = UInt8
private var stateObservingContext = KVOContext()

class LaunchButton: BorderedButton {

    enum State : UInt {
        case Start = 8
        case Stop = 16
    }
    
    let stateKey = "state_key"
    
    var currentState = State.Start
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    deinit {
        removeObserver(self, forKeyPath: stateKey)
    }
    
    override var state: UIControlState {
        return UIControlState(rawValue: (super.state.rawValue | currentState.rawValue))
    }
    
    override func awakeFromNib() {
        let uiControlStateStart = UIControlState(rawValue: State.Start.rawValue)
        let uiControlStateStop = UIControlState(rawValue: State.Stop.rawValue)
        
        self.setBackgroundColor(color: UIColor.kontaktMainDarkBlue, forState: uiControlStateStart)
        self.setBackgroundColor(color: UIColor.white, forState: uiControlStateStop)
        
        self.setTitle("START", for: uiControlStateStart)
        self.setTitle("STOP", for: uiControlStateStop)
        
        self.setTitleColor(UIColor.white, for: uiControlStateStart)
        self.setTitleColor(UIColor.kontaktMainDarkBlue, for: uiControlStateStop)
        
        self.layer.borderColor = UIColor.kontaktMainDarkBlue.cgColor
        
        self.addObserver(self, forKeyPath: stateKey, options: .old, context: &stateObservingContext)
    }
    
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        if &stateObservingContext == context {
            if let oldState = change?[.oldKey] as? UInt {
                if currentState.rawValue != oldState {
                    self.layoutSubviews()
                }
            }
        } else {
            super.observeValue(forKeyPath: keyPath, of: object, change: change, context: context)
        }
    }
    
}

extension LaunchButton {
    
    func setBackgroundColor(color: UIColor, forState: UIControlState) {
        // Generate Image
        UIGraphicsBeginImageContext(CGSize(width: 1, height: 1))
        UIGraphicsGetCurrentContext()!.setFillColor(color.cgColor)
        UIGraphicsGetCurrentContext()!.fill(CGRect(x: 0, y: 0, width: 1, height: 1))
        let colorImage = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        
        // Set Background Image
        self.setBackgroundImage(colorImage, for: forState)
        
        // Set clip to bounds for visible corners
        self.clipsToBounds = true
    }
}
