//
//  ecosystemMesh.cpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/18/19.
//

#include "ecosystemMesh.hpp"

    const int N = 256;
    float spectrum[N];
    float Rad = 500;
    float Vel = 0.1;
    int bandRad = 2;
    int bandVel = 100;
    
    const int n = 1000;
    
    float tx[n], ty[n], tz[n];
    ofPoint p[n];
    
    float time0 = 0;

//--------------------------------------------------------------
void Mesh::setup(){
    for (int i=0; i<N; i++){
        spectrum[i] = 0.0f;
    }
    for ( int j=0; j<n; j++ ) {
        tx[j] = ofRandom( 0, 1500 );
        ty[j] = ofRandom( 0, 1500 );
        tz[j] = ofRandom( 0, 1000 );
    }
}

//--------------------------------------------------------------
void Mesh::update(){
    ofSoundUpdate();
    float *val = ofSoundGetSpectrum(N);
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.97; //Slow decreasing
        spectrum[i] = max( spectrum[i], val[i] );
    }
    
    float time = ofGetElapsedTimef();
    float dt = time - time0;
    dt = ofClamp(dt, 0.0, 0.1);
    time0 = time;
    
    Rad = ofMap( spectrum[ bandRad ], 1, 3, 1000, 1600, true );
    Vel = ofMap( spectrum[ bandVel ], 0, 0.1, 0.05, 0.5 );
    
    for (int j=0; j<n; j++) {
        tx[j] += Vel * dt;
        ty[j] += Vel * dt;
        tz[j] += Vel * dt;
        p[j].x = ofSignedNoise( tx[j] ) * Rad;
        p[j].y = ofSignedNoise( ty[j] ) * Rad;
        p[j].z = ofSignedNoise( tz[j] ) * Rad;
    }
}

//--------------------------------------------------------------
void Mesh::draw(float distInput, float endTime){
        float changeConst = (distInput/endTime) / 4;
    
//        cout << changeConst;
//        cout << "\n";
    ofPushMatrix();

        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, -150);
        ofFill();
        ofSetColor(200, 220, 210, 255 * changeConst);

        for (int i = 0; i<n; i++){
            ofDrawCircle(p[i],1 + 6.5 * changeConst);
        }
    ofPopMatrix();
}
