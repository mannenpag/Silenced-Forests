#pragma once

#include "ofMain.h"
#include "soundClass.hpp"
#include "meshClass.hpp"
#include "ecosystemMesh.hpp"
#include "checkTimer.hpp"
#include "ofxTimer.h"

#include "ofxOsc.h"
#define PORT 12345

class ofApp : public ofBaseApp{
    
	public:
		void setup();
		void update();
		void draw();
        void camStart();
        void camEnd();
        void areaDetection();
        bool pointRect(float userX, float userY, float rx, float ry, float rw, float rh);
        void showPausScreen();
        void showVisuals();

    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
    
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxTimer appActive;
    ofxTimer pausScreenTimer;
    ofxTimer failResetTimer;
    Timer timer;

    soundClass loadSound;
    meshClass imageMesh;
    Mesh centerMesh;

    ofTrueTypeFont fenixFont;
    ofTrueTypeFont fenixFontLarge;
    ofTrueTypeFont puristaFont;
    ofTrueTypeFont puristaFontLarge;
    ofTrueTypeFont puristaFontXL;
    
    std::string infoAreaOneTitle, infoAreaTwoTitle, infoAreaThreeTitle, infoAreaFourTitle, infoAreaOne, infoAreaTwo, infoAreaThree, infoAreaFour;
    std::string intro, pausScreen, timeIsUp, causesFound;
    
    ofCamera cam;

    //user input class
    ofxOscReceiver osc;
    float oscx = 0.0;
    float oscy = 0.0;
    float inputY, inputX;
    
    ofRectangle userInput;
    
    ofVec2f position, positionsOffset;
    vector <ofVec2f> positions;
    
    int endTime = 1000;
    
    int successCounter = 0;
    int failCounter = 0;
    bool isSuccessCounter = false;
    bool isFailCounter = false;

    bool isMoving;
    bool isChecking = true;
    bool taskWasFailed = false;
    bool taskWasSuccessful = false;

    bool secondPassed;
    bool insideAreaOne, insideAreaTwo, insideAreaThree, insideAreaFour;
    bool areaOneActive, areaTwoActive, areaThreeActive, areaFourActive;
    
    //For debugging
    bool oscActive;
    bool mouseActive;
    
    int areaCounter = 0;
    float areaW = 80;
    float areaH = 80;
    
    //Area one
    int a1X = 1500;
    int a1Y = 195;
    //Area two
    int a2X = 255;
    int a2Y = 785;
    //Area two
    int a3X = 1123;
    int a3Y = 833;
    //Area two
    int a4X = 281;
    int a4Y = 179;
};
