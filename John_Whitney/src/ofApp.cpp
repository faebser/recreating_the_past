#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    // todo
    // add ofxgui
    const float radius = 200;

    ofEnableAntiAliasing();

    ofSetBackgroundAuto(false);
    ofBackground(0);

    general.setup("General");
    general.add( blend.set( "blend", 100, 0, 255 ));

    circleA.setup("Circle A");
    circleA.add( radiusA.set( "radius", 200, 50, 500 ));
    circleA.add( scaleXA.set( "scale X", 0.5, -1, 1 ));
    circleA.add( scaleYA.set( "scale Y", 0.2, -1, 1 ));

    circleB.setup("Circle B");
    circleB.add( radiusB.set( "radius", 100, 25, 500 ));
    circleB.add( scaleXB.set( "scale X", 0.5, -1, 1 ));
    circleB.add( scaleYB.set( "scale Y", 0.2, -1, 1 ));

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

    // add ofpolyline in ofxgui

    const float half_width = ofGetWidth() * 0.5;
    const float half_height = ofGetHeight() * 0.5;

    const auto org = ofVec2f(
                getx( half_width, half_width - radiusA, ofGetElapsedTimef() * scaleXA ),
                gety( half_height, half_height - radiusA, ofGetElapsedTimef() * scaleYA ));
    // auto org = ofVec2f( 512, 334 );
    const auto org2 =  ofVec2f(
                getx( half_width, half_width - radiusB, ofGetElapsedTimef() * scaleXB ),
                gety( half_height, half_height - radiusB, ofGetElapsedTimef() * scaleYB ));

    for (int i = 0; i < 32 ; i++ ) {
        auto& p = points[ i ];
        p.x = getx( org.x, radiusA, ofGetElapsedTimef() + i * step );
        p.y = gety( org.y, radiusA, ofGetElapsedTimef() + i * step );

        auto& p2 = points2[ i ];
        p2.x = getx( org2.x, radiusB, ofGetElapsedTimef() * -1 + i * step );
        p2.y = gety( org2.y, radiusB, ofGetElapsedTimef() * -1 + i * step );
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
    ofEnableBlendMode( OF_BLENDMODE_MULTIPLY );
    ofSetColor( blend, blend, blend );
    ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
    ofEnableBlendMode( OF_BLENDMODE_ALPHA );

    ofSetColor( 255, 255, 255, 125 );

    for (int i = 0; i < 32 ; i++ ) {
        ofDrawLine( points[ i ], points2[ i ]);
    }

    for( const auto& p: points ) {
        //ofDrawCircle( p.x, p.y, 5 );
    }

    for( const auto& p: points2 ) {
        //ofDrawCircle( p.x, p.y, 5 );
    }

    general.draw();
    circleA.draw();
    circleB.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    cout << "key: " << key << endl;
    cout << "key: " << (key == 'l') << endl;

        if(key == 's'){
            general.saveToFile("settings.xml");
            circleA.saveToFile("circleA.xml");
            circleB.saveToFile("circleB.xml");
        }
        else if(key == 'l'){
            general.loadFromFile("settings.xml");
            circleA.loadFromFile("circleA.xml");
            circleB.loadFromFile("circleB.xml");
        }
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
