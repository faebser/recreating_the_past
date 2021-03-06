#include "ofApp.h"
#include "tree.h"


//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(800, 800, GL_RGBA, 4);
    // top, left, w, h
    size = glm::vec4( ofGetWidth() * 0.04, ofGetHeight() * 0.04, ofGetWidth() * 0.93, ofGetHeight() * 0.93 );

    top = ofRectangle( 0, 0, ofGetWidth() * 0.93, size.w - 60 );

    // borders
//    top.y += 30;
//    top.height -= 60;

    fboBorder.allocate( size.z, 30, GL_RGBA, 4 );

    ofSetLineWidth(4);

    fboBorder.begin();
        ofClear(0,0,0,255);
        ofBackground( 242, 203, 139, 100);
        ofSetColor( 193, 156, 89 );
        for (int i = -30; i < size.z; i += 8 ) {
            ofDrawLine( 0 + i, 0, i + 30, 30 );
        }
    fboBorder.end();

    // generate some rects
    // first top
    // the children of top all need to be inside of top
    // int max = ofRandom( 3, 6 );
    float space = top.height;

    auto h = ceil( ofRandom(30, space) ); // TODO this one is too big
    space -= h;

    auto r = ofRectangle( top.x, 0, top.width, h);
    rects.push_back( r );
    ofRectangle & last = r;

    // while is maybe better

    while ( space > 30 ) {
        h = ceil( ofRandom(30, space) );
        //cout << "i: " << i << endl;
        space -= h;
        cout << "space: " << space << endl;
        auto r = ofRectangle( top.x, last.y + last.height , last.width, h);
        rects.push_back( r );
        cout << "last.y: " << last.y << endl;
        last = r;
    }

    cout << "space at end: " << space << endl;

    if ( space > 0 && space <= 100 ) {
        rects.back().setHeight( last.height + space );
    }
    else {
        auto r = ofRectangle( top.x, last.y + last.height , last.width, space);
        rects.push_back( r );
    }

    // TODO write a recursive function
    // that adds sub rects to the now created rects

    bool dir = true;

    for (auto r : rects ) {
        auto f = ofFbo();
        f.allocate(r.width, r.height, GL_RGBA , 4);
        fbos.push_back( f );

        drawLines( r, f, dir );
        dir = !dir;
    }

    r = rects.at( 0 );

    auto temp = ofRectangle(ofRandom(r.x, r.width), ofRandom(r.y, r.height), 100, 100);
    auto f = fbos.at( 0 );

    auto tempf = ofFbo();
    tempf.allocate( temp.height, temp.width );

    drawLines(temp, tempf, false );

    f.begin();
        ofClearAlpha();
        ofFill();
        ofSetColor(0,0,0,0);
        ofDisableAlphaBlending();
        ofDrawRectangle(temp);
        ofEnableAlphaBlending();

        ofSetColor(255, 192, 164);
        tempf.draw( temp.x, temp.y );

    f.end();

//    top_it = rectTree.begin();
//    auto n = Node{ top, ofFbo() };
//    nodes.push_back( n );
//    rectTree.insert(top_it, &n);

    // if remaining height is smaller than 100 we just add it to the last rect
    // otherwise we add another rect

//    cout << size.x << endl;
//    cout << size.y << endl;
//    cout << size.z << endl;
//    cout << size.w << endl;
}

void ofApp::drawLines(ofRectangle rect, ofFbo fbo, bool direction) {

    fbo.begin();
        ofClear(0,0,0,255);
        ofBackground( 208, 170, 111, 75 );
        if ( direction ) {
            for (int i = -rect.height; i < rect.width; i+=8) {
                ofSetColor(141, 25, 15);
//                if ( i % 2 == 0 ) {
//                    ofSetColor(141, 25, 14);
//                }
//                else {
//                    ofSetColor(255, 192, 164);
//                }
                ofDrawLine(0 + i,0, i + rect.height, rect.height );
            }
        }
        else {
           ofSetColor(141, 25, 15);
            for (int i = 0; i < rect.width + rect.height ; i+=8) {
                ofDrawLine(0 + i,0, i - rect.height, rect.height );
            }
        }


//        ofClearAlpha();
//        ofFill();
//        ofSetColor(0,0,0,0);
//        ofDisableAlphaBlending();
//        //ofDrawRectangle(0,0,100,100);
//        ofEnableAlphaBlending();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //    ofNoFill();
    //    ofDrawRectangle(200,200,600,400);
    //
    //    glEnable(GL_SCISSOR_TEST);
    //    glScissor( 200,ofGetHeight()-200-400,600,400);
    //
    //
    //    for (int i = -400; i < 600; i+=20){
    //        ofDrawLine(200 + i,200,200+i + 400, 600 );
    //    }
    //
    //    glDisable(GL_SCISSOR_TEST);
    ofBackground(255);
    fbo.begin();
        ofClear(0,0,0,255);
        ofSetColor(255,0,0);
        for (int i = -800; i < 800; i+=4) {
            if ( i % 2 == 0 ) {
                ofSetColor(141, 25, 14);
            }
            else {
                ofSetColor(255, 192, 164);
            }
            ofDrawLine(0 + i,0, i + 800, 800 );
        }
        ofClearAlpha();
        ofFill();
        ofSetColor(0,0,0,0);
        ofDisableAlphaBlending();
        ofDrawRectangle(0,0,100,100);
        ofEnableAlphaBlending();

    fbo.end();
    ofSetColor(255);
    // fbo.draw(0, 0);


    ofSetColor(255, 192, 164);
    //ofDrawRectangle( top );


    int bla = 0;

    ofPushMatrix();
    ofTranslate( size.x, size.y );

    fboBorder.draw( 0, 0 );
    fboBorder.draw( 0, size.w - 30 );

    ofSetColor(255, 192, 164);

    ofTranslate(0, 30);

    for (int i = 0; i < rects.size(); i++ ) {
        auto f = fbos.at( i );
        auto r = rects.at( i );

        f.draw( r.x, r.y );
    }

    for(auto r : rects) {
        //ofDrawRectangle(r);
        //ofNoFill();
        ofSetColor(0);
        //ofDrawRectangle(r);
        bla += 50;
        ofSetColor(20+bla, bla, 0);
    }
    ofPopMatrix();

    if ( !screen_taken ) {
        take();
        screen_taken = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RETURN) {
        take();
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

void ofApp::take() {
    ofImage image;
    image.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    string str = "images/devImgs/devImg" + ofToString(ofGetTimestampString()) + ".jpg";
    image.saveImage(str);
    std::cout << "screenshot taken" << endl;
}
