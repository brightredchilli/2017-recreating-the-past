#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetCircleResolution(100);
    center.set(0, 0);
    ofBackground(0);
    blur.setup(ofGetWidth(), ofGetHeight(), 2, .2, 4, .3);
    numLoops = 13;
    for(int i = 0; i < numLoops; i++) {
        loops.push_back(false);
    }
//    loops[9] = true;
    loops[12] = true;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw circles around in a circle

//    blur.begin();
    ofPushStyle();
    ofStyle style = ofGetStyle();
    style.rectMode = OF_RECTMODE_CENTER;
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    float scale = 0.7 + sin(ofGetElapsedTimef() * 0.1) * 0.4;
    ofScale(scale,scale,1);

    if (loops[0]) {
        drawLoop();
    }
    if (loops[1]) {
        drawLoop1();
    }
    if (loops[2]) {
        drawLoop2();
    }
    if (loops[3]) {
        drawLoop3();
    }
    if (loops[4]) {
        drawLoop4();
    }
    if (loops[5]) {
        drawLoop5();
    }
    if (loops[6]) {
        drawLoop6();
    }
    if (loops[7]) {
        drawLoop7();
    }
    if (loops[8]) {
        drawLoop8();
    }
    if (loops[9]) {
        drawLoop9();
    }
    if (loops[10]) {
        drawLoop10();
    }
    if (loops[11]) {
        drawLoop11();
    }
    if (loops[12]) {
        drawLoop12();
    }

    ofPopMatrix();
    ofPopStyle();
//    blur.end();
//    blur.draw();

    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}


void ofApp::drawLoop12() {
    float time = ofGetElapsedTimef() * 0.01;
    int count = 100;

    float rowoffset = 30;
    float increment = TWO_PI / count;
    float innerRadius = 480;

    ofPushStyle();
    ofColor color = ofColor::fromHex(0xCCCCCC);
    color.r += 30 * sin(time);
    color.g += 30 * cos(time * 0.36);
    color.b += 30 * sin(time * 0.96);

    ofSetColor(color, 230);
    for (int i = 0; i < count; i++) {
        float radius = innerRadius;
//        center.set(ofGetWidth()/2, ofGetHeight()/2);
        float x = center.x + radius * sin(time + increment * i);
        float y = center.y + radius * cos(time + increment * i);

        ofPushMatrix();
        ofTranslate(x, y);
        int childCount = 100;
        int childRadius = 300;
        float childIncrement = TWO_PI / childCount;
        for (int j = 0; j < childCount; j++) {
            x = childRadius * sin(-time + childIncrement * j);
            y = childRadius * cos(-time + childIncrement * j);
            ofDrawCircle(x, y, 2);
        }

        ofPopMatrix();


    }
    ofPopStyle();

}

void ofApp::drawLoop9() {

    float time = ofGetElapsedTimef() * 0.01;
    int count = 80;

    float rowoffset = 30;
    float increment = TWO_PI / count;
    float innerRadius = 480;

    ofPushStyle();
    ofColor color = ofColor::fromHex(0xAAAAAA);
    color.r += 100 * sin(time);
    color.g += 100 * cos(time * 0.36);
    color.b += 100 * sin(time * 0.96);

    ofSetColor(color, 230);

    for (int i = 0; i < count; i++) {
        float radius = innerRadius + sin(time * 0.6) * 200;
        float x = center.x + radius * sin(time + increment * i);
        float y = center.y + radius * cos(time + increment * i);

        ofPushMatrix();
        ofTranslate(x, y);
        int childCount = 100;
        int childRadius = 330;
        float childIncrement = TWO_PI / childCount;
        for (int j = 0; j < childCount; j++) {
            x = radius * sin(-time + childIncrement * j);
            y = radius * cos(-time + childIncrement * j);
            ofDrawCircle(x, y, 2);
        }

        ofPopMatrix();


    }
    ofPopStyle();
}

