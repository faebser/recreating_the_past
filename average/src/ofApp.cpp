#include "ofApp.h"

bool ofApp::draw_if_close_enough( ofVec2f center, ofVec2f k ) {
//    cout << "distance: " << ofDist( 1024, 768, k.x, k.y ) << endl;
//    cout << "bool: " << ( ofDist( 1024, 768, k.x, k.y ) > 500 ) << endl;
//    cout << "bool2: " << ( k.distance( center ) > 500 ) << endl;
    return ( k.distance( center ) < 500.0 );
}

bool remove_if_far_enough ( ofVec2f k ) {
    return ( ofDist( 1024, 768, k.x, k.y ) > 500.0f );
}

//--------------------------------------------------------------
void ofApp::setup() {

    ofDirectory dir;
    dir.listDir( "purple" );

    for ( size_t i = 0; i < dir.size(); i++ ) {
        cout << dir.getPath( i ) << endl;

        ofImage img;
        images.push_back( img );
        images.back().load( dir.getPath( i ) );

        ofRectangle targetDim = ofRectangle( 0, 0, 1000, 650 );
        ofRectangle imageDim;

        imageDim = ofRectangle( 0, 0, images.back().getWidth(), images.back().getHeight() );

        targetDim.scaleTo( imageDim );
        images.back().crop( targetDim.x, targetDim.y, targetDim.width, targetDim.height );


    }

    average.allocate( 1000, 650, OF_IMAGE_COLOR );

    float is = ( float ) images.size();

    for ( int i = 0; i < 1000; i++ ) {
        for ( int j =0; j < 650; j++ ) {
            float sumRed = 0, sumBlue = 0, sumGreen = 0;

            for (auto& im: images) {
                auto color = im.getColor( i,j );
                sumRed   += color.r;
                sumBlue  += color.b;
                sumGreen += color.g;
            }

            average.setColor( i, j, ofColor( sumRed / is, sumBlue / is, sumGreen / is ) );
        }
    }

    average.update();

    center = ofVec2f( 1024, 768 );

    float w = ofGetWidth();
    float h = ofGetHeight();
    m_density = min<float>(w,h) * 0.01;
    m_samples = ofxPoissonDiskSampling::sample2D(w, h, m_density, false);

    printf("%d samples\n", m_samples.size());

    // this removes only points in the upper left corner
    remove_if( m_samples.begin(), m_samples.end(), remove_if_far_enough );

    // this randomly removes points inside of the circle
    for( size_t i = 0; i < m_samples.size(); i++ ) {
        if ( draw_if_close_enough( center, m_samples[ i ]) ) {
            // vector< ofVec2f >::iterator it = std::next( m_samples.begin(), i);
            // m_samples.erase( it );
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
        ofSetColor(220,0,50);
        ofFill();

        // in the end I just resorted to this
        // as a temporary solution and
        // started working on the images
        // instead
        for(ofVec2f v : m_samples) {
            if ( draw_if_close_enough( center, v )) {
               ofDrawCircle(v.x,v.y, 5);
            }
        }

        ofSetColor(0,90,180);
        ofNoFill();
        for(ofVec2f v : m_samples) {
           ofDrawCircle(v.x,v.y, m_density * 0.5);
        }

        ofSetColor(255, 0 , 0);
        ofDrawCircle( 1024, 768, 500 );

        ofSetColor( ofColor::white );
//        images[ ofGetFrameNum() % images.size() ].draw( 0,0 );

        //average.draw( 0, 0 );
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
