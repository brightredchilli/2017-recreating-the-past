#include "ofApp.h"

struct FloatComparator : public std::unary_function<float, bool> {
    float needle;
    float epsilon;
    explicit FloatComparator(const float &needle, float epsilon) : needle(needle), epsilon(epsilon) {}
    bool operator() (const float arg) {
        return abs(arg - needle) < epsilon;
    }
};

struct PointComparator : public std::unary_function<ofPoint, bool> {
    ofPoint needle;
    float epsilon;
    explicit PointComparator(const ofPoint &needle, float epsilon) : needle(needle), epsilon(epsilon) {}
    bool operator() (const ofPoint &arg) {
        return (arg - needle).length() < epsilon;
    }
};

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("SF.otf", 200, true, true, true);
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    ofBackground(0);
    string stringToUse = "SFPC";
    bounds = font.getStringBoundingBox(stringToUse, 0, 0);
    auto offset = ofPoint(-bounds.width/2, bounds.height/2);
    scale = (ofGetWidth() * 0.8)/bounds.width;

    mesh.setMode(OF_PRIMITIVE_POINTS);

    characters = font.getStringAsPoints(stringToUse);

    for (ofTTFCharacter shape : characters) {
        vector<ofPolyline> lines = shape.getOutline();
        for (ofPolyline line : lines) {
            line = line.getResampledBySpacing(5);
            for (ofPoint point : line) {
                mesh.addVertex(point);

                bool pointInVector = find_if(xPoints.begin(), xPoints.end(), FloatComparator(point.x, 5)) != xPoints.end();
                if (!pointInVector) {
                    xPoints.push_back(point.x);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();

    // each 3rd frame make a new droplet
    if (ofGetFrameNum() % 3 == 0) {
        float xOffset = xPoints[floor(ofRandom(xPoints.size()))];
        points.push_back(ofVec3f(xOffset, -5, time));
    }

    map
    
//    mesh.clear();
    mesh.clearColors();
    int count;
    for (ofTTFCharacter shape : characters) {
        vector<ofPolyline> lines = shape.getOutline();
        for (ofPolyline line : lines) {
            line = line.getResampledBySpacing(5);
            for (ofPoint point : line) {
                float hue = fmod(time * 0.8 + (float)count * 0.01, 1);
                mesh.addColor(ofFloatColor::fromHsb(hue, 0.7, 1));
                count++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(center.x - (bounds.width/2 + bounds.x) * scale, center.y + (bounds.height/2) * scale);
    ofScale(scale, scale);
    mesh.draw();
    ofPopMatrix();
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
