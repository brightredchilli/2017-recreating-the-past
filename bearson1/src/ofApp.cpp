#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int imageW = 320;
    int imageH = 480;

    ofDirectory dir;
    dir.listDir("google_presidents");
//    dir.listDir("craigslist_ppp");

    cout << dir.getFiles().size() << endl;

    mix.allocate(imageW, imageH, OF_IMAGE_COLOR);

    int pixelSum[imageW * imageH * 3];
    for (int i = 0; i <imageW * imageH * 3; i++){
        pixelSum[i] = 0;
    }

    ofImage temp;
    temp.setUseTexture(false);
    int maxRedPixel = 0;
    for (int i = 0; i < dir.size(); i++){
        cout << "loading: " << dir.getPath(i) << endl;

        temp.load(dir.getPath(i));

        for (int j = 0; j < imageW; j++){
            for (int k = 0; k < imageH; k++){
                ofColor c = temp.getColor(j,k);
                int index = (k * imageW+ j) * 3;
                pixelSum[index] += c.r;
                pixelSum[index+1] += c.g;
                pixelSum[index+2] += c.b;

                if (maxRedPixel < pixelSum[index]) {
                    maxRedPixel = pixelSum[index];
                }
            }
            cout << "Max red pixel sum " << maxRedPixel << endl;
        }
    }

    float numImages = (float)dir.size(); // float for division operation
    for (int i = 0; i < imageW; i++){
        for (int j = 0; j < imageH; j++){

            ofColor c;
            int index = (j * imageW + i) * 3;
            c.r = (float)pixelSum[index] / numImages;
            c.g = (float)pixelSum[index+1] / numImages;
            c.b = (float)pixelSum[index+2] / numImages;
            mix.setColor(i,j, c);

        }
    }
    mix.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    mix.draw(0,0);
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
