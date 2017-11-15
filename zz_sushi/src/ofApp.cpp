#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    dimensions = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    center.set(dimensions.getCenter());

    drawEvery = 2;
    imageScale = 0.0075;
    widthScale = 0.8;


    font.load("SF.otf", 200, true, true, true);

    ofBackground(0);
    string stringToUse = "sushi";
    bounds = font.getStringBoundingBox(stringToUse, 0, 0);
    auto offset = ofPoint(-bounds.width/2, bounds.height/2);
    scale = (dimensions.width * widthScale) /bounds.width;
    characters = font.getStringAsPoints(stringToUse);

    for (int i = 0; i < imageCount; i++) {
        char buf[10];
        sprintf(buf, "%d.png", i);
        images[i].load(buf);
    }
    sushiScale = dimensions.width / images[0].getWidth() * imageScale;
}

//--------------------------------------------------------------
void ofApp::update(){
//    drawEvery = ofMap(ofGetMouseX(), 0, dimensions.width, 2, 10);
//    imageScale = ofMap(ofGetMouseY(), 0, dimensions.height, 0.005, 0.01);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor backgroundColor = ofColor::fromHsb(fmod(ofGetElapsedTimef() * 2.0, 255), 200, 255);
    ofBackground(backgroundColor);

    ofPushStyle();

    // push matrix to center the text
    ofPushMatrix();
    ofTranslate(center.x - (bounds.width/2 + bounds.x) * scale, center.y + (bounds.height/2) * scale);
    ofScale(scale, scale);

//    ofNoFill();
//    ofDrawRectangle(bounds);

    for (ofTTFCharacter shape : characters) {
        vector<ofPolyline> lines = shape.getOutline();
        for (ofPolyline line : lines) {
            ofPolyline resampledLine = line.getResampledBySpacing(5);
            drawAlongLine(resampledLine);
        }
    }



    ofPopMatrix();
    ofPopStyle();
}

void ofApp::drawAlongLine(ofPolyline &polyline) {
    float size = polyline.size();
    float time = ofGetElapsedTimef() * 0.08;
    float length  = polyline.getLengthAtIndex(polyline.size()-1);
    int numberOfPointsToDraw = size / drawEvery; // draw every x points
    float increment = 1.0/numberOfPointsToDraw;

    int count = 0;
    float pct = 0.0;
    while(pct < 0.98) {

        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        float offset = fmod(pct + time, 1.0);
        float findex = polyline.getIndexAtPercent(offset);
        float fangle = polyline.getAngleAtIndexInterpolated(findex);

        int i_m_1 = fmod(findex - 1 + size, size);
        int i_p_1 = fmod(findex + 1 + size, size);

        ofPoint diff = polyline[i_p_1] - polyline[i_m_1];
        float angle = atan2(diff.y, diff.x);


//        ofPoint ftangent = polyline.getTangentAtIndexInterpolated(findex);
//        float deg = RAD_TO_DEG * acos(ftangent.y / ftangent.x);
//        cout << "deg" << deg << endl;
        ofPoint point = polyline.getPointAtPercent(offset);
        ofTranslate(point.x, point.y);
        ofRotate(angle * RAD_TO_DEG);
        ofScale(sushiScale, sushiScale);


//        sushiImage.draw(0, 0);
        images[count].draw(0, 0);

        ofPopMatrix();

        pct += increment;
        count = (count + 1) % imageCount;



    }

//    cout << "polyline.size(): " << polyline.size() << endl;
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
