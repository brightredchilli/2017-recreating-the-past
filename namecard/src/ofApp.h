#pragma once

#include "ofMain.h"

#include "ofxVoronoi.h"
//#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

class Highpass {
public:
    cv::Mat lab, lowpass, highpass;
    vector<cv::Mat> labChannels;

    template <class S, class D>
    void filter(S& src, D& dst, int size, float contrast = 1) {
        ofxCv::convertColor(src, lab, CV_RGB2Lab);
        cv::split(lab, labChannels);
        cv::Mat& lightness = labChannels[0];
        ofxCv::blur(lightness, lowpass, size);
        // could convert to 16s instead of 32f for extra speed
        cv::subtract(lightness, lowpass, highpass, cv::noArray(), CV_32F);
        if (contrast != 1) {
            highpass *= contrast;
        }
        highpass += 128; // should be diff for other datatypes
        highpass.convertTo(lightness, lightness.type());
        ofxCv::imitate(dst, src);
        cv::merge(labChannels, ofxCv::toCv(dst));
        ofxCv::convertColor(dst, dst, CV_Lab2RGB);
    }
};

class ofApp : public ofBaseApp{



	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );

    ofRectangle      bounds;
    vector <ofPoint> points;
    ofxVoronoi       voronoi;
    ofFbo voronoiFbo;
    ofImage baseImage;
    ofImage grayImage;
    ofImage thresholdedImage;
    ofImage outputImage;
    ofImage voronoiImage;
    ofImage voronoiThresholdImage;
    int * distanceMap;
    int highestDistance;
    ofxPanel gui;
    ofParameter<float> threshold;
    ofParameter<float> size, contrast;
    ofColor targetColor;
    ofPolyline contourPolyline;

    Highpass highpass;
    ofImage filtered;
    
    ofxCv::ContourFinder contourFinder;

    bool recording;



    void setThresholdedImageFromDistanceMap();
    vector <ofPoint>  generateRandomPoints(int count, int seed, ofRectangle bounds);
    void drawVoronoi();
    void setUpVoronoi();
    void populateDistanceMap(ofPoint fromPoint);
    int distanceAtPoint(ofPoint point);
    void setDistanceAtPoint(ofPoint point, int distance);
    bool pointValid(ofPoint point, ofRectangle bounds);
    void pushIntoQueueIfValid(ofPoint point,
                              ofRectangle bounds,
                              std::queue<ofPoint> &queue,
                              int distance);
		
};

void adjustGamma(cv::Mat& img, float gamma = 0.5);

