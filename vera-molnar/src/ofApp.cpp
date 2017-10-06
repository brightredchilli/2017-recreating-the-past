#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofSetLineWidth(0.1);
    setUpLines();
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
}

ofVec2f getRandomDirection() {
    // acording to vera molnar, the tilt angle was 120 to 150, which translates to
    // -60 to -30 going up, and 120 to 150 going down
    // this returns only 4 possible random numbers for base pairs

    float r = ofRandom(4);
    if (r < 1) {
        return ofVec2f(-55, 110);
    } else if (r < 2) {
        return ofVec2f(-45, 90);
    } else if (r < 3) {
        return ofVec2f(-38, 115);
    } else if (r < 4) {
        return ofVec2f(-31, 95);
    }
}

void ofApp::setUpLines() {
    ofSeedRandom(0);

    float lineHeight = 35;
    float padding = 50;
    float radius = 30;
    float maxWidth = ofGetWidth() - padding;
    float maxHeight = ofGetHeight() - padding;

    ofPoint pos = ofPoint(padding, padding + lineHeight);

    while (pos.y < maxHeight) {
        ofPolyline line;
        line.addVertex(pos);

        while (pos.x < maxWidth) {

            ofVec2f randomDirection = getRandomDirection();

            float angle = ofDegToRad(randomDirection.x);

            float x1 = radius * cos(angle);
            float y1 = radius * sin(angle);


            float angleDown = ofDegToRad(randomDirection.y);
            float x2 = x1 + radius * cos(angleDown);
            float y2 = y1 + radius * sin(angleDown);


            ofPoint point1 = ofPoint(x1, y1);
            ofPoint point2 = ofPoint(x2, y2);

            ofPoint intersection = ofPoint(0, 0);

            bool foundIntersection = ofLineSegmentIntersection(point1,
                                                               point2,
                                                               ofPoint(-10000, 0),
                                                               ofPoint(10000, 0),
                                                               intersection);
            if (foundIntersection) {
                point2 = intersection;
            }

            pos += point1;
            line.addVertex(pos);
            pos += point2 - point1;
            line.addVertex(pos);
        }

        // add the last point on the line, since it will be skipped if we exit the
        // while loop

        lines.push_back(line);

        pos.x = padding;
        pos.y += lineHeight;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    // for some reason, drawing is irresponsive in the first couple of frames. we just skip them.
    if (ofGetFrameNum() < 30) {
        return;
    }
    // draw the vertices one by one
    for (int i = 0; i <= verticesPerFrame; i++) {
        if (currentLine < lines.size()) {
            ofPolyline line = lines[currentLine];
            if (currentVertex + 1 < line.size()) {
                ofDrawLine(line[currentVertex], line[currentVertex + 1]);
                currentVertex++;
            } else {
                currentLine++;
                currentVertex = 0;
            }
        }
    }
    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }

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
