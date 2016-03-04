#pragma once

#include "ofMain.h"

class dotMovie{
public:
    void update();
    void draw(ofVideoPlayer video);
    void draw(ofVideoPlayer video, int mode, int size_spect);
    void draw(ofVideoPlayer video, int mode, int size_spect1, int size_spect2);
    void draw(ofVideoPlayer video, int size_spect[]);
};
