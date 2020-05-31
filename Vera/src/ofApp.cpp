#include "ofApp.h"


/* NOTES
 * Original is
 * Structure de Quadrilatères (Square Structures), 1987.
 * Computer drawing with white ink on salmon-coloured paper, 11 3/4 x 16 1/2 in.
 * see Vera-Molnar.jpg
 *
 * It is a grid of 6 x 9 composed of quads with random vertexes.
 * The first column contains 1 quad, the second 2, the third 4,
 * the fourth 8, the fifth 16, the sixth 32, the seventh 8,
 * the eighth 2, the ninth 1
 *
 * The salmon css color values are rgb(250, 128, 114) from http://html-color-names.com/salmon.php
 *
 * margins are approx. left 20%, right 20%, top 25%, bottom 25%
 *
 * */

//--------------------------------------------------------------
void ofApp::setup() {
    // heap allocated
    matrix = new ofMatrix3x3();
    margins = new ofVec2f( 300, 200 );

    // updateQuadSize( ofGetWidth(), ofGetHeight() );
    ofNoFill();
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update() {
    // matrix.setTranslation();
    // matrix.getTranslation();
    //updateMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( 240, 128, 114 );
    auto pos = ofVec2f();
    ofTranslate( margins->x, margins->y );
    ofSetColor( 255, 255, 255, 150 );

    ofSeedRandom(0);

    ofEnableAlphaBlending();

    for ( int quads = 0; quads < 54; quads++ ) {
        ofPushMatrix();
        ofTranslate( floor( pos.x ) * ( quadSize * marginScale ), pos.y * ( quadSize * marginScale) );

        int overlays = 0;

        if ( quads < 6 ) { overlays = 1; }
        else if ( quads < 12 ) { overlays = 2; }
        else if ( quads < 18 ) { overlays = 4; }
        else if ( quads < 24 ) { overlays = 8; }
        else if ( quads < 30 ) { overlays = 16; }
        else if ( quads < 36 ) { overlays = 32; }
        else if ( quads < 42 ) { overlays = 8; }
        else if ( quads < 48 ) { overlays = 2; }
        else { overlays = 1; }

        for (int i = 0; i < overlays ; i++ ) {
            auto random = getRandomPoints( range, quadSize );
            ofBeginShape();
                for(const auto& v : random ) {
                    ofVertex( v.x, v.y );
                }
                ofVertex( random[ 0 ].x, random[ 0 ].y );
            ofEndShape();
        }

        ofPopMatrix();

        pos.y = fmod(pos.y + 1, 6);
        pos.x = pos.x + 0.167f;

        cout << "i" << endl;
        cout << quads << endl;
        cout << "pos" << endl;
        cout << floor(pos.x) << endl;
        cout << pos.y << endl;
        cout << "////" << endl << endl;
    }

    ofDisableAlphaBlending();
}

array<ofVec2f, 4> ofApp::getRandomPoints( float range, float quadSize ) {
    std::array<ofVec2f, 4> result {
        ofVec2f( ofRandomf() * range, ofRandomf() * range ),
        ofVec2f( quadSize + ofRandomf() * range, ofRandomf() * range ),
        ofVec2f( quadSize + ofRandomf() * range, quadSize + ofRandomf() * range ),
        ofVec2f( ofRandomf(), quadSize + ofRandomf() * range ),
    };
    return result;
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
