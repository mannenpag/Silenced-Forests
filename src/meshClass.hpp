//
//  meshClass.hpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/8/19.
//

#ifndef meshClass_hpp
#define meshClass_hpp

#include "ofMain.h"

class meshClass {
    
    public:
        void setup();
        void update(float _x, float _y, float input, float endTime);
        void draw();
    
        ofImage image;
        ofMesh mesh;
        vector<ofVec3f> offsets;
        ofMesh meshCopy;
        bool magnification;
    
        float intensityThreshold;
        float connectionDistance;
        float intialT;
};

#endif /* meshClass_hpp */
