#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "HexagonTrack.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);

private:
    ofxPanel gui;
    ofxFloatSlider track2Cos;
    ofxFloatSlider track2Sin;
    bool debugTrails;
    float time;

    HexagonTrack1 hexagonTrack1;
    HexagonTrack1 hexagonTrack2;
    HexagonTrack1 hexagonTrack3;
};
