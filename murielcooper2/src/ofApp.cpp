#include "ofApp.h"
#include "EasingFunctions.hpp"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
//    ofSetBackgroundAuto(false);
    center.set(ofGetWidth(), ofGetHeight());
    font.load("avenirnext.ttc", 80, true, false, true, 0.000001);
//    font.setLetterSpacing(0.94);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

//    if (ofGetFrameNum() == 6) {
//        ofPoint position = ofPoint(center.x, 0);
//        int fontSizeStep = 5;
//
//        float t = 1;
//        int count = 0;
//        while(position.y < ofGetHeight()) {
//
//            if (t < 0) {
//                t = 0;
//            }
//            //            float out = powf(t, 5);
////            float out = function_CubicBezier(t, 0.433, 0.05, 0.81, 0.057);
//            float out = function_CubicBezier(t, 0.513, 0.152, 0.917, 0.3);
////            float out = function_VariableStaircase(t, 1., 4);
//
//            int size = ofMap(out, 0, 1, 3, 3);
//            font.load("SF.otf", size, true, true, true);
//            font.setLetterSpacing(0.94);
//            auto bounds = font.getStringBoundingBox("aaaa", 0, 0);
//
//            float adjustedHeight = bounds.height * 0.98;
//            font.drawString("aaaa", position.x - bounds.width/2, position.y + adjustedHeight);
//
////            float testWidth = ofMap(size, 5, 180, 0, ofGetWidth()/2);
////            ofDrawRectangle(center.x - testWidth/2, count * 20, testWidth , 20);
//            position.y += adjustedHeight;
//            t -= 0.065;
//
//
//            count++;
//        }
//    }

    ofPushMatrix();
    ofScale(0.5, 0.5);

    string myString = "technologic";
    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    bounds.x = center.x - bounds.width/2;


//    font.drawString(myString, bounds.x - 4, bounds.getBottom());
//    ofPushStyle();
//    ofSetColor(255, 100, 0, 100);
//    ofDrawRectangle(bounds);
//    ofPopStyle();


    auto previousBounds = bounds;
    float t = 1;
    int count = 0;
    while(previousBounds.y < ofGetHeight() * 2) {


//        float out = function_CubicBezier(t, 0.513, 0.152, 0.917, 0.3);
//        float out = function_CubicBezier(t, 0.433, 0.05, 0.81, 0.057);
        float power = ofMap(mouseX, 0, ofGetWidth() * 2, 0, 10);
        float out = ofClamp(powf(t, 7) + 0.08, 0.08, 1);

//        ofPushStyle();
//        ofSetColor(0, 255, 0, 120);
//        float testWidth = ofMap(out, 0, 1, 0, ofGetWidth()*2);
//        ofDrawRectangle(0, count * 30, testWidth , 30);
//        ofPopStyle();

        auto newBounds = ofRectangle(bounds);
        newBounds.scaleFromCenter(out);
        newBounds.y = previousBounds.y + previousBounds.height;
//        ofPushStyle();
//        ofSetColor(0, 255, 0, 120);
//        ofDrawRectangle(newBounds);
//        ofPopStyle();

        ofPushMatrix();
        ofTranslate(newBounds.getTopLeft());
        ofScale(out, out);
//        float adjustedHeight = adjustedBounds.height * 0.98;
        font.drawString(myString, 0, newBounds.height * 1/out);

        ofPopMatrix();

        //            float testWidth = ofMap(size, 5, 180, 0, ofGetWidth()/2);
        //            ofDrawRectangle(center.x - testWidth/2, count * 20, testWidth , 20);
//        position.y += adjustedHeight;
        previousBounds = newBounds;
        t -= 0.03;


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
