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
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);

    bool recording = false;
    ofPoint center;
    ofPoint signedRandomPoint();

    void drawSineWave();
    void drawCurve(bool smooth);
    void drawStraightWithIntersection();
};
