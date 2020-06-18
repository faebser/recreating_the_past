#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cobol.load("bauhaus.ttf",50, true, true, true);

    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {

    cam.begin();

    auto points = cobol.getStringAsPoints("cobol");

    ofPushMatrix();
    //ofTranslate( ofGetWidth() * 0.5, ofGetHeight() * 0.5 );
    ofDrawAxis( 200 );
    ofScale( 1, -1 );

    for ( auto&p: points ) {
        p.simplify( 0.5f );
        p.draw();
    }
    ofPopMatrix();

    cam.end();

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
