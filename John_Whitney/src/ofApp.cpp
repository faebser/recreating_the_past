#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    const float radius = 200;

    ofEnableAntiAliasing();

    for (int i = 0; i < 32 ; i++ ) {
        const auto x = getx( 512, radius, i * step); //sin( i * step ) * 512 + 512;
        const auto y = gety( 334, radius, i * step );
        auto v = ofVec2f( x,  y );
        points[ i ] = v;
        points2[ i ] = v;
    }
}

//--------------------------------------------------------------
void ofApp::update() {

    // add ofpolyline

    auto org = ofVec2f(
                getx( 512, 400, ofGetElapsedTimef() * 1.618 ),
                gety( 334, 200, ofGetElapsedTimef() * 2.349 ));
    // auto org = ofVec2f( 512, 334 );
    const auto org2 =  ofVec2f(
                getx( 512, 400, ofGetElapsedTimef() * 0.2 ),
                gety( 334, 200, ofGetElapsedTimef() * 2 ));
    const float radius = 200;

    for (int i = 0; i < 32 ; i++ ) {
        auto& p = points[ i ];
        p.x = getx( org.x, radius, ofGetElapsedTimef() + i * step ); //sin( i * step ) * 512 + 512;
        p.y = gety( org.y, radius, ofGetElapsedTimef() + i * step );

        auto& p2 = points2[ i ];
        p2.x = getx( org2.x, radius * 0.5, ofGetElapsedTimef() * -1 + i * step );
        p2.y = gety( org2.y, radius * 0.5, ofGetElapsedTimef() * -1 + i * step );
    }

    //for( auto& p: points ) {
        //p.x = getx( org.x, radius, ofGetElapsedTimef() + do_step ); //sin( i * step ) * 512 + 512;
        //p.y = gety( org.y, radius, ofGetElapsedTimef() + do_step );
        //p.x = sin( ofGetElapsedTimef() + do_step ) * 512 + 512;
        //do_step += step;
    //}
}

float ofApp::getx ( float origin, float radius, float angle ) {
    return origin + radius * cos( angle );
}

float ofApp::gety ( float origin, float radius, float angle ) {
    return origin + radius * sin( angle );
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (int i = 0; i < 32 ; i++ ) {
        ofDrawLine( points[ i ], points2[ i ]);
    }

    for( const auto& p: points ) {
        //ofDrawCircle( p.x, p.y, 5 );
    }

    for( const auto& p: points2 ) {
        //ofDrawCircle( p.x, p.y, 5 );
    }
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
