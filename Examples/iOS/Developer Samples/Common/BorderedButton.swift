//
//  BorderedButton.swift
//  Developer Samples
//
//  Created by Szymon Bobowiec on 21.12.2016.
//  Copyright © 2016 kontakt.io. All rights reserved.
//

import UIKit

class BorderedButton: UIButton {
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setupView()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        setupView()
    }
    
    private func setupView() {
        layer.borderColor = tintColor.cgColor
        layer.borderWidth = 1
        layer.cornerRadius = 5
        
        contentEdgeInsets = UIEdgeInsets(top: 10, left: 15, bottom: 10, right: 15)
    }
}
