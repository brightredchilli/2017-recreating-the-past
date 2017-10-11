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
    ofTrueTypeFont font;
    vector<ofTTFCharacter> characters;
    std::string stringToUse;
    ofPoint originOffsetForCharacters(const std::string &s);
    void loadCharacters(const std::string &s);
    void drawStringCentered(const std::string &s, float x, float y);
		
};