void ofApp::drawLoop10() {

    float time = ofGetElapsedTimef() * 0.01;
    int count = 80;

    float rowoffset = 40;
    float increment = TWO_PI / count;
    float innerRadius = 480;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xF5CCE8), 230);

    for (int i = 0; i < count; i++) {
        float radius = innerRadius;
        float x = center.x + radius * sin(time + increment * i);
        float y = center.y + radius * cos(time + increment * i);

        ofPushMatrix();
        ofTranslate(x, y);
        int childCount = 40;
        int childRadius = 300;
        float childIncrement = TWO_PI / childCount;
        for (int j = 0; j < childCount; j++) {
            childRadius = childRadius + 100 * cos(3 * childIncrement * j)*sin(3 * childIncrement * j);
            x = childRadius * sin(-time + childIncrement * j);
            y = childRadius * cos(-time + childIncrement * j);
            ofDrawCircle(x, y, 2);
        }

        ofPopMatrix();
    }
    ofPopStyle();
}

void ofApp::drawLoop11() {

    float time = ofGetElapsedTimef() * 0.01;
//    float time = ofGetElapsedTimef() * ofMap(ofNoise(ofGetElapsedTimef() * 0.01), 0, 1, 0, 0.2);
    int count = 80;

    float rowoffset = 40;
    float increment = TWO_PI / count;
    float innerRadius = 480;

    ofPushStyle();
    ofColor color = ofColor::fromHex(0xF5CCE8);
    ofSetColor(color, 230);


    for (int i = 0; i < count; i++) {
        float radius = innerRadius + cos(time) * 200;
        float x = center.x + radius * sin(time + increment * i);
        float y = center.y + radius * cos(time + increment * i);

        ofPushMatrix();
        ofTranslate(x, y);
        int childCount = 120;
        int childRadius = 300;
        float childIncrement = TWO_PI / childCount;
        for (int j = 0; j < childCount; j++) {
            childRadius = childRadius + 100 * cos(3./5. * time);
            x = childRadius * sin(-time + childIncrement * j);
            y = childRadius * cos(-time + childIncrement * j);
            ofDrawCircle(x, y, 2 + sin(time));
        }

        ofPopMatrix();
    }
    ofPopStyle();
}

// counter clockwise spiral loop
void ofApp::drawLoop() {

    float time = ofGetElapsedTimef() * 0.1;
    int count = 30;
    int rows = 20;
    float rowoffset = 30;
    float increment = TWO_PI / count;
    float innerRadius = 80;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xF5CCE8), 150);

    for (int i = 0; i < count; i++) {

        for (int j = 0; j < rows; j++) {
            float radius = innerRadius + (j * rowoffset) + sin(time * 0.6) * 200;
            float x = center.x + radius * sin(time + increment * i - sin(time * 0.4) * j * 0.32);
            float y = center.y + radius * cos(time + increment * i - sin(time * 0.4) * j * 0.32);
            ofDrawCircle(x, y, 10);
        }
    }
    ofPopStyle();
}

// clockwise spiral loop
void ofApp::drawLoop1() {
    float time = -ofGetElapsedTimef() * 0.1 + 1;
    int count = 30;
    int rows = 20;
    float rowoffset = (sin(time) + 1) * 20;
    float increment = TWO_PI / count;
    float innerRadius = 80;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xEC9DED), 190);

    for (int i = 0; i < count; i++) {

        for (int j = 0; j < rows; j++) {
            float radius = innerRadius + (j * rowoffset) + (sin(time * 0.8) + 1) * 400;
            float x = center.x + radius * sin(time + increment * i + sin(time * 0.5) * j * 0.4);
            float y = center.y + radius * cos(time + increment * i + sin(time * 0.5) * j * 0.4);
            ofDrawCircle(x, y, 10);
        }
    }
    ofPopStyle();
}

// This draws a rose petal
void ofApp::drawLoop2() {
    float time = ofGetElapsedTimef() * 0.1;
    int count = 30;
    float increment = TWO_PI / count;
    float innerRadius = 200;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xC880B7), 190);

    for (int i = 0; i < count; i++) {
//      This line below was a bug but introduces an interesting effect where all 'points'
//      collapse to origin
//        float t = time * increment * i;
        float t = time + increment * i;
        float radius = innerRadius + innerRadius * cos(6 * t);
        float x = center.x + radius * cos(t);
        float y = center.y + radius * sin(t);

        ofDrawCircle(x, y, 10);
    }
    ofPopStyle();
}

