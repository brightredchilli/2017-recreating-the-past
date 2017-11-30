#include "ofApp.h"
#include "EasingFunctions.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
//    ofSetBackgroundAuto(false);
    font.load("AkzidenzGrotesk-BoldExtended.otf", 100, true, false, true, 0.000001);
    myString = "ROBOT";
    vector<ofTTFCharacter> characters = font.getStringAsPoints(myString);
    meshOutlines.clear();
    for (ofTTFCharacter c : characters) {
        meshOutlines.push_back(c.getTessellation());
    }
    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    textToScreenWidthRatio = ofGetWidth()/bounds.width;
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    center /= textToScreenWidthRatio;

    csv.load(myString + "-scalepoints.csv");
    for (ofxCsvRow row : csv) {
        ScalePoint point(row.getFloat(0), row.getFloat(1), row.getFloat(2));
        csvScalePoints.push_back(point);
    }

    initialScale.set("scale", 0.7408, 0.718, 0.9);
    initialScaleBy.set("scale by", 0.0434, 0.04, 0.1);

    panel.setup();
    panel.add(initialScale);
    panel.add(initialScaleBy);
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    if (csvScalePoints.size() > 0) {
        drawTexts(csvScalePoints);
    } else {
        drawDownwards();
    }

    ofPopMatrix();
    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }

//    panel.draw();
}

void ofApp::drawDownwards() {
    float startTime = ofGetElapsedTimef();
    ofPushMatrix();
    ofScale(textToScreenWidthRatio, textToScreenWidthRatio);
    recorder.clear();

    auto bounds = font.getStringBoundingBox(myString, 0, 0);
    bounds.x = center.x - bounds.width/2 - bounds.x;
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
        ofPushStyle();
        ofSetColor(200, count*20, count*20, 100);
        ofDrawRectangle(newBounds.x, newBounds.y, newBounds.width, newBounds.height);
        ofPopStyle();

        ofPushMatrix();
        ofTranslate(newBounds.getBottomLeft());
        ofScale(out, out);
        for (ofMesh mesh : meshOutlines) {
            mesh.draw();
        }
        ofxCsvRow row;
        row.addFloat(newBounds.getBottomLeft().x);
        row.addFloat(newBounds.getBottomLeft().y);
        row.addFloat(out);
        recorder.addRow(row);

        ofPopMatrix();

        previousBounds = newBounds;
        t *= scale;
        scale += scaleBy * (t);
        if (scale >= 1) {
            scale = 1;
        }
        count++;

        // do a gut check, if we have spent too much time in this frame, bail.

        if (ofGetElapsedTimef() - startTime > 1.0) {
            break;
        }
    }

    ofPopMatrix();
    recorder.save(myString + "-scalepoints.csv");
}

void ofApp::drawTexts(vector<ScalePoint> scalePoints) {
    ofPushMatrix();
    ofScale(textToScreenWidthRatio, textToScreenWidthRatio);

    float duration = 2;
    float time = fmod(ofGetElapsedTimef(), duration);
    float pct = ofMap(time, 0, duration, 0, 1);

    for (int i = 0; i < scalePoints.size() - 1; i++) {
        ScalePoint current = scalePoints[i];
        ScalePoint next = scalePoints[i+1];

        float xLerped = ofMap(pct, 0, 1, current.x, next.x);
        float yLerped = ofMap(pct, 0, 1, current.y, next.y);
        float scaleLerped = ofMap(pct, 0, 1, current.scale, next.scale);
        ofPushMatrix();
        ofTranslate(xLerped, yLerped);
        ofScale(scaleLerped, scaleLerped);
        for (ofMesh mesh : meshOutlines) {
            mesh.draw();
        }
        ofPopMatrix();
    }
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x') {
        recording = !recording;
    }

    if (key == 's') {
        panel.saveToFile("settings.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    initialScale = ofMap(mouseX, 0, ofGetWidth(), initialScale.getMin(), initialScale.getMax());
    initialScaleBy = ofMap(mouseY, 0, ofGetHeight(), initialScaleBy.getMin(), initialScaleBy.getMax());
}
