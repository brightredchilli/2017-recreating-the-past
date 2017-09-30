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

//    ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();

    float time = ofGetElapsedTimef();
    hexagonTrack1.draw(time);
    hexagonTrack2.draw(time);
    hexagonTrack3.draw(time);
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
