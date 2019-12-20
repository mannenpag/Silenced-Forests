#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("Silent Ecosphere");
    fenixFont.load("fonts/Fenix-Regular.ttf", 38);
    fenixFontLarge.load("fonts/Fenix-Regular.ttf", 76);
    puristaFont.load("fonts/Purista-Medium.ttf", 14);
    puristaFontLarge.load("fonts/Purista-Medium.ttf", 25);
    puristaFontXL.load("fonts/Purista-Medium.ttf", 180);

    intro = "Show dashboard by releasing the iPad";
    pausScreen = "Examine the interconnected web of \namphibian species. Look for the four \npossible causes of killer fungus hidden \nin the web, before it is too late.";

    timeIsUp = "Time is up, and species have disappeared \ndue to fungal spread. This is what happens \nwhen consumerism makes humans \ninterfere in an ecosystem blindly.";
    causesFound = "Good – you have found the cause of the \nproblem. There may still be time to \nfind it is solution. The world is not \nlost unless we allow it to be…";
    
    infoAreaOneTitle = "Pet & Food trade";
    infoAreaTwoTitle = "Global Warming";
    infoAreaThreeTitle = "Habitat Loss";
    infoAreaFourTitle = "Pollution";

    infoAreaOne = "We relocate thousands of animals every day, and with animals, \nthere are diseases. Since a lot of cultures around the world see \nAmphibians as food, a huge number of frogs are being shipped \nall over the world, passing the disease around where it arrives.";
    infoAreaTwo = "The release of greenhouse gases is altering the conditions \nfor life on our planet; sea levels are rising, glaciers are melting, \nand the weather patterns are changing. Global warming matters \nespecially to amphibians because they regulate their temperature \nfrom their surroundings.";
    infoAreaThree = "One of the greatest threats to species is the loss of \ntheir habitats. The world's forests, lakes, swamps, and other habitats \nare disappearing as they are harvested for human consumption \nto make way for industrial development such as agriculture, housing, \nroads, and pipelines. This leaves the remaining population stressed, which increases \nthe risk of getting sick.";
    infoAreaFour = "Pollutants damage the quality of air, water, and land, destroy \nthe amphibians’ home, and impact the animals themselves, leaving \nthe amphibians less resilient to other threats like a disease.";
    
    ofSetFrameRate(45);
    ofSetCircleResolution(60);
    
    loadSound.setup();
    imageMesh.setup();
    centerMesh.setup();
    
    appActive.setup(3000, false);
    pausScreenTimer.setup(10000, false);
    failResetTimer.setup(10000, false);
    
    timer.setup(endTime, true);
    isChecking = true;

    osc.setup(PORT);

    isMoving = false;
    secondPassed = false;

    areaOneActive = false;
    areaTwoActive = false;
    areaThreeActive = false;
    areaFourActive = false;
    
    oscActive = false;
    mouseActive = true;
    
    position = ofVec2f(0, 0);
    positionsOffset = ofVec2f(0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(osc.hasWaitingMessages()) {
        ofxOscMessage m;
        osc.getNextMessage(&m);
        if (m.getAddress() == "/position/x") {
            oscx = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/position/y") {
            oscy = m.getArgAsFloat(0);
        }
    }
    if (oscActive) {
        inputY = (ofMap(oscy, 1, 0, 0, ofGetHeight()));
        inputX = (oscx * ofGetWidth());
    }
    if (mouseActive) {
        inputY = mouseY;
        inputX = mouseX;
    }
    
    cout << mouseX;
    cout << "\n";
    cout << mouseY;
    cout << "\n";
//
    //Load classes
    imageMesh.update(inputX, inputY, 0, endTime);
    loadSound.update();
    centerMesh.update();
    
    if (isMoving && !taskWasSuccessful &&!taskWasFailed) {
        if(!isChecking) timer.startCheck(isChecking);
        else timer.runCheck();
        
    } else {
        if(isChecking) timer.stopCheck(isChecking);
        appActive.reset();
        appActive.startTimer();
    }
    
    if (taskWasSuccessful) {
        pausScreenTimer.startTimer();
    } else {
        pausScreenTimer.reset();
    }
    
    if (taskWasFailed) {
        failResetTimer.startTimer();
    } else {
        failResetTimer.reset();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //Setting up the timer again
    
    timer.checkEnd(isChecking);
    
    if (taskWasSuccessful || taskWasFailed) {
        timer.stopCheck(isChecking);
    }

    //draw background gradient
    ofColor centerColor = ofColor(62, 78, 68);
    ofColor edgeColor(12, 12, 12);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    //Sound change
    loadSound.draw(timer.currentTime()/100, endTime);
    
    //Mesh init
    camStart();
        showVisuals();
    camEnd();
    
    //detection of user input
    position.x = inputX;
    position.y = inputY;
    
    userInput.width = 200;
    userInput.height = 200;
    userInput.x = position.x - userInput.width*0.5;
    userInput.y = position.y - userInput.height*0.5;
    
//    ofPopMatrix();
//        ofNoFill();
//        ofSetColor(230, 230, 230);
//        ofDrawRectangle(userInput);
//    ofPushMatrix();

    positions.push_back(position);
    for (float i = 0; i < positions.size(); i++) {
        positionsOffset.x = positions[i - 1].x;
        positionsOffset.y = positions[i - 1].y;
        if (i > 1) {
            positions.erase (positions.begin());
        }
    }
    
    if (positionsOffset.x != position.x || positionsOffset.y != position.y) {
        isMoving = false;
    } else {
        isMoving = true;
    }
    
    //declare the bool for interaction areas
    insideAreaOne = pointRect(inputX, inputY, a1X, a1Y, areaW, areaH);
    insideAreaTwo = pointRect(inputX, inputY, a2X, a2Y, areaW, areaH);
    insideAreaThree = pointRect(inputX, inputY, a3X, a3Y, areaW, areaH);
    insideAreaFour = pointRect(inputX, inputY, a4X, a4Y, areaW, areaH);
    
    //Check system if user has descovered
    if (insideAreaOne && !areaOneActive) {
        areaCounter = 1;
        areaOneActive = true;
    }
    if (insideAreaTwo && !areaTwoActive && areaCounter == 1) {
        areaCounter = 2;
        areaTwoActive = true;
    }
    if (insideAreaThree && !areaThreeActive && areaCounter == 2) {
        areaCounter = 3;
        areaThreeActive = true;
    }
    if (insideAreaFour && !areaFourActive && areaCounter == 3) {
        areaCounter = 4;
        areaFourActive = true;
    }
    if (areaCounter == 4) {
        taskWasSuccessful = true;
        if (!isSuccessCounter) {
            successCounter+=1;
            isSuccessCounter = true;
        }
    }
    
    if (timer.currentTime() >= endTime) {
//        areaCounter = 0;
//        areaOneActive = false;
//        areaTwoActive = false;
//        areaThreeActive = false;
//        areaFourActive = false;
        taskWasFailed = true;
        if (!isFailCounter) {
            failCounter+=1;
            isFailCounter = true;
        }

    }
    
    if (appActive.getTimeLeftInSeconds() < 2.5) {
        secondPassed = true;
    } else {
        secondPassed = false;
    }
    
    //If application isn't active
    if (isMoving && secondPassed && !taskWasSuccessful && !taskWasFailed) {
        showPausScreen();
        fenixFont.drawString(pausScreen, 60, 60);
    }
    
    if (!isMoving && !taskWasSuccessful && !taskWasFailed) {
        //Draw Instructions and string
        ofSetColor(230, 230, 230);
        puristaFontLarge.drawString(intro, 40, 40);
        
        string reasons = "Reasons discovered: " + ofToString(areaCounter);
        puristaFontLarge.drawString(reasons, ofGetWidth()-puristaFont.stringWidth(reasons)-180, 60);
    }
    
    if (taskWasSuccessful) {
        ofPopMatrix();
        ofSetColor(10, 14, 10, 240);
        ofFill();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPushMatrix();
        ofSetColor(230, 230, 230);
        fenixFontLarge.drawString(causesFound, 60, 100);
        string showPausTime = "Time untill restart: " + ofToString(floor(pausScreenTimer.getTimeLeftInSeconds()));
        puristaFontLarge.drawString(showPausTime, 60, fenixFontLarge.stringHeight(causesFound) + 100);
    }
    
    if (taskWasFailed) {
        ofPopMatrix();
        ofSetColor(10, 14, 10, 240);
        ofFill();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPushMatrix();
        ofSetColor(230, 230, 230);
        fenixFontLarge.drawString(timeIsUp, 60, 100);
        string showPausTime = "Time untill restart: " + ofToString(floor(failResetTimer.getTimeLeftInSeconds()));
        puristaFontLarge.drawString(showPausTime, 60, fenixFontLarge.stringHeight(timeIsUp) + 100);
    }
    
    //If the timers of the fail / success is done reset the program.
    if (pausScreenTimer.getTimeLeftInSeconds() <= 0 || failResetTimer.getTimeLeftInSeconds() <= 0) {
        timer.reset();

        areaCounter = 0;
        areaOneActive = false;
        areaTwoActive = false;
        areaThreeActive = false;
        areaFourActive = false;
        taskWasSuccessful = false;
        taskWasFailed = false;
        isSuccessCounter = false;
        isFailCounter = false;

        cout <<  "Things are done";
        cout <<  "\n";
        
    }
}

//--------------------------------------------------------------
void ofApp::camStart(){
    float degMapX = ofMap(inputX, 0, ofGetWidth(), -6, 6);
    float degMapY = ofMap(inputY, 0, ofGetHeight(), -6, 6);
    //float time = sin(.3 * ofGetElapsedTimef());
    float time = 1;
    
    float longitude = degMapX * time/2;
    float latitude = degMapY * time/2;
    
    float radius = 1300;
    cam.orbit(longitude, latitude, radius, ofPoint(0,0,0));
    cam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::camEnd(){
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
bool ofApp::pointRect(float userX, float userY, float rx, float ry, float rw, float rh){
    if (userX >= rx &&
        userX <= rx + rw &&
        userY >= ry &&
        userY <= ry + rh) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f'){
        ofToggleFullscreen();
    }
    if (key == 'h'){
        ofHideCursor();
    }
    if (key == '1'){
        oscActive = false;
        mouseActive = true;
    }
    if (key == '2'){
        oscActive = true;
        mouseActive = false;
    }
}

//--------------------------------------------------------------
void ofApp::showPausScreen(){
    ofPopMatrix();
    ofSetColor(12, 12, 12, 180);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofPushMatrix();
    ofSetColor(230, 230, 230);
    
    //Draw dashbord
//    string showTime = "Time left: " + ofToString(floor(timer.currentTime()));
//    puristaFontLarge.drawString(showTime, ofGetWidth()-puristaFontLarge.stringWidth(showTime)-60, 140);
    
    //Draw strings from reasons
    if (areaOneActive) {
        puristaFontLarge.drawString(
                               infoAreaOneTitle,
                               60,
                               ofGetHeight()/4 + puristaFont.stringHeight(infoAreaOne) - 40
                                );
        puristaFont.drawString(
                               infoAreaOne,
                               60,
                               ofGetHeight()/4 + puristaFont.stringHeight(infoAreaOne)
                               );
    }
    if (areaTwoActive) {
        puristaFontLarge.drawString(
                               infoAreaTwoTitle,
                               60,
                               ofGetHeight()/2.5 + puristaFont.stringHeight(infoAreaTwo) - 40
                                );
        puristaFont.drawString(
                               infoAreaTwo,
                               60,
                               ofGetHeight()/2.5 + puristaFont.stringHeight(infoAreaTwo)
                               );

    }
    if (areaThreeActive) {
        puristaFontLarge.drawString(
                               infoAreaThreeTitle,
                                60 + ofGetWidth()/3,
                                ofGetHeight()/4 + puristaFont.stringHeight(infoAreaOne) - 40
                                );
        puristaFont.drawString(
                               infoAreaThree,
                               60 + ofGetWidth()/3,
                               ofGetHeight()/4 + puristaFont.stringHeight(infoAreaOne)
                               );

    }
    if (areaFourActive) {
        puristaFontLarge.drawString(
                               infoAreaFourTitle,
                               60 + ofGetWidth()/3,
                               ofGetHeight()/2.5 + puristaFont.stringHeight(infoAreaThree) - 40
                               );
        puristaFont.drawString(
                               infoAreaFour,
                               60 + ofGetWidth()/3,
                               ofGetHeight()/2.5 + puristaFont.stringHeight(infoAreaThree)
                               );

    }
}

//--------------------------------------------------------------
void ofApp::showVisuals(){
    imageMesh.draw();
    centerMesh.draw(timer.currentTime(), endTime);
    
    //Draw hotspots for areas
    if (areaOneActive) {
        ofPopMatrix();
        ofFill();
        ofSetColor(254, 153, 34, 50);
        ofDrawCircle(a1X-ofGetWidth()/2, a1Y+ofGetHeight()/9, areaW/2);
        ofPushMatrix();
        ofPopMatrix();
        ofNoFill();
        ofSetColor(254, 153, 34, 200);
        ofDrawCircle(a1X-ofGetWidth()/2, a1Y+ofGetHeight()/9, areaW/2);
        ofPushMatrix();
    }
    if (areaTwoActive) {
        ofPopMatrix();
        ofFill();
        ofSetColor(254, 153, 34, 50);
        ofDrawCircle(a2X-ofGetWidth()/2, a2Y-ofGetHeight(), areaW/2);
        ofPushMatrix();
        ofPopMatrix();
        ofNoFill();
        ofSetColor(254, 153, 34, 200);
        ofDrawCircle(a2X-ofGetWidth()/2, a2Y-ofGetHeight(), areaW/2);
        ofPushMatrix();
    }
    if (areaThreeActive) {
        ofPopMatrix();
        ofFill();
        ofSetColor(254, 153, 34, 50);
        ofDrawCircle(a3X-ofGetWidth()/2, a3Y-ofGetHeight(), areaW/2);
        ofPushMatrix();
        ofPopMatrix();
        ofNoFill();
        ofSetColor(254, 153, 34, 200);
        ofDrawCircle(a3X-ofGetWidth()/2, a3Y-ofGetHeight(), areaW/2);
        ofPushMatrix();
    }
    if (areaFourActive) {
        ofPopMatrix();
        ofFill();
        ofSetColor(254, 153, 34, 50);
        ofDrawCircle(a4X-ofGetWidth()/2.1, a4Y+ofGetHeight()/6, areaW/2);
        ofPushMatrix();
        ofPopMatrix();
        ofNoFill();
        ofSetColor(254, 153, 34, 200);
        ofDrawCircle(a4X-ofGetWidth()/2.1, a4Y+ofGetHeight()/6, areaW/2);
        ofPushMatrix();
    }
    
//    ofPopMatrix();
//    ofSetColor(255, 255, 255, 100);
//    //Show the wins and fails
//    string success = ofToString(successCounter);
//    puristaFontXL.drawString(success, 800, 0);
//    string fails = ofToString(failCounter);
//    puristaFontXL.drawString(fails, puristaFont.stringWidth(success)+1000, 0);
//    ofPushMatrix();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
