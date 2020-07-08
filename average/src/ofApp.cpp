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

    mask.load("shadersGL3/mask");
    //shaderBlurY.load("shadersGL3/shaderBlurY");

    ofDirectory dir;
    dir.listDir( "purple" );

    for ( size_t i = 0; i < dir.size(); i++ ) {
        cout << dir.getPath( i ) << endl;

        imageWithData imgD;
        images.push_back( imgD );
        images.back().img.load( dir.getPath( i ) );

        ofRectangle targetDim = ofRectangle( 0, 0, 1000, 650 );
        ofRectangle imageDim;

        imageDim = ofRectangle( 0, 0, images.back().img.getWidth(), images.back().img.getHeight() );

        targetDim.scaleTo( imageDim );
        images.back().img.crop( targetDim.x, targetDim.y, targetDim.width, targetDim.height );
    }



    for ( auto& img: images ) {
        float r = 0, g = 0, b = 0;
        for ( int x = 0; x < img.img.getWidth(); x++ ) {
            for ( int y = 0; y < img.img.getHeight(); y++ ) {
                auto c = img.img.getColor( x, y );
                if ( c != ofColor::white && c != ofColor::black ) {
                    img.hue += c.getHue();
                    r += c.r;
                    g += c.g;
                    b += c.b;
                    if ( ofRandomf() > 0.7 ) {
                        // img.c = c;
                    }
                    //img.img.getColor( x, y ).getHsb( img.hue, img.s, img.b );
                }
            }
        }

        float is = img.img.getWidth() * img.img.getHeight();
        img.hue = img.hue / is;
        cout << r / is << " " << g / is << endl;
        img.c = ofColor( r / is, g / is, b / is );
        cout << (int) img.c.r << " " << (int) img.c.g << endl;
        cout <<  "// " << endl;
    }

    sort( images.begin(), images.end(),
        [] ( const imageWithData & a, const imageWithData & b ) -> bool {
        return a.hue < b.hue;
    });


//    average.allocate( 1000, 650, OF_IMAGE_COLOR );

//

//    for ( int i = 0; i < 1000; i++ ) {
//        for ( int j =0; j < 650; j++ ) {
//            float sumRed = 0, sumBlue = 0, sumGreen = 0;

//            for (auto& im: images) {
//                auto color = im.getColor( i,j );
//                sumRed   += color.r;
//                sumBlue  += color.b;
//                sumGreen += color.g;
//            }

//            average.setColor( i, j, ofColor( sumRed / is, sumBlue / is, sumGreen / is ) );
//        }
//    }

//    average.update();

    center = ofVec2f( 1024, 768 );

    float w = ofGetWidth();
    float h = ofGetHeight();
    m_density = images.size() * 0.5; //min<float>(w,h) * 0.01;
    m_samples = ofxPoissonDiskSampling::sample2D(w, h, m_density, false);

    printf("%d samples\n", m_samples.size());

    for ( auto v: m_samples ) {
        if ( draw_if_close_enough( center, v )) {
//            pointWithColor p;
//            points.push_back(p);
//            points.back().vec = v;
            particles.push_back( particle() );
            particles.back().setInitialCondition( v.x, v.y, 0, 0 );
        }
    }

    float step = ceil( height * 2 / images.size() );
    float top = center.y - height;

    for ( auto& img : images ) {
        for ( auto& p : particles ) {
            if ( p.pos.y > top && top + step > p.pos.y ) {
                p.c = ofColor( img.c.r, img.c.g, img.c.b );
//                cout << (int) img.c.r << " " << (int) img.c.g << endl;
//                cout << (int) p.c.r << " " << (int) p.c.g << endl;

                // img.c.getBrightness();
            }
        }
        top += step;
    }


    // this removes only points in the upper left corner
    // remove_if( m_samples.begin(), m_samples.end(), remove_if_far_enough );

