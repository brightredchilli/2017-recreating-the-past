#include "ofApp.h"
#include "EasingFunctions.hpp"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
//    ofSetBackgroundAuto(false);
    font.load("AkzidenzGrotesk-BoldExtended.otf", 100, true, false, true, 0.000001);
    myString = "TECHNO";
    vector<ofTTFCharacter> characters = font.getStringAsPoints(myString);
    meshOutlines.clear();
    for (ofTTFCharacter c : characters) {
        meshOutlines.push_back(c.getTessellation());
    }
    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    textToScreenWidthRatio = ofGetWidth()/bounds.width;
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    center /= textToScreenWidthRatio;
}

//--------------------------------------------------------------
void ofApp::update(){
    initialScale = 0.7408; //ofMap(mouseX, 0, ofGetWidth()*2, 0.8, 1.0); //0.7408;
    initialScaleBy = 0.0434; //ofMap(mouseY, 0, ofGetHeight()*2, 0.04, 0.1); //0.0434;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofScale(0 + sin(ofGetElapsedTimef()), 0 + sin(ofGetElapsedTimef()));
    ofTranslate(ofGetWidth()/2, ofGetElapsedTimef()*2);
    drawDownwards();
    drawUpwards();
}

void ofApp::drawDownwards() {
    ofPushMatrix();
    ofScale(textToScreenWidthRatio, textToScreenWidthRatio);

    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    bounds.x = center.x - bounds.width/2;
    bounds.y = 0;
    auto previousBounds = bounds;
    previousBounds.y -= bounds.height; // some accounting so that the bounds is correct on first run

    int count = 0;
    float scale = initialScale;
    float scaleBy = initialScaleBy;
    float t = 1;
    while(previousBounds.y < ofGetHeight()/textToScreenWidthRatio) {
        float out = t;
        auto newBounds = ofRectangle(bounds);
        newBounds.scaleFromCenter(out);
        newBounds.y = previousBounds.y + previousBounds.height;

        // debug rectangle
        //        ofPushStyle();
        //        ofSetColor(200, count*20, count*20, 100);
        //        ofDrawRectangle(newBounds.x, newBounds.y, newBounds.width, newBounds.height);
        //        ofPopStyle();

        ofPushMatrix();
        ofTranslate(newBounds.getBottomLeft());
        ofScale(out, out);
        for (ofMesh mesh : meshOutlines) {
            mesh.draw();
        }

        ofPopMatrix();

        previousBounds = newBounds;
        t *= scale;
        scale += scaleBy * (t);
        if (scale >= 1) {
            scale = 1;
        }
        count++;
    }

    ofPopMatrix();
}

void ofApp::drawUpwards() {
    ofPushMatrix();
    ofScale(textToScreenWidthRatio, textToScreenWidthRatio);
    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    bounds.x = center.x - bounds.width/2;
    bounds.y = 0;
    auto previousBounds = bounds;
//    previousBounds.y += bounds.height; // some accounting so that the bounds is correct on first run

    int count = 0;
    float scale = initialScale;
    float scaleBy = initialScaleBy;
    float t = 1;
    while(previousBounds.y > -500) {
        float out = 1/t;
        auto newBounds = ofRectangle(bounds);
        newBounds.scaleFromCenter(out);
        newBounds.y = previousBounds.y - newBounds.height;

//         debug rectangle
//                ofPushStyle();
//                ofSetColor(200, count*20, count*20, 100);
//                ofDrawRectangle(newBounds.x, newBounds.y, newBounds.width, newBounds.height);
//                ofPopStyle();

        ofPushMatrix();
        ofTranslate(newBounds.getBottomLeft());
        ofScale(out, out);
        for (ofMesh mesh : meshOutlines) {
            mesh.draw();
        }


        ofPopMatrix();


        previousBounds = newBounds;
        t *= scale;
        scale += scaleBy * (t);
        if (scale >= 1) {
            scale = 1;
        }
        count++;
    }

    ofPopMatrix();
}

void ofApp::drawMeshOutlines() {

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
