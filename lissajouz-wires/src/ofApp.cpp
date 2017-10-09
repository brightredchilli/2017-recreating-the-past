#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {


    ofPolyline line = ofPolyline();
    ofSetLineWidth(10);

    float time = ofGetElapsedTimef();
    int r = 127 + sin(time * 3) * cos(time) * 127;
    int g = 127 + sin(time * 3.2) * cos(time) * 127;
    int b = 127 + sin(time * 3) * cos(time * 2) * 127;

    ofSetColor(r, g, b);

    float start = ofRandom(0, 10000);
    float end = start + ofRandom(0, 70);

    float resolution = 0.1;
    float radius = 800 + 200 * sin(time * 3.2) * sin(time * 2.1);
    ofPoint center = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    center.x += 100 * sin(3 * time) * cos(9 * time);
    center.y += 100 * sin(5 * time) * cos(7 * time);

    for (float t = start; t < end; t += resolution) {
        float xAdder = 4.5 * sin(time * 3);
        float yAdder = 98.3 * sin(time * 5);
        int x = center.x + radius * sin(t + xAdder);
        int y = center.y + radius * cos(t + yAdder);
        line.addVertex(ofPoint(x, y));
    }
    line.draw();

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x') {
        recording = !recording;
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

