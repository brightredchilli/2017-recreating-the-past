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

    ofRectangle dimensions;

    ofTrueTypeFont font;
    ofPoint center;
    ofRectangle bounds;
    vector<ofTTFCharacter> characters;
    ofImage sushiImage;

    float sushiScale;
    float scale;

    static int const imageCount = 14;
    ofImage images[imageCount];

    ofParameter <float> imageScale;
    ofParameter <float> widthScale;
    ofParameter <int> drawEvery;

    void drawAlongLine(ofPolyline &polyline);


};
