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
};

#endif /* Config_h */
