#pragma once

#include "ofMain.h"
#import "ofxCsv.h"
#import "ofxGui.h"

struct ScalePoint {
    float x, y; // bottom left coordinates
    float scale;

    ScalePoint(float x, float y, float scale) : x(x), y(y), scale(scale)
    {
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );

    ofxCsv csv;
    ofxCsv recorder;
    ofPoint center;
    ofTrueTypeFont font;
    vector<ofMesh> meshOutlines;
    vector<ScalePoint> csvScalePoints;
    string myString;
    ofxPanel panel;
    ofParameter < float > initialScale;
    ofParameter < float >initialScaleBy;
    float textToScreenWidthRatio;
    float textBounds;

    bool recording;
    void drawDownwards();
    void drawTexts(vector<ScalePoint> scalePoints);
};
