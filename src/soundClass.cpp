//
//  soundClass.cpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/8/19.
//

#include "soundClass.hpp"

void soundClass::setup() {
    //Sound files setup
    frogs.load("audio/frogs.wav");
    frogs.setLoop(true);
    
    treeFrog.load("audio/tree-frog.wav");
    treeFrog.setLoop(true);
    
    chineseFrog.load("audio/frog-chinese.wav");
    chineseFrog.setLoop(true);
    
    silence.load("audio/silence.wav");
    silence.setLoop(true);
    
    silence.setVolume(0);

    
    volumeReset(1,1,1);
    
    frogs.play();
    treeFrog.play();
    chineseFrog.play();
    silence.play();
    
    int fftWidth = ofGetWidth();
    
    fft = new float[fftWidth];
    for (int i = 0; i < fftWidth; i++) {
        fft[i] = 0;
    }
    bands = fftWidth;
}

void soundClass::update(){
    ofSoundUpdate();
    polylineupdate();
}

void soundClass::draw(float timerInput, float endTime) {
    if (timerInput <= endTime) {
        float timeConst = 1 - (timerInput/endTime) * 100;
        float timeConstSilence = 0 + (timerInput/endTime) * 100;
//        cout << timeConstSilence;
        cout << "\n";
        volumeReset(timeConst,timeConst,timeConst);
        silence.setVolume(timeConstSilence);
    }
    if (timerInput >= endTime) {
        volumeReset(0,0,0);
        silence.setVolume(1);
    }
    polylineDraw();
}

void soundClass::volumeReset(float _a,float _b,float _c) {
    frogs.setVolume(_a);
    treeFrog.setVolume(_b);
    chineseFrog.setVolume(_c);
}

void soundClass::polylineupdate(){
    ofSoundUpdate();
    soundSpectrum = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++) {
        fft[i] *= 0.9;
        if (fft[i] < soundSpectrum[i]) {
            fft[i] = soundSpectrum[i];
        }
    }
}

void soundClass::polylineDraw(){
    for (int i = 0; i < 1; i++) {
        ofPolyline polyline;
        int yPos = ofGetHeight() - 60;
        
        for (int j = 0; j < bands; j++) {
            polyline.addVertex(j, i+yPos - fft[j] * 100.0);
        }
        polyline.draw();
    }
}
