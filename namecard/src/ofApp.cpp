#include "ofApp.h"
#import "EasingFunctions.hpp"

#define str(x) #x
string frag =
str(
    void main() {
        float alpha = max(mod(gl_Color.r * 10., 1.),
                          mod(gl_TexCoord[0].g * 10., 1.));
        gl_FragColor = vec4(gl_Color.rgb, alpha);
    }
    );

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {

    ofEnableSmoothing();
    setUpVoronoi();
    drawVoronoi();
    gui.setup("params", "settings.xml");
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(size.set("size", 80, 0, 128));
    gui.add(contrast.set("contrast", 1.5, .5, 5));
    gui.loadFromFile("settings.xml");

    targetColor = ofColor(40, 57, 38, 255);
//    targetColor = ofColor(38, 54, 41, 255);

    baseImage.load("plantmask.jpg");
    grayImage.setFromPixels(baseImage.getPixels());
    grayImage.setImageType(OF_IMAGE_GRAYSCALE);
    Mat gray = toCv(grayImage);
    adjustGamma(gray, 1.7);
    grayImage.update();
//    toOf(gray, grayImage.getPixels());

    distanceMap = NULL;

    ofImage source;
    source.load("plantmask.jpg");

    contourFinder.setTargetColor(targetColor, TRACK_COLOR_RGB);
    contourFinder.setMinAreaRadius(100);
    contourFinder.setMaxAreaRadius((int)baseImage.getWidth() * (int)baseImage.getHeight());
    contourFinder.setThreshold(threshold);

    highpass.filter(source, filtered, size, contrast);
    contourFinder.findContours(filtered);
    if (contourFinder.size() > 0) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        contourPolyline = contourFinder.getPolyline(0).getSmoothed(5);
        contourPolyline.draw();
        ofPopStyle();
        populateDistanceMap(ofPoint(1083, 1811));
        setThresholdedImageFromDistanceMap();
    }

    outputImage.load("plantmask.jpg");
    outputImage.getTexture().setAlphaMask(thresholdedImage.getTexture());

    // voronoiImage generated by drawVoronoiImage
    voronoiImage.getTexture().setAlphaMask(voronoiThresholdImage.getTexture());
}

void ofApp::setThresholdedImageFromDistanceMap() {

    int numElements = (int)baseImage.getWidth() * (int)baseImage.getHeight();
    unsigned char charDistanceMap[numElements];

//    for (int i = 0; i < numElements; i++) {
//        float normalized = (float)distanceMap[i] / (float)highestDistance;
//        charDistanceMap[i] = (int)(normalized * 255);
//    }
    thresholdedImage.clone(baseImage);
    thresholdedImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    unsigned char * data = thresholdedImage.getPixels().getData();

    voronoiThresholdImage.clone(baseImage);
    voronoiThresholdImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    unsigned char * voronoiThresholdData = voronoiThresholdImage.getPixels().getData();

    int stride = 4;
    //modify the alpha channel
    for (int i = 0; i < numElements; i++) {
        float val = (float)distanceMap[i] / (float)highestDistance;
        float normalized = function_SmootherStep(val);
        data[(i * stride)] = (int)(normalized * 255.0f);
        data[(i * stride) + 1] = (int)(normalized * 255.0f);
        data[(i * stride) + 2] = (int)(normalized * 255.0f);
        data[(i * stride) + 3] = (int)(normalized * 255.0f);

//        float voronoiNormalized = pow((float)distanceMap[i] / (float)highestDistance, 1.3);
        float voronoiNormalized = function_AdjustableSigmaHalfGaussian(val, 0.773);
        voronoiThresholdData[(i * stride)] = (int)(voronoiNormalized * 255.0f);
        voronoiThresholdData[(i * stride) + 1] = (int)(voronoiNormalized * 255.0f);
        voronoiThresholdData[(i * stride) + 2] = (int)(voronoiNormalized * 255.0f);
        voronoiThresholdData[(i * stride) + 3] = (int)(voronoiNormalized * 255.0f);
    }


//    thresholdedImage.setFromPixels(charDistanceMap, baseImage.getWidth(), baseImage.getHeight(), OF_IMAGE_RGBA);
    thresholdedImage.update();
    voronoiThresholdImage.update();
}

//--------------------------------------------------------------
void ofApp::update(){
//    grayDiff.setFromImage
//
    //    contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);


}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();
    ofScale(0.75, 0.75);
    ofBackground(255, 255);

//    baseImage.draw(0, 0);
    grayImage.draw(0, 0);
    outputImage.draw(0, 0);
    voronoiImage.draw(0, 0);

//    voronoiFbo.draw(0,0);
//
//
//    if (thresholdedImage.isAllocated()) {
//        thresholdedImage.draw(0, 0);
//    }
//
//    if (contourFinder.size() > 0) {
//        ofPushStyle();
//        ofSetColor(255, 0, 0);
//        contourFinder.getPolyline(0).getSmoothed(5).draw();
//        ofPopStyle();
//    }

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
        recording = false;
    }

    // make frame rate a lit
    ofPushMatrix();
    ofDrawBitmapString(ofGetFrameRate(), 10, 100);
    ofDrawBitmapString(contourFinder.size(), 10, 200);
    ofPopMatrix();
    gui.draw();
    ofPopMatrix();

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'c') {
        int x = mouseX;
        int y = mouseY;
        if (x < baseImage.getWidth() && y < baseImage.getHeight()) {
            targetColor = baseImage.getColor(x, y);
            cout << targetColor << endl;
            // 40, 57, 38, 255
        }
    } else if (key == 't') {
        threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    }

    if (key == 'x') {
        recording = !recording;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

void ofApp::setUpVoronoi() {
    ofRectangle bounds = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());

    int pointCount = 800;
    int seed = 33;

    points = generateRandomPoints(pointCount, seed, bounds);

    voronoi.setBounds(bounds);
    voronoi.setPoints(points);

    voronoi.generate();

    points.clear();
    for(auto cell : voronoi.getCells()) {
        points.push_back(cell.pt);
    }
}

