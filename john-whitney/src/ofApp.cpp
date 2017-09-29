#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /***
     Try:
     Makes a lissajous figure by connecting separate line segments.
     Each segment can be turned on and off separately
     **/

    float step = 1/30.0;

    for (float t = 0; t < 30.0; t += step) {
        float x = ofGetWidth()/2 + 200 * cos(t * 3.2);
        float y = ofGetHeight()/2 + 200 * sin(t * 2.1);
        points.push_back(ofPoint(x, y));
    }

    for (float i = 1; i < points.size(); i++) {
        ofPolyline line;
        line.addVertex(points[i-1]);
        line.addVertex(points[i]);
        lines.push_back(line);
    }

    ofBackground(0);
    ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0, 50);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(255);
    float t = ofGetElapsedTimef() * 0.5;
    for(int i = 0; i < lines.size(); i++) {
        float noise = ofNoise(t + i * 0.3);
        if (noise < 0.5) {
            lines[i].draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
