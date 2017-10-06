#pragma once

#include "ofMain.h"
#include "ofxBlur.h"


class RosePetalDrawer {
protected:
    int count = 5;
    int rows = 1;
    float increment = TWO_PI / count;
    float innerRadius = 100;
    float shapeSize = 10;
    ofPoint center;

    virtual ofColor color(float time) {
        return ofColor(0,0,0);
    };

    virtual void drawShape(float x, float y) {
        ofDrawCircle(x, y, shapeSize);
    }

public:
    RosePetalDrawer(int count,
                    int rows,
                    float innerRadius,
                    float shapeSize,
                    float phase = TWO_PI)
    : count(count),
    rows(rows),
    increment(phase/(float)count),
    innerRadius(innerRadius) {
        center.set(ofGetWidth() / 2, ofGetHeight() / 2);
    }

    virtual void draw(float time) {

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
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

protected:
    void drawLoop();
    void drawLoop1();
    void drawLoop2();
    void drawLoop3();
    void drawLoop4();
    void drawLoop5();
    void drawLoop6();
    void drawLoop7();
    void drawLoop8();
    void drawLoop9();
    void drawLoop10();
    void drawLoop11();
    void drawLoop12();
    int numLoops;

    vector<bool> loops;
    ofPoint center;
    ofxBlur blur;
		
};
