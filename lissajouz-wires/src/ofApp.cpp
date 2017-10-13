#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    center.set(ofGetWidth() / 2, ofGetHeight() / 2);
    ofSetLineWidth(10);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    drawSineWave();

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }

}

void ofApp::drawSineWave() {
    ofPolyline line = ofPolyline();

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

}

void ofApp::drawCurve(bool smooth) {
    // find two points on the opposite sides of the screen
    // make a couple of bezier curve between them, with random control points

    // pick a random angle between 0 and 360
    float theta = ofRandom(TWO_PI);
    float oppTheta = theta + PI;
    float radius = ofGetWidth() * 0.8;
    float time = ofGetElapsedTimef();
    int r = 127 + sin(time * 323) * cos(time) * 127;
    int g = 127 + sin(time * 343.2) * cos(time) * 127;
    int b = 127 + sin(time * 3308) * cos(time * 2) * 127;
    ofColor color = ofColor(r, g, b);

    ofPoint pStart = center + ofPoint(radius * sin(theta), radius * cos(theta))
    + signedRandomPoint() * 1000;
    ofPoint pEnd = center + ofPoint(radius * sin(oppTheta), radius * cos(oppTheta))
    + signedRandomPoint() * 1000;
    // find a couple of points between p1 and p2

    ofPoint line = pEnd - pStart;

    ofPoint p1 = pStart + line * ofRandomf();
    ofPoint p2 = pStart + line * ofRandomf();
    ofPoint unitPoint = ofPoint(1, 1);

    ofPath path = ofPath();
    path.setFilled(false);
    path.setStrokeWidth(10);
    path.moveTo(pStart);

    float mult = 300;
    path.bezierTo(pStart + signedRandomPoint() * mult, p1 + signedRandomPoint() * mult, p1);
    path.bezierTo(p1 + signedRandomPoint() * mult, p2 + signedRandomPoint() * mult, p2);
    path.bezierTo(p2 + signedRandomPoint() * mult, pEnd + signedRandomPoint() * mult, pEnd);

    if (smooth) {
        path.setStrokeColor(color);
        path.draw();
    } else {
        ofSetColor(color);
        ofPolyline polyline = path.getOutline()[0];
        polyline = polyline.getSmoothed(10);
        polyline.draw();
    }
}

void ofApp::drawStraightWithIntersection() {
    /***
     * Draw straight lines on opposite ends, but saving a list of polylines, and randomly
     * interleaving them one atop the other
     */
}

ofPoint ofApp::signedRandomPoint() {
    return ofPoint(ofRandom(-1, 1), ofRandom(-1, 1));
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

