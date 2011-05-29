/*
 *  baseStrip.cpp
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 25/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#include "BaseStrip.h"

BaseStrip::BaseStrip()
{
	beat=0;
}

void BaseStrip::addPoint(float x,float y,float directionX,float directionY)
{
	particle* point  = new particle();
	point->position.x = x;//150 + (i * startAngleX);
	point->position.y = y;//150 + (i * startAngleY /100);
	
	point->vector.x = 0;// (ofRandom(1.5,10.9) *directionX);
	point->vector.y = 0;//(ofRandom(1.5,10.9) *directionY);
	point->vectorDirecection.x = directionX;
	point->vectorDirecection.y = directionY;
	point->width = ofRandom(1,60);
	
	nodes.push_back(point);
}

void BaseStrip::createMesh(ofColor innerBaseColor,ofColor outerBaseColor,ofPrimitiveMode primitive)
{
	mesh.setMode(primitive);	
	
	for (int i=0; i < nodes.size(); i++) {
		
		float rnd = ofRandom(0.2,1);
		float colorStepSize = (1.0 / (float) nrOfStrips);
		
		float rnd1 = ofRandom(0.1,0.2);
		
		particle* point = nodes.at(i);
		// added fixed vertexes
		mesh.addVertex(ofVec3f(point->position.x,point->position.y,100));
		mesh.addColor(ofColor(innerBaseColor.r *rnd,innerBaseColor.g*rnd,innerBaseColor.b * rnd,rnd * innerBaseColor.a ));			
		
		// added moving vertexes
		mesh.addVertex(ofVec3f(point->position.x + point->vector.x, point->position.y + point->vector.y,0));
		point->baseColorTone = ofColor(outerBaseColor.r*rnd1,outerBaseColor.r*rnd,outerBaseColor.r*rnd,rnd1 * outerBaseColor.a);
		mesh.addColor(point->baseColorTone);							
	}
}

void BaseStrip::update(float beatValue,float limit)
{
	int vertexIndex =0;
	// pow 9 / 800
	beat += (pow(beatValue *  50,7)-beat) / 200;
	beat-= 1;
	beat = ofClamp(beat, 2, limit);
	
	//cout << beat << " == " << beatValue << "\n";
	
	for (int i=0; i < nodes.size(); i+=1) {
		particle* point = nodes.at(i);
		mesh.setVertex(i*2, ofVec3f(point->position.x + point->vector.x + (beat * point->vectorDirecection.x),point->position.y + point->vector.y + (beat * point->vectorDirecection.y),beat));
		//ofColor newColor = point->baseColorTone;

		mesh.setVertex((i*2) +1, ofVec3f(point->position.x + point->vector.x + (beat * point->vectorDirecection.x),point->position.y + point->vector.y + (beat * point->vectorDirecection.y),-beat));

		
	//	ofColor newColor = point->baseColorTone;
//		newColor += ofColor(0,0,0);
	//	mesh.setColor(i*2, point->baseColorTone);
	}	
}

void BaseStrip::draw()
{
	ofFill();
		
//	ofSetColor(255, 255, 255,235);
//	cout << "base draw";
//	glPushMatrix();

//	float scale = ofClamp(beat/130, 1, 100);
//	ofScale(scale, scale, 1);
//	ofRotateZ(beat / 10);

	
	glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);  
	mesh.drawFaces();

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  
    glDisable(GL_BLEND);  
	ofEnableAlphaBlending();
//	glPopMatrix();
	ofNoFill();


}
