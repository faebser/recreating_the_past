#pragma once

#include "ofMain.h"
#include "screenshot.hpp"
#include "tree.h"

struct Node
{
    ofRectangle rect;
    ofFbo fbo;
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

        void drawLines(ofRectangle rect, ofFbo fbo, bool direction);

        void take();

        ofFbo fbo;
        ofFbo fboBorder;

        ofRectangle top;

        vector< ofRectangle > rects;
        vector< ofFbo > fbos;

        glm::vec4 size;
        tree< Node* > rectTree;
        tree< Node* >::iterator top_it;

        vector< Node > nodes;


        bool screen_taken = false;
};
