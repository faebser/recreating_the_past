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


        array<ofVec2f, 32> points;
        array<ofVec2f, 32> points2;
        const float step = PI / 32;
        float getx ( float origin, float radius, float angle );
        float gety ( float origin, float radius, float angle );

        ofxPanel general;
        ofxPanel circleA;
        ofxPanel circleB;
        ofParameter< int > blend;
        ofParameter< float > radiusA;
        ofParameter< float > scaleXA;
        ofParameter< float > scaleYA;

        ofParameter< float > radiusB;
        ofParameter< float > scaleXB;
        ofParameter< float > scaleYB;
};
