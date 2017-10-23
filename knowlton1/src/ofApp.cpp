#include "ofApp.h"
#include <algorithm>
#include <iterator>

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    camWidth = 640;
    camHeight = 480;
    res = 5;

    vidGrabber.setVerbose(true);
    vidGrabber.setPixelFormat(OF_PIXELS_RGBA);
    vidGrabber.setup(camWidth, camHeight);

    ofSetBackgroundAuto(false);
    targetImage.load("ying.png");
    targetImage.setImageType(OF_IMAGE_COLOR);

    int cols = targetImage.getWidth() / res;
    int rows = targetImage.getHeight() / res;
    targetScores = new unsigned char[cols * rows];
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(3,3);

    if (vidGrabber.isFrameNew() && sourceImage.isAllocated() && ofGetFrameNum() % 2 == 0 ) {
        targetImage = ofImage(vidGrabber.getPixels());
        ofImage &image = sourceImage;
        int cols = image.getWidth() / res;
        int rows = image.getHeight() / res;
        int positions = cols * rows;
        int bytesPerPixel = 3;
        unsigned char * targetPointer = targetImage.getPixels().getData();


        for (int it = 0; it < 1; it++) {
            for (int i = 0; i < image.getWidth(); i += res) {
                for (int j = 0; j < image.getHeight(); j += res) {
                    float previousTargetScore = targetScore;
                    int index = (j * image.getWidth() + i) * bytesPerPixel;
                    int x = i / res;
                    int y = j / res;

                    int randX = floor(ofRandom(cols)) * res;
                    int randY = floor(ofRandom(rows)) * res;
                    int randIndex = (randY * image.getWidth() + randX) * bytesPerPixel;

                    unsigned char * from = getSubImage(image, i, j, res);
                    unsigned char * to = getSubImage(image, randX, randY, res);

                    // calculate costs
                    float fromScore = distance(from, targetPointer + index);
                    float toScore = distance(to, targetPointer + randIndex);

                    float afterSwapFromScore = distance(to, targetPointer + index);
                    float afterSwapToScore = distance(from, targetPointer + randIndex);

                    if (fromScore + toScore < afterSwapFromScore + afterSwapToScore) {
                        // perform swap
                        setSubImage(image, i, j, res, to);
                        setSubImage(image, randX, randY, res, from);
                    }
                    delete[] from;
                    delete[] to;
                }
            }
        }

        image.update();
        image.draw(0, 0);
    }
    ofPopMatrix();

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
    }
}

unsigned char * ofApp::getSubImage(ofImage &image,
                                   int _x,
                                   int _y,
                                   int maskSize) {
    int bytesPerPixel = 3;
    unsigned char * subImage = new unsigned char[maskSize * maskSize * bytesPerPixel];
    unsigned char * data = image.getPixels().getData();

    int c = 0;
    for (int y = _y; y < _y + maskSize; y++) {
        for (int x = _x; x < _x + maskSize; x++) {
            int idx = y * image.getWidth()*bytesPerPixel + x*bytesPerPixel;
            for (int i = 0; i < bytesPerPixel; i++) {
                subImage[c + i] = data[idx + i];
            }
            c += bytesPerPixel;
        }
    }
    return subImage;
}


void ofApp::setSubImage(ofImage &image,
                        int _x,
                        int _y,
                        int maskSize,
                        unsigned char * subImage) {
    int bytesPerPixel = 3;
    unsigned char * data = image.getPixels().getData();
    int c = 0;
    for (int y = _y; y < _y + maskSize; y++) {
        for (int x = _x; x < _x + maskSize; x++) {
            int idx = (y * image.getWidth() + x) * bytesPerPixel;
            for (int i = 0; i < bytesPerPixel; i++) {
                data[idx + i] = subImage[c + i];
            }
            c += bytesPerPixel;
        }
    }
}

float ofApp::distance(unsigned char * pixel1,
               unsigned char * pixel2) {

    float r1 = pixel1[0];
    float g1 = pixel1[1];
    float b1 = pixel1[2];

    float r2 = pixel2[0];
    float g2 = pixel2[1];
    float b2 = pixel2[2];

    float dist = abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
    dist /= (255*3);
    return dist;
}

float ofApp::getTargetScore() {
    
    float total = 0;
    int cols = targetImage.getWidth() / res;
    int rows = targetImage.getHeight() / res;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int score = targetScores[j * cols + i];
            total += score;
        }
    }
    return total;
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
//    sourceImage = ofImage(vidGrabber.getPixels());
//    sourceImage.setImageType(OF_IMAGE_COLOR);

    sourceImage.load("sources/coral.png");
    sourceImage.setImageType(OF_IMAGE_COLOR);
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
