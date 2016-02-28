//
//  Drop.hpp
//  test_rain&kinect
//
//  Created by 片山怜 on 2016/02/21.
//
//

#ifndef Drop_hpp
#define Drop_hpp

#include <stdio.h>
#include "ofMain.h"

class Drop {
    
public:
    
    float rainX;
    float rainY1;
    float rainY2;
    float speed_y;
    float linewidth;
    
    Drop();
    void update();
    void draw();
    
    ofColor rainHue;
    
};

#endif /* Drop_hpp */
