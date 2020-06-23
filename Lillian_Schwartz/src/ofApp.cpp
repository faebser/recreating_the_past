#include "ofApp.h"

void ofApp::dilate( ofImage & imgSrc, ofImage & imgDest){

    // assumptions!
    // img1 / img2 same w/h
    // both grayscale / binary images

    for (int i = 0; i < imgSrc.getWidth(); i++){
        for (int j = 0; j < imgSrc.getHeight(); j++){

            // neighbors
            // edges

            int i_m_1 = ofClamp(i-1, 0, imgSrc.getWidth()-1); // do mod(i, width) for wrap
            int i_p_1 = ofClamp(i+1, 0, imgSrc.getWidth()-1);
            int j_m_1 = ofClamp(j-1, 0, imgSrc.getHeight()-1);
            int j_p_1 = ofClamp(j+1, 0, imgSrc.getHeight()-1);

            // neighbor values

            ofColor n_ = imgSrc.getColor(i,j_p_1);
            ofColor ne = imgSrc.getColor(i_p_1,j_p_1);
            ofColor e_ = imgSrc.getColor(i_p_1,j);
            ofColor se = imgSrc.getColor(i_p_1,j_m_1);
            ofColor s_ = imgSrc.getColor(i,j_m_1);
            ofColor sw = imgSrc.getColor(i_m_1,j_m_1);
            ofColor w_ = imgSrc.getColor(i_m_1,j);
            ofColor nw = imgSrc.getColor(i_m_1,j_p_1);

            array< ofColor, 8 > c = {
                imgSrc.getColor(i,j_p_1),
                imgSrc.getColor(i_p_1,j_p_1),
                imgSrc.getColor(i_p_1,j),
                imgSrc.getColor(i_p_1,j_m_1),
                imgSrc.getColor(i,j_m_1),
                imgSrc.getColor(i_m_1,j_m_1),
                imgSrc.getColor(i_m_1,j),
                imgSrc.getColor(i_m_1,j_p_1)
            };

            int acc = 0;

            for(auto& co : c) {
                if ( co.getBrightness() > 240 ) {
                    acc++; // white
                }
                else {
                    acc--; // black
                }
            }

            // if the are black spots and white spots

            if (  n_.getBrightness() > 127 ||
                  ne.getBrightness() > 127 ||
                e_.getBrightness() > 127 ||
                se.getBrightness() > 127 ||
                s_.getBrightness() > 127 ||
                sw.getBrightness() > 127 ||
                w_.getBrightness() > 127 ||
                nw.getBrightness() > 127 ){
                //imgDest.setColor(i,j, ofColor(255));
            } else {
                //imgDest.setColor(i,j, ofColor(0));
            }

            if ( 0 < acc && acc < 8 ) {
                imgDest.setColor( i, j, ofColor( 0 ) );
            }
            else if ( acc > -8 && acc < 0) {
                imgDest.setColor( i, j, ofColor( 255 ) );
            }
        }
    }

    imgDest.update();
}

void ofApp::erosion(ofImage & imgSrc, ofImage & imgDest) {

    // assumptions!
    // img1 / img2 same w/h
    // both grayscale / binary images

    for (int i = 0; i < imgSrc.getWidth(); i++){
        for (int j = 0; j < imgSrc.getHeight(); j++){

            // neighbors
            // edges

            int i_m_1 = ofClamp(i-1, 0, imgSrc.getWidth()-1);
            int i_p_1 = ofClamp(i+1, 0, imgSrc.getWidth()-1);
            int j_m_1 = ofClamp(j-1, 0, imgSrc.getHeight()-1);
            int j_p_1 = ofClamp(j+1, 0, imgSrc.getHeight()-1);

            // neighbor values

            ofColor n_ = imgSrc.getColor(i,j_p_1);
            ofColor ne = imgSrc.getColor(i_p_1,j_p_1);
            ofColor e_ = imgSrc.getColor(i_p_1,j);
            ofColor se = imgSrc.getColor(i_p_1,j_m_1);
            ofColor s_ = imgSrc.getColor(i,j_m_1);
            ofColor sw = imgSrc.getColor(i_m_1,j_m_1);
            ofColor w_ = imgSrc.getColor(i_m_1,j);
            ofColor nw = imgSrc.getColor(i_m_1,j_p_1);

            if (  n_.getBrightness() > 127 ||
                  ne.getBrightness() > 127 ||
                e_.getBrightness() > 127 ||
                se.getBrightness() > 127 ||
                s_.getBrightness() > 127 ||
                sw.getBrightness() > 127 ||
                w_.getBrightness() > 127 ||
                nw.getBrightness() > 127 ){
                imgDest.setColor(i,j, ofColor(255));
            } else {
                imgDest.setColor(i,j, ofColor(0));
            }
        }
    }

    imgDest.update();
}

//--------------------------------------------------------------
void ofApp::setup(){

    thing.load("thing.png");
    thing.setImageType(OF_IMAGE_GRAYSCALE);

    thing1.allocate( thing.getWidth(), thing.getHeight(), OF_IMAGE_GRAYSCALE );
    thing2.allocate( thing.getWidth(), thing.getHeight(), OF_IMAGE_GRAYSCALE );

    // erosion( thing, thing1 );
    //dilate( thing, thing2 );
    //dilate( thing2, thing1 );

    ofSetFrameRate(1);

    dilate( thing, thing1 );

}

//--------------------------------------------------------------
void ofApp::update(){

    dilate( thing1, thing2 );
    dilate( thing2, thing1 );

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    ofScale(3, 3);
    thing.draw( 0, 0 );
    thing1.draw( thing.getWidth(), 0);
    thing2.draw( 0, thing.getHeight() );
    ofPopMatrix();

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