void ofApp::drawLoop3() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 30;
    int rows = 100;
    int rowOffset = 20;
    float increment = TWO_PI / count;
    float innerRadius = 100;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0x9F6BA0), 190);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < rows; j++) {
            float radius = innerRadius + (j * rowOffset) + -cos(time) * 100;
            float x = center.x + radius * sin(time + increment * i + j * 0.09);
            float y = center.y + radius * cos(time + increment * i + j * 0.09);
            ofDrawCircle(x, y, 8);
        }
    }
    ofPopStyle();
}

void ofApp::drawLoop4() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 32;
    int rows = 90;
    int rowOffset = 20;
    float increment = TWO_PI / count;
    float innerRadius = 70;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0x4A2040), 190);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < rows; j++) {
            float radius;
            if (time < 4) {
                radius = innerRadius + (j * rowOffset);
            } else {
                radius = innerRadius + (j * rowOffset) + -cos(time) * 100;
            }
            float x = center.x + radius * sin(time + increment * i + j * 0.1);
            float y = center.y + radius * cos(time + increment * i + j * 0.1);
            ofDrawCircle(x, y, 8);
        }
    }
    ofPopStyle();
}

// another more complicated rose petal
void ofApp::drawLoop5() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 14;
    int rows = 20;
    float increment = TWO_PI / count;
    float innerRadius = 400;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xFAE7F4), 100);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < rows; j++) {
            float t = time + increment * i;
            float radius = innerRadius + innerRadius * cos(5.0/6.0 * t);
            float x = center.x + radius * sin(time + increment * i + sin(j) * -3.5);
            float y = center.y + radius * cos(time + increment * i + sin(j) * -3.5);
            ofDrawCircle(x, y, 10);
        }
    }
    ofPopStyle();
}

// even more rose petals
void ofApp::drawLoop6() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 54;
    int rows = 10;
    float increment = (TWO_PI * 7) / count;
    float innerRadius = 300;

    ofPushStyle();
    ofSetColor(ofColor::fromHex(0xD6C2D6), 100);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < rows; j++) {
            float t = time + increment * i;
            float radius = 100 + innerRadius * cos(-time + 4.0/7.0 * increment * i);
            float x = center.x + radius * sin(t);
            float y = center.y + radius * cos(t);
            ofDrawCircle(x, y, 10);
        }
    }
    ofPopStyle();
}

// even more rose petals
void ofApp::drawLoop7() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 84;
    float increment = (TWO_PI * 7) / count;
    float innerRadius = 900;

    ofPushStyle();
    ofColor color = ofColor::fromHex(0x916292, 120);
    color.r += 30 * sin(time * 0.4);
    color.g += 30 * sin(time * 1.4);
    color.b += 30 * sin(time * 1.34);

    for (int i = 0; i < count; i++) {
        float t = time + increment * i;
        float radius = 100 + innerRadius * cos(time + 5.0/7.0 * increment * i);
        float x = center.x + radius * sin(t);
        float y = center.y + radius * cos(t);
        ofDrawCircle(x, y, 10);
    }
    ofPopStyle();
}

void ofApp::drawLoop8() {
    float time = ofGetElapsedTimef() * 0.2;
    int count = 104;
    float increment = (TWO_PI * 7) / count;
    float innerRadius = 300;

    ofPushStyle();
    ofColor color = ofColor::fromHex(0x441E3B, 120);
    color.r += 30 * sin(time * 1.4);
    color.g += 30 * sin(time * 1.2);
    color.b += 30 * sin(time * 1.8);

    for (int i = 0; i < count; i++) {

        float t = time + increment * i;
        float radius = 100 + innerRadius * cos(-time + 7.0/9.0 * increment * i);
        float x = center.x + radius * sin(t);
        float y = center.y + radius * cos(t);
        ofDrawCircle(x, y, 10);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int index = 0;
    switch(key) {
        case '0':
            index = 0;
            break;
        case '1':
            index = 1;
            break;
        case '2':
            index = 2;
            break;
        case '3':
            index = 3;
            break;
        case '4':
            index = 4;
            break;
        case '5':
            index = 5;
            break;
        case '6':
            index = 6;
            break;
        case '7':
            index = 7;
            break;
        case '8':
            index = 8;
            break;
        case '9':
            index = 9;
            break;
        case 'a':
            index = 10;
            break;
        case 'b':
            index = 11;
            break;
    }
    loops[index] = !loops[index];
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
