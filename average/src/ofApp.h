#pragma once

#include "ofMain.h"
#include "ofxPoissonDiskSampling.h"

class imageWithData {

    public:
        ofImage img;

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
        bool draw_if_close_enough( ofVec2f center, ofVec2f k );

        vector<ofVec2f> m_samples;
        float m_density;
        ofVec2f center;

        vector< ofImage > images;
        ofImage average;
};
