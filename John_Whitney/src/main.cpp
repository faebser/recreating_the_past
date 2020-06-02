#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ) {


    ofGLFWWindowSettings settings;
    // settings.setGLVersion(3,2);
    settings.resizable = false;
    settings.decorated = false;
    settings.setSize(1024, 768);
    ofCreateWindow(settings);

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
