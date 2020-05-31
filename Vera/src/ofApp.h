#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        ofMatrix3x3* matrix;
        ofVec2f* margins;
        const float marginScale = 1.25f;
        const float quadSize = 80;
        const float range = 13.0;

        array<ofVec2f, 4> getRandomPoints( float range, float quadSize );
        float r( float range );

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

};
