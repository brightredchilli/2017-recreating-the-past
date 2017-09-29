#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:
    ofxPanel gui;
    ofxFloatSlider track2Cos;
    ofxFloatSlider track2Sin;
    ofPoint center;
    ofPoint track1(float time);
    ofPoint track2(float time);
    ofPoint track3(float time);
    void drawHexagon(ofPoint point, float size);
    bool debugTrails;
		
};
