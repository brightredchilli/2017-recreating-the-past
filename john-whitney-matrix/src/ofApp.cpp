#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    ofBackground(0);
    ofNoFill();
    ofStyle style = ofGetStyle();
    style.rectMode = OF_RECTMODE_CENTER;
    ofSetStyle(style);

    gui.setup();
    gui.add(track2Cos.setup("track 2 cos", 1.0, 0.5, 6.0));
    gui.add(track2Sin.setup("track 2 sin", 1.0, 0.5, 6.0));

//    ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();

    float time = ofGetElapsedTimef();

    int numTrack1 = 10;
    for(int i = 0; i < numTrack1; i++) {
        float count = numTrack1 - 1;
        ofPoint t = track1(time + i * cos(time * 0.5) * 0.1);
        float size = 60 + 40 * cos((count - i)/(count) * HALF_PI);
//        ofSetColor(127, 180, 230);
        drawHexagon(t, size);
    }

    float numTrack2 = 10;
    for(float i = 0; i < numTrack2; i++) {
        float count = numTrack2 - 1;
        ofPoint t = track2(time + i * cos(time * 0.5) * 0.1);
        float size = 60 + 40 * cos((count-i)/(count) * HALF_PI);

//        ofSetColor(127, 180, 190);
        drawHexagon(t, size);
    }


    float numTrack3 = 10;
    for(float i = 0; i < numTrack3; i++) {
        int count = numTrack3 - 1;
        ofPoint t = track3(time + i * cos(time * 0.5) * 0.1);
        float size = 60 + 40 * cos((count-i)/(count) * HALF_PI);
//        ofSetColor(197, 120, 190);
        drawHexagon(t, size);
    }

}

/// Draws hexagon pointing up
void ofApp::drawHexagon(ofPoint point, float size) {
    ofPushMatrix();
    ofSetCircleResolution(6);
    ofTranslate(point.x, point.y);
    ofRotateDeg(30);
    ofDrawCircle(0, 0, size);
    ofPopMatrix();
}

ofPoint ofApp::track1(float time) {
    float r = ofGetWidth() * .25; // ~ 200 - 300
    float x = center.x + r * sin(time * 1.0);
    float y = center.y + r * cos(time * 1.6);
    return ofPoint(x, y);
}

ofPoint ofApp::track2(float time) {
    float r = ofGetWidth() * .18;
    float x = center.x + r * (sin(time * 1) + sin(time * 3));
    float y = center.y + r * (cos(time * 1) + sin(time * 2));
    return ofPoint(x, y);
}

ofPoint ofApp::track3(float time) {
    float r = ofGetWidth() * .18;
    float x = center.x + r * cos(time * 1.0);
    float y = center.y + r * sin(time * 1.6);
    return ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c') {
        ofSetBackgroundAuto(!ofGetBackgroundAuto());
    } else if (key == 'd') {
        debugTrails = !debugTrails;
    }
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
