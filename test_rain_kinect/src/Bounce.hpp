//
//  Bounce.hpp
//  BouncingWater
//
//  Created by 片山怜 on 2016/02/24.
//
//

#ifndef Bounce_hpp
#define Bounce_hpp

#include <stdio.h>
#include "ofMain.h"

class Bounce{
    
public:
    Bounce();
    void update();
    void draw();
    
    static const int NUM = 30;
    
    float loc_x[NUM];
    float loc_y[NUM];
    float speed_y[NUM];
    float radius[NUM];
    float gravity;
    
    int lifetime;
    int time;
    
    ofColor hue;
};


#endif /* Bounce_hpp */
