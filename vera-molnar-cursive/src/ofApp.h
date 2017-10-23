#pragma once

#include "ofMain.h"
#include "ofxPanel.h"

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

private:
    ofxPanel panel;
    ofParameterGroup group;
    ofParameter < float > slider1;
    ofParameter < float > slider2;

    bool recording;
    int currentCP;
    vector <ofPoint> controlPoints;
};
