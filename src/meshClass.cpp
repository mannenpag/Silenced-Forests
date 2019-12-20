//
//  meshClass.cpp
//  silent-ecosphere-v2
//
//  Created by Gustav Bodin on 11/8/19.
//  Based on the example in ofBook.
//
// From the examples in ofBook

#include "meshClass.hpp"

//--------------------------------------------------------------
void meshClass::setup() {
    image.load("images/test.png");
    image.resize(150, 150);
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();
    
    intensityThreshold  = 200.0;
    
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                
                float xConst = ofGetWidth()/150;
                float yConst = ofGetHeight()/150;

                ofVec3f pos(x*xConst, y*yConst, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            
            float distance = verta.distance(vertb);
            
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    meshCopy = mesh;
    magnification = true;
}

//--------------------------------------------------------------

//Add an input to the mesh class so that the class fades as the sound is fading.
void meshClass::update(float _x, float _y, float input, float endTime) {
    float timeInput = endTime - input;
    
    int numVerts = mesh.getNumVertices();
    if (magnification) {
        ofVec3f userInput(_x, ofGetHeight()-_y, 0);
        for (int i=0; i<mesh.getNumVertices(); ++i) {
            ofVec3f vertex = meshCopy.getVertex(i);
            
            float distanceToMouse = userInput.distance(vertex);
            float displacement = ofMap(distanceToMouse, 0, 300, 200.0, 0, true);
            
            ofVec3f direction = vertex - userInput;
            direction.normalize();

            float time = ofGetElapsedTimef();
            float timeScale = 3.0;
            float displacementScale = 0.15 * displacement;
            ofVec3f timeOffsets = offsets[i];
            
            ofVec3f displacedVertex = vertex + displacement * direction + (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
            mesh.setVertex(i, displacedVertex);
        }
    }
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);

        float time = ofGetElapsedTimef();
        float timeScale = 3.0;
        float displacementScale = 0.95;
        ofVec3f timeOffsets = offsets[i];

        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
}

//--------------------------------------------------------------
void meshClass::draw() {
    mesh.drawFaces();
}
