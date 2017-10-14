#include "ofApp.h"
#include "EasingFunctions.hpp"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
//    ofSetBackgroundAuto(false);
    center.set(ofGetWidth(), ofGetHeight());
    font.load("AkzidenzGrotesk-BoldExtended.otf", 160, true, false, true, 0.000001);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    ofScale(0.5, 0.5);

    string myString = "TECHNO";
    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    bounds.x = center.x - bounds.width/2;

    auto previousBounds = bounds;
    float t = 1;
    int count = 0;
    float scale = 0.7408;//ofMap(mouseX, 0, ofGetWidth()*2, 0.8, 1.0);
    float start = 0.0434; //ofMap(mouseY, 0, ofGetHeight()*2, 0.04, 0.1);
    while(previousBounds.y < ofGetHeight() * 2) {
        float out = t;
        auto newBounds = ofRectangle(bounds);
        newBounds.scaleFromCenter(out);
        newBounds.y = previousBounds.y + previousBounds.height;

        ofPushMatrix();
        ofTranslate(newBounds.getTopLeft());
        ofScale(out, out);
        font.drawString(myString, 0, newBounds.height * 1/out);
        ofPopMatrix();

        previousBounds = newBounds;
        t *= scale;
        scale += start * (t);
        if (scale >= 1) {
            scale = 1;
        }
        count++;
    }

    ofPopMatrix();
}

float function_DoubleEllipticSigmoid (float x) {
    float a = 0.823;
    float b = 0.463;
    float y = 0;
    if (x<=a){
        if (a <= 0){
            y = 0;
        } else {
            y = b * (1.0 - (sqrt(a*a - x*x)/a));
        }
    }
    else {
        if (a >= 1){
            y = 1.0;
        } else {
            y = b + ((1.0-b)/(1.0-a))*sqrt((1.0-a)*(1.0-a) - (x-1.0)*(x-1.0));
        }
    }
    return y;
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
