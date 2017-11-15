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
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofTrueTypeFont font;
    ofPoint center;
    ofMesh mesh;
    ofRectangle bounds;
    vector <ofVec3f> points; // the z axis stores start time, a bit sneaky
    vector <float> xPoints;
    vector<ofTTFCharacter> characters;

    float scale;
		
};

