/*
 *  FatStrip.cpp
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 25/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#include "FatStrip.h"

void FatStrip::draw()
{
	//cout<< "DRAW SUPER!";
	//ofNoFill();
	innerFrame.drawFaces();

	ofSetLineWidth(2);
	outline.drawFaces();
	ofSetLineWidth(1);

	if(beat > 3){
		BaseStrip::draw();	
		//cout << beat << "\n";
	}
}

void FatStrip::update(float beatValue,float limit)
{
	BaseStrip::update( beatValue/2, limit);
}


void FatStrip::addPoint(float x,float y,float directionX,float directionY)
{
	BaseStrip::addPoint( x, y, directionX, directionY);	
}


void FatStrip::createMesh(ofColor innerBaseColor,ofColor outerBaseColor)
{
		BaseStrip::createMesh(innerBaseColor,outerBaseColor,OF_TRIANGLE_STRIP_MODE);	
	
		innerFrame.setMode(OF_TRIANGLE_FAN_MODE);	
		outline.setMode(OF_LINE_LOOP_MODE);
		
		for (int i=0; i < nodes.size(); i++) {
			
			particle* point = nodes.at(i);

			// added fixed vertexes
			innerFrame.addVertex(ofVec3f(point->position.x,point->position.y));
			innerFrame.addColor(ofColor(0.2,0.2,0.2,.2 /i));			
			
			outline.addVertex(ofVec3f(point->position.x,point->position.y));
			outline.addColor(ofColor(1,1,1,0.1));			
		}	
}
