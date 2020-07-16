#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    img.allocate(640, 480, OF_IMAGE_COLOR);
    font1.allocate(640, 480, OF_IMAGE_COLOR); // maybe the format is the problem?
    font2.allocate(640, 480, OF_IMAGE_COLOR);

    font1.begin();
        ofBackground( 255 );
        ofSetColor( 255, 0, 0 );
        ofDrawRectangle( font1.getWidth() * 0.5, font1.getHeight() * 0.5, 10, 10 );
    font1.end();
}

//--------------------------------------------------------------
void ofApp::update(){

    // I get the following errors
//    [ error ] ofGLUtils: ofGetGLTypeFromInternal(): unknown internal format 1, returning GL_UNSIGNED_BYTE
//    [ error ] ofGLUtils: ofGetGLFormatFromInternal(): unknown internal format 1, returning GL_RGBA
//    [ error ] ofGLUtils: ofGetGLTypeFromInternal(): unknown internal format 1, returning GL_UNSIGNED_BYTE
//    [ error ] ofGLUtils: ofGetGLFormatFromInternal(): unknown internal format 1, returning GL_RGBA
    // [ error ] ofPixels: image type not supported

    if ( dir ) {
        ofImage imgTemp;
        images.push_back(imgTemp);
        images.back().setUseTexture(false);
        ofPixels pixels;
        pixels.allocate(640, 480, OF_IMAGE_COLOR);
        font1.readToPixels( pixels );
        images.back().setFromPixels( pixels );

        if (images.size() > 80){
            images.erase(images.begin());
        }

        if (images.size() > 0){
            for (int y = 0; y < 480; y++){
                int whichImage = ofMap(y, 0, 480, 0, images.size());
                for (int x = 0; x < 640; x++){
                    ofColor color = images[whichImage].getColor(x,y);
                    img.setColor(x, y, color);
                }
            }
        }
        img.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

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
