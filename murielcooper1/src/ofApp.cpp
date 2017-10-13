#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("SF.otf", 200, true, true, true);
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    ofBackground(0);
    stringToUse = "SFPC";

    
    setUpCooperDots1();
}

void ofApp::setUpCooperDots1() {
    loadCharacters(stringToUse);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {

    drawCooperDots1();
    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }
}
void ofApp::drawCooperDots1() {
    ofPushMatrix();
    ofTranslate(center);
    ofTranslate(originOffsetForCharacters(stringToUse));

    float time = ofGetElapsedTimef() * 2;
    for (ofTTFCharacter shape : characters) {
        vector<ofPolyline> lines = shape.getOutline();
        for (ofPolyline line : lines) {
            line = line.getResampledBySpacing(5);
            for (int i = 0; i < line.size(); i++) {
                ofPoint point = line[i];
                ofSetColor(255, 255, 255, 128 + 127 *sin(time + 0.1 * i));
                ofDrawCircle(point.x, point.y, 1);
            }
        }
    }
    ofPopMatrix();
}

void ofApp::loadCharacters(const std::string &s) {
    characters = font.getStringAsPoints(s);
}

 ofPoint ofApp::originOffsetForCharacters(const std::string &s) {
    auto bounds = font.getStringBoundingBox(s, 0, 0);
    return ofPoint(-bounds.width/2, bounds.height/2);
}

void ofApp::drawStringCentered(const std::string &s, float x, float y) {
    auto offset = originOffsetForCharacters(s);
    font.drawString(s, x - offset.x, y + offset.y);
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

//  Globals which should be set before calling this function:
//
//  int    polyCorners  =  how many corners the polygon has (no repeats)
//  float  polyX[]      =  horizontal coordinates of corners
//  float  polyY[]      =  vertical coordinates of corners
//  float  x, y         =  point to be tested
//
//  (Globals are used in this example for purposes of speed.  Change as
//  desired.)
//
//  The function will return YES if the point x,y is inside the polygon, or
//  NO if it is not.  If the point is exactly on the edge of the polygon,
//  then the function may return YES or NO.
//
//  Note that division by zero is avoided because the division is protected
//  by the "if" clause which surrounds it.

bool pointInPolygon(ofPolyline line, ofPoint test) {

    int i = 0;
    int j = line.size() - 1;
    bool oddNodes = false;

    for (i = 0; i < line.size(); i++) {
        ofPoint point = line[i];
        ofPoint otherPoint = line[j];
        if (point.y < test.y && otherPoint.y >= test.y
            ||  otherPoint.y < test.y && point.y >= test.y) {

            if (point.x + (test.y - point.y) / (otherPoint.y - point.y) * (otherPoint.x -point.x) < test.x) {
                oddNodes=!oddNodes;
            }
        }
        j=i;
    }

    return oddNodes;
}