//    // this randomly removes points inside of the circle
//    for( size_t i = 0; i < m_samples.size(); i++ ) {
//        if ( draw_if_close_enough( center, m_samples[ i ]) ) {
//            vector< ofVec2f >::iterator it = std::next( m_samples.begin(), i);
//            m_samples.erase( it );
//        }
//    }

    gradient.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA );
    background.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA );
    circles.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA );
    bg_gradient.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA );
    finalFbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA );

    mesh.setMode( OF_PRIMITIVE_TRIANGLE_STRIP );

    ofVec2f center = ofVec2f( ofGetWidth() * 0.5, 300 );

    for ( int k = 0; k < 100; k++ ) {
        for ( size_t i = 0; i < particles.size(); i++ ) {
            auto& p = particles[ i ];
            p.resetForce();
            //p.addRepulsionForce(mouseX, mouseY, 200, 1.4);

            float dist = p.pos.distance( center );

            for ( size_t j = 0; j < i; j++ ) {
                particles[i].addRepulsionForce( particles[ j ], 50, dist * 0.005 );
                particles[i].addAttractionForce(particles[ j ], 150, 2 / dist );
            }
        }

        for ( auto& p : particles ) {
            p.addDampingForce();
            p.update();
        }
    }

    float mult = 1000 / images.size();
    for (size_t i = 0; i < images.size(); i++ ) {
        mesh.addVertex( ofPoint( i * mult, 0 ) );
        mesh.addVertex( ofPoint( i * mult, 1000 ) );

        mesh.addColor( images[ i ].c );
        mesh.addColor( images[ i ].c );
    }

    gradient.begin();
        ofBackground( 0 );
        ofTranslate( gradient.getWidth() * 0.5, gradient.getHeight() * 0.5 );
        ofRotateDeg( 90 );
        ofTranslate( -gradient.getWidth() * 0.5, -gradient.getHeight() * 0.5 );
        ofTranslate( (gradient.getWidth() - 1000) * 0.5 , (gradient.getHeight() - 1000) * 0.5  );
        mesh.draw();
    gradient.end();

    background.begin();
        ofBackground( 0 );
        ofSetColor( 255 );
        ofDrawCircle( background.getWidth() * 0.5, background.getHeight() * 0.5, 500 );
//        ofSetColor( 255, 0, 0 );
//        ofTranslate( (gradient.getWidth() - 1000) * 0.5 , (gradient.getHeight() - 1000) * 0.5  );
//        ofDrawRectangle( 0, 0, 1000, 1000 );
    background.end();

    circles.begin();
        ofBackground(0);
        ofSetColor( 255 );
        for(auto& p : particles) {
            ofDrawCircle( p.pos.x, p.pos.y, 5 );
        }
    circles.end();

    bg_gradient.begin();
        mask.begin();

        mask.setUniformTexture( "colorTex", gradient, 1 );
        mask.setUniformTexture( "imageMask", background, 2 );

        background.draw( 0, 0 );

        mask.end();
    bg_gradient.end();

    finalFbo.begin();
        mask.begin();

        mask.setUniformTexture( "colorTex", bg_gradient, 1 );
        mask.setUniformTexture( "imageMask", circles, 2 );

        bg_gradient.draw( 0, 0 );

        mask.end();

    finalFbo.end();

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    circles.begin();
        ofBackground(0);
        ofSetColor( 255 );
        for(auto& p : particles) {
            ofDrawCircle( p.pos.x, p.pos.y, 5 );
        }
    circles.end();

    finalFbo.begin();
        mask.begin();

        mask.setUniformTexture( "colorTex", bg_gradient, 1 );
        mask.setUniformTexture( "imageMask", circles, 2 );

        bg_gradient.draw( 0, 0 );

        mask.end();

    finalFbo.end();

        //ofSetColor(220,0,50);
        ofFill();

        // in the end I just resorted to this
        // as a temporary solution and
        // started working on the images
        // instead
        for(auto& p : particles) {
            // ofSetColor( p.c );
            // ofDrawCircle( p.pos.x, p.pos.y, 5 );
        }

//        ofSetColor(0,90,180);
        for(ofVec2f v : m_samples) {
           //ofDrawCircle(v.x,v.y, m_density * 0.5);
        }

        // ofSetColor(255, 0 , 0);
        // ofDrawCircle( 1024, 768, 500 );

        // ofSetColor( ofColor::white );
        // images[ ofGetFrameNum() % images.size() ].img.draw( 0,0 );

        //average.draw( 0, 0 );

        //f.draw( 0, 0 );



        ofSetColor( 255 );
        //ofDrawRectangle(0, 0, 500, 500);

        finalFbo.draw( 0, 0 );

        ofPushMatrix();
         ofScale( 0.25, 0.25 );
            ofSetColor( 255 );
            //mesh.draw();
            gradient.draw( 0, 0 );
            ofSetColor( 255 );
            background.draw( gradient.getWidth(), 0 );
            circles.draw( gradient.getWidth() + background.getWidth(), 0 );
            bg_gradient.draw( gradient.getWidth() + background.getWidth() + circles.getWidth(), 0 );

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
