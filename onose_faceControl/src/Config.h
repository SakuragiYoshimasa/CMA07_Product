//
//  Config.h
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#ifndef Config_h
#define Config_h

#include <stdio.h>

class Config{
public:
    Config();
    ~Config(){};
    
    const int camWidth = 640;
    const int camHeight = 480;
    
    const float mouseOpenedHeightThreshold = 3.0;
    const float faceOriXThreshold = 0.3;
    const float faceOriYThreshold = 0.2;
    const float faceOriZThreshold = 0.2;
    
    const int channel = 2;
    
};

#endif /* Config_h */
