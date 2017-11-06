#include "ofRecodedApp.h"

//--------------------------------------------------------------
void ofRecodedApp::setup() {

    /// recoded setup begins

    dimensions = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());

    /// recoded setup ends

    ofBackground(0);
    ofNoFill();
    ofStyle style = ofGetStyle();
    style.rectMode = OF_RECTMODE_CENTER;
    ofSetStyle(style);

    // don't freeze time for recoded project
    hexagonTrack1.freezeTime = -100;
    hexagonTrack2.freezeTime = -100;
    hexagonTrack3.freezeTime = -100;

    time = 0;
}

//--------------------------------------------------------------
void ofRecodedApp::update() {
    time += ofGetLastFrameTime() * param1;
    hexagonTrack1.spacingRatioMultiplier = param2;
    hexagonTrack2.spacingRatioMultiplier = param2;
    hexagonTrack3.spacingRatioMultiplier = param2;
}

//--------------------------------------------------------------
void ofRecodedApp::draw() {
    gui.draw();

//    float time = time * param1; // slow everyone down
    hexagonTrack1.draw(time);
    hexagonTrack2.draw(time + 3);
    hexagonTrack3.draw(time + 8);
}

//--------------------------------------------------------------
void ofRecodedApp::keyPressed(int key){
    if (key == 'c') {
        ofSetBackgroundAuto(!ofGetBackgroundAuto());
    } else if (key == 'd') {
        debugTrails = !debugTrails;
    }
}


//--------------------------------------------------------------
void ofRecodedApp::mouseMoved(int x, int y ){
    param1 = ofMap(x, 0, ofGetWidth(), 0, 1.5);
    param2 = ofMap(y, 0, ofGetHeight(), 0, 1);
}

