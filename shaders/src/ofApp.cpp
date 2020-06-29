#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    shaderBlurX.load("shadersGL3/shaderBlurX");
    shaderBlurY.load("shadersGL3/shaderBlurY");

    image.load("img.jpg");

    fboBlurOnePass.allocate(image.getWidth(), image.getHeight());
    fboBlurTwoPass.allocate(image.getWidth(), image.getHeight());

    init.allocate( image.getWidth(), image.getHeight() );

    init.begin();
        ofBackground(0);
        ofSetColor( ofColor::white );
        ofDrawRectangle( 100, 100, 50, 50 );
    init.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 4, true);

    //----------------------------------------------------------
    fboBlurOnePass.begin();

    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);

    init.draw(0, 0);

    shaderBlurX.end();

    fboBlurOnePass.end();

    cout << "finished first pass" << endl;

    //----------------------------------------------------------
    fboBlurTwoPass.begin();

    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);

    fboBlurOnePass.draw(0, 0);

    shaderBlurY.end();

    fboBlurTwoPass.end();

    //----------------------------------------------------------
    ofSetColor(ofColor::white);
    //fboBlurTwoPass.draw(0, 0);

    fboBlurOnePass.draw(0, 0);

    init.draw( fboBlurTwoPass.getWidth(), 0 );

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
