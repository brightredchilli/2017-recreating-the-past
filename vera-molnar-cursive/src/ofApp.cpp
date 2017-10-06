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

    path.moveTo(pos);

//    if (slider1.getName() == "") {
//        slider1.set("x offset", 70, 0, 100);
//        slider2.set("y offset", 10, 0, 80);
//    }

    float bezierLength = 50;
    float controlPointDist = 55;
    float controlPointYOffset = 17;

    while(pos.y < maxHeight) {
        for(pos.x = padding; pos.x < maxWidth;) {
            ofPoint mid = pos + ofPoint(bezierLength/2, 0);
            ofPoint dest = pos + ofPoint(bezierLength, 0);

            path.bezierTo(mid + ofPoint(controlPointDist, -controlPointYOffset),
                          mid + ofPoint(-controlPointDist, -controlPointYOffset),
                          dest);

            pos = dest;
        }
        pos.y += lineHeight;
    }

    path.draw();
//    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    float xNorm = (float)x / (float)ofGetWidth();
    float yNorm = (float)y / (float)ofGetHeight();

    slider1.set(slider1.getMin() + (slider1.getMax() - slider1.getMin()) * xNorm);
    slider2.set(slider2.getMin() + (slider2.getMax() - slider2.getMin()) * yNorm);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

