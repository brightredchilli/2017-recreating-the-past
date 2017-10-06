#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofNoFill();
    ofStyle style = ofGetStyle();
    style.rectMode = OF_RECTMODE_CENTER;
    ofSetStyle(style);

    gui.setup();
    gui.add(track2Cos.setup("track 2 cos", 1.0, 0.5, 6.0));
    gui.add(track2Sin.setup("track 2 sin", 1.0, 0.5, 6.0));

    time = 0;

    hexagonTrack2.freezeTime += 3;
    hexagonTrack3.freezeTime += 8;
}

//--------------------------------------------------------------
void ofApp::update() {
    time += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();

    float time = ofGetElapsedTimef() * 0.6; // slow everyone down
    hexagonTrack1.draw(time);
    hexagonTrack2.draw(time + 3);
    hexagonTrack3.draw(time + 8);
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
