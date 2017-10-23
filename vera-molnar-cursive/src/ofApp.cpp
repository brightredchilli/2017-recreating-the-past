#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    panel.setup();
    group.add(slider1);
    group.add(slider2);
    
    panel.add(group);
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float lineHeight = 35;
    float padding = 50;
    float radius = 30;
    float maxWidth = ofGetWidth() - padding;
    float maxHeight = ofGetHeight() - padding;

    ofSetColor(255);

    ofPoint pos = ofPoint(padding, padding + lineHeight);
    ofPath path = ofPath();
    path.setFilled(false);
    path.setStrokeWidth(1);

//    if (slider1.getName() == "") {
//        slider1.set("x offset", 70, 0, 100);
//        slider2.set("y offset", 10, 0, 80);
//    }

    for (int i = 0; i < controlPoints.size(); i++) {
        ofPushStyle();
        if (i < 2) {
            ofSetColor(0, 255, 0);
        } else {
            ofSetColor(255, 0, 0);
        }
        ofDrawCircle(controlPoints[i], 1);
        ofPopStyle();
    }

    float bezierLength = 50;
    float controlPointDist = 55;
    float controlPointYOffset = 17;

    int idx = 0;
    while(pos.y < maxHeight) {
        pos.x = padding;
        path.moveTo(pos);
        while( pos.x < maxWidth) {


            ofPoint mid = pos + ofPoint(bezierLength/2, 0);
            ofPoint dest = pos + ofPoint(bezierLength, 0);
//
//            if (controlPoints.size() < idx * 2 + 1) {
//                controlPoints.push_back(mid + ofPoint(controlPointDist, -controlPointYOffset));
//                controlPoints.push_back(mid + ofPoint(-controlPointDist, -controlPointYOffset));
//            }
//
//            ofPoint cp1 = controlPoints[idx * 2];
//            ofPoint cp2 = controlPoints[idx * 2 + 1];
//
//            path.bezierTo(cp1, cp2, dest);
//
//            pos = dest;
//            idx++;

            float noiseScale = 6;
            float t = ofGetElapsedTimef() * 0.3;
            ofPoint p1 = mid + ofPoint(bezierLength * 0.15, -controlPointYOffset * 0.5);
            p1 += ofPoint(ofSignedNoise(p1.x, p1.y, t)) * noiseScale;
            ofPoint p2 = mid + ofPoint(0, -controlPointYOffset);
            p2 += ofPoint(ofSignedNoise(p2.x, p2.y, t)) * noiseScale;
            ofPoint p3 = mid + ofPoint(-bezierLength * 0.15, -controlPointYOffset * 0.5);
            p3 += ofPoint(ofSignedNoise(p3.x, p3.y, t)) * noiseScale;
            path.curveTo(p1);
            path.curveTo(p2);
            path.curveTo(p3);
            path.curveTo(dest);
            pos = dest;
        }
        pos.y += lineHeight;

    }

    path.draw();

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }
//    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        currentCP = 0;
    } else if (key == 'b') {
        currentCP = 1;
    }  else if (key == 'c') {
        currentCP = 2;
    }  else if (key == 'd') {
        currentCP = 3;
    }

    if (key == 'x') {
        recording = !recording;
    }
}

void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    float xNorm = (float)x / (float)ofGetWidth();
    float yNorm = (float)y / (float)ofGetHeight();

    controlPoints[currentCP].set(x, y);

//    slider1.set(slider1.getMin() + (slider1.getMax() - slider1.getMin()) * xNorm);
//    slider2.set(slider2.getMin() + (slider2.getMax() - slider2.getMin()) * yNorm);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

