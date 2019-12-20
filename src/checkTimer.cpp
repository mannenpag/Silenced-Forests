//
//  checkTimer.cpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/22/19.
//

#include "checkTimer.hpp"

void Timer::setup(int _endTime, bool _loop) {
    endTime = _endTime;
    startTime = 0;
    oldEnd = 0;
    time = ofGetElapsedTimef();
    loopCount = 0;
    loopTimer = _loop;
}

void Timer::startCheck(bool _checking) {
    _checking = true;
    startTime = ofGetElapsedTimef();
    runCheck();
}

float Timer::currentTime(){
    return time - startTime + oldEnd;
}

void Timer::runCheck(){
    update = currentTime();
}

void Timer::stopCheck(bool _checking){
    oldEnd = currentTime();
    _checking = false;
}

void Timer::checkEnd(bool _checking) {
    isLoopCount = false;
    if (update >= endTime && loopTimer) {
        cout << "Timer stopped \n";
        startTime = 0;
        oldEnd = 0;
        _checking = false;
        if (!isLoopCount) {
            loopCount++;
            isLoopCount = true;
        }
    }
}

void Timer::reset() {
    startTime = 0;
    oldEnd = 0;
}

int Timer::returnLoopCount(){
    return loopCount;
}

//void Timer::setup(float _endTime, bool bLoop) {
//    endTime = _endTime;
//    timerLoop = bLoop;
//
//    timerIsFinished = false;
//    startTime = 0;
//    oldEnd = 0;
//    //time = ofGetElapsedTimef();
//    loopCount = 0;
//}
//
//void Timer::startCheck(bool bInput) {
//    bInput = true;
//    startNum = ofGetElapsedTimef();
//    runCheck();
//}
//
//float Timer::currentTime(){
//    return ofGetElapsedTimef() - startNum + oldEnd;
//}
//
//void Timer::runCheck(){
//    update = currentTime();
//}
//
//void Timer::stopCheck(bool bInput){
//    oldEnd = currentTime();
//    bInput = false;
//}
//
//void Timer::checkEnd(bool bInput) {
//    //cout << bInput;
//
//    time = ofGetElapsedTimef();
//
//    if (update >= endTime && timerLoop) {
//        timerIsFinished = true;
//
//        loopCount++;
//        startTime = 0;
//        oldEnd = 0;
//        //time = time - time * loopCount;
//        bInput = false;
//
//    }
//}
//
