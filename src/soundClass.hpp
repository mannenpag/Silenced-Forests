//
//  soundClass.hpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/8/19.
//

#ifndef soundClass_hpp
#define soundClass_hpp

#include "ofMain.h"

class soundClass {
    
    public:
        void setup();
        void update();
        void draw(float timerInput, float endTime);
        void volumeReset(float _a,float _b,float _c);
        void polylineupdate();
        void polylineDraw();
        ofSoundPlayer sound;
    
        float *fft;
        float *soundSpectrum;
        int bands;
        ofSoundPlayer frogs;
        ofSoundPlayer treeFrog;
        ofSoundPlayer chineseFrog;
        ofSoundPlayer silence;
};

#endif /* soundClass_hpp */
