#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );

    ofPoint center;
    ofTrueTypeFont font;
    vector<ofMesh> meshOutlines;
    string myString;
    float initialScale;
    float initialScaleBy;
    float textToScreenWidthRatio;
    float textBounds;

    bool recording;
    void drawMeshOutlines();
    void drawDownwards();
};
