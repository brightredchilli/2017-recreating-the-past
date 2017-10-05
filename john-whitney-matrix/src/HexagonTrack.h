//
//  HexagonTrack.h
//  john-whitney-matrix
//
//  Created by Ying Quan Tan on 9/30/17.
//

#ifndef HexagonTrack_h
#define HexagonTrack_h
#include "ofMain.h"

#define IsInvalidSpacing(x) (x < 0.0)
#define InvalidSpacing  -1.0

class HexagonTrack {
protected:
    float numItems; // float for easy division
    float count;
    float baseSize;
    float spacingRatio;
    ofPoint center;

    HexagonTrack() {
        numItems = 7;
        count = numItems - 1;
        baseSize = 50;
        spacingRatio = 0.26;
        center.set(ofGetWidth()/2, ofGetHeight()/2);
    }

    void drawShape(ofPoint location, float size) {
        ofPushMatrix();
        ofSetCircleResolution(6);
        ofTranslate(location.x, location.y);
        ofRotateDeg(30);
        ofDrawCircle(0, 0, size);
        ofPopMatrix();
    }

    // Figures out the location of each point,
    virtual ofPoint location(float time) = 0;

    // and the spacing between each of the tracks
    virtual float spacing(float time, int i) {
        return defaultSpacing(time, i);
    }

    // Figures out the size of each hexagon
    virtual float size(float time, int i) {
        return baseSize;
    }

public:
    // draw the actual thing
    void draw(float time) {
        for(int i = 0; i < numItems; i++) {
            float count = numItems - 1;
            float timeForIndex = spacing(time, i);
            ofPoint t = location(timeForIndex);
            float shapeSize = size(timeForIndex, i);
            drawShape(t, shapeSize);
        }
    }

    // collapses the spacing from the 'default'
    float freezeSpacing(float time, int i, float target, float duration) {
        if (time >= target && time < target+duration) {
            return time + i * spacingRatio * invParabola((time - target) / duration);
        } else {
            return InvalidSpacing;
        }
    }

    // default spacing
    virtual float defaultSpacing(float time, int i) {
        return time + i * spacingRatio;
    }

    //utility functions
    float parabola(float x) {
        float k = 4.0;
        return pow( 4.0*x*(1.0-x), k);
    }

    float invParabola(float x) {
        return 1 - parabola(x);
    }
};

class HexagonTrack1 : public HexagonTrack {
protected:


    ofPoint location(float time) {
        // make time stop, and even go backwards
        float r = ofGetWidth() * .25; // ~ 200 - 300
        float x = center.x + r * sin(time * 1.0);
        float y = center.y + r * cos(time * 1.0);
        return ofPoint(x, y);
    }

    // and the spacing between each of the tracks
    float spacing(float time, int i) {
        float freeze = freezeSpacing(time, i, 4, 5);
        if (!IsInvalidSpacing(freeze)) {
            return freeze;
        }
        return defaultSpacing(time, i);
    }

    float size(float time, int i) {
        float count = numItems - 1;
        return baseSize + 40 * cos((count - i)/(count) * HALF_PI);
    }
};

class HexagonTrack2 : public HexagonTrack {
protected:
    ofPoint location(float time) {
        float r = ofGetWidth() * .18;
        float x = center.x + r * (sin(time * 1) + sin(time * 3));
        float y = center.y + r * (cos(time * 1) + sin(time * 2));
        return ofPoint(x, y);
    }

    // and the spacing between each of the tracks
    float spacing(float time, int i) {
        float freeze = freezeSpacing(time, i, 4, 5);
        if (!IsInvalidSpacing(freeze)) {
            return freeze;
        }
        return defaultSpacing(time, i);
    }

    float size(float time, int i) {
        return baseSize + 40 * cos((count-i)/(count) * HALF_PI);
    }
};

class HexagonTrack3 : public HexagonTrack {
protected:
    ofPoint location(float time) {
        float r = ofGetWidth() * .18;
        float x = center.x + r * cos(time * 1.0 + sin(time) * 0.3);
        float y = center.y + r * sin(time * 1.6  + sin(time) * 0.8);
        return ofPoint(x, y);
    }

    // and the spacing between each of the tracks
    float spacing(float time, int i) {
        float freeze = freezeSpacing(time, i, 4, 5);
        if (!IsInvalidSpacing(freeze)) {
            return freeze;
        }
        return defaultSpacing(time, i);
    }

    float size(float time, int i) {
        return baseSize + 40 * cos((count-i)/(count) * HALF_PI);
    }
};


#endif /* HexagonTrack_h */