void ofApp::drawVoronoi() {

    ofRectangle bounds = voronoi.getBounds();
    if (!voronoiFbo.isAllocated()) {
        voronoiFbo.allocate(bounds.width, bounds.height, GL_RGBA);
    }
    voronoiFbo.begin();

    ofClear(0, 0, 0, 0);
    ofPushMatrix();

    ofPushStyle();
    ofSetLineWidth(2);
    ofNoFill();
    ofSetColor(0);
    //    ofDrawRectangle(bounds);

    vector <ofxVoronoiCell> cells = voronoi.getCells();
    for(int i=0; i<cells.size(); i++) {
        ofSetColor(255);
        ofNoFill();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        mesh.addVertices(cells[i].pts);
        mesh.draw();

        mesh.clear();
        //        for(int j = 0; j < cells[i].pts.size(); j++) {
        //            mesh.addVertex(cells[i].pt);
        //            mesh.addVertex(cells[i].pts[j]);
        //        }
        //        ofSetColor(120);
        //        mesh.draw();

        // Draw cell points
        //        ofSetColor(ofColor::fromHsb(255. * i / cells.size(), 255., 255.));
        //        ofFill();
        //        ofDrawCircle(cells[i].pt, 2);
    }
    ofPopStyle();
    ofPopMatrix();
    voronoiFbo.end();

    voronoiImage.allocate(baseImage.getWidth(), baseImage.getWidth(), OF_IMAGE_COLOR_ALPHA);
    voronoiFbo.readToPixels(voronoiImage.getPixels());
    voronoiImage.update();
}

vector <ofPoint> ofApp::generateRandomPoints(int count, int seed, ofRectangle bounds) {
    vector <ofPoint> points;
    ofSeedRandom(seed);

    for(int i=0; i<count; i++) {
        ofPoint newPoint = ofPoint(
                                   ofRandom(bounds.x, bounds.width),
                                   ofRandom(bounds.y, bounds.height)
                                   );

        points.push_back(newPoint);
    }

    return points;
}

void ofApp::populateDistanceMap(ofPoint fromPoint) {
    int width = baseImage.getWidth();
    int height = baseImage.getHeight();
    if (distanceMap == NULL) {
        distanceMap = (int *) malloc(sizeof(int) * width * height);
    }
    memset(distanceMap, 0, sizeof(int) * width * height);
    std::queue <ofPoint> queue;
    queue.push(fromPoint);
    setDistanceAtPoint(fromPoint, 1);

    ofRectangle bounds = ofRectangle(0, 0, width, height);
    

    while (!queue.empty()) {
        ofPoint point = queue.front();
        queue.pop();
        int nextDistance = distanceAtPoint(point) + 1;
        if (nextDistance > highestDistance) {
            highestDistance = nextDistance;
        }


        // look in all 8 boxes surrounding this point.

        ofPoint topLeft = point + ofPoint(-1, -1);
        pushIntoQueueIfValid(topLeft, bounds, queue, nextDistance);

        ofPoint top = point + ofPoint(0, -1);
        pushIntoQueueIfValid(top, bounds, queue, nextDistance);

        ofPoint topRight = point + ofPoint(1, -1);
        pushIntoQueueIfValid(topRight, bounds, queue, nextDistance);

        ofPoint right = point + ofPoint(1, 0);
        pushIntoQueueIfValid(right, bounds, queue, nextDistance);

        ofPoint bottomRight = point + ofPoint(1, 1);
        pushIntoQueueIfValid(bottomRight, bounds, queue, nextDistance);

        ofPoint bottom = point + ofPoint(0, 1);
        pushIntoQueueIfValid(bottom, bounds, queue, nextDistance);

        ofPoint bottomLeft = point + ofPoint(-1, 1);
        pushIntoQueueIfValid(bottomLeft, bounds, queue, nextDistance);

        ofPoint left = point + ofPoint(-1, 0);
        pushIntoQueueIfValid(left, bounds, queue, nextDistance);
    }
}

bool ofApp::pointValid(ofPoint point, ofRectangle bounds) {
    bool isValid = bounds.inside(point) &&
    distanceAtPoint(point) == 0 &&
    contourPolyline.inside(point);
//    baseImage.getColor(point.x, point.y).getBrightness() < threshold;
    return isValid;
}

int ofApp::distanceAtPoint(ofPoint point) {
    int width = baseImage.getWidth();
    int height = baseImage.getHeight();
    int distance = distanceMap[width * (int)point.y + (int)point.x];
    return distance;
}

void ofApp::setDistanceAtPoint(ofPoint point, int distance) {
    int width = baseImage.getWidth();
    int height = baseImage.getHeight();
    distanceMap[width * (int)point.y + (int)point.x] = distance;
}

void ofApp::pushIntoQueueIfValid(ofPoint point,
                                 ofRectangle bounds,
                                 std::queue<ofPoint> &queue,
                                 int distance) {
    if (pointValid(point, bounds)) {
        setDistanceAtPoint(point, distance);
        queue.push(point);
    }
}

void adjustGamma(cv::Mat& img, float gamma) {
    cv::Mat lookUpTable(1, 256, CV_8U);
    unsigned char* p = lookUpTable.ptr();
    for (int i = 0; i < 256; i++) {
        p[i] = saturate_cast<unsigned char>(pow(i / 255.0, gamma) * 255.0);
    }
    cv::LUT(img, lookUpTable, img);
}


