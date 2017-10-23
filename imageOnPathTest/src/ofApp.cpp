#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    test.load("test.png");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);
    
    ofSetColor(0);
    myLine.draw();
    
    ofPolyline tempLine = myLine;
    tempLine = tempLine.getResampledBySpacing(50);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    for (int i = 0; i < tempLine.size(); i++){
        // grab the point ahead and behind to figure out the angle.
        int i_m_1 = MAX(i - 1, 0);
        int i_p_1 = MIN(i + 1, tempLine.size()-1);
        ofPoint diff = tempLine[i_p_1] - tempLine[i_m_1];
        float angle = atan2(diff.y, diff.x);
        ofPushMatrix();
        ofTranslate(tempLine[i]);
        ofRotate(angle*RAD_TO_DEG + 90, 0, 0, 1);
        ofScale(0.3, 0.3);
        test.draw(0,0);
        ofPopMatrix();
        
    }
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

    myLine.addVertex(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    myLine.clear();
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
