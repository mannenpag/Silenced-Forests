//
//  checkTimer.hpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/22/19.
//

#ifndef checkTimer_hpp
#define checkTimer_hpp

#include "ofMain.h"

class Timer {
    
    public:
        void setup(int _endTime, bool _loop);
        void startCheck(bool _checking);
        void runCheck();
        void stopCheck(bool _checking);
        float currentTime();
        void checkEnd(bool _checking);
        void reset();
        int returnLoopCount();
    
        float time;
        float update;
        float oldEnd;
        float startTime;
        float endTime;

        int loopCount;
        bool isLoopCount = false;
        bool loopTimer;
        bool timerIsFinished;
};

#endif /* checkTimer_hpp */
