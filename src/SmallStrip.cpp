/*
 *  SmallStrip.cpp
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 26/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#include "SmallStrip.h"

void SmallStrip::draw()
{
	//cout<< "DRAW SUPER!";
	//ofNoFill();
	innerFrame.drawFaces();
	
	outline.drawFaces();
	if(beat > 3){
		BaseStrip::draw();	
		//cout << beat << "\n";
		
	}
}

void SmallStrip::update(float beatValue,float limit)
{
	BaseStrip::update( beatValue/2, limit);
}


void SmallStrip::addPoint(float x,float y,float directionX,float directionY)
{
	BaseStrip::addPoint( x, y, directionX, directionY);	
}


void SmallStrip::createMesh(ofColor innerBaseColor,ofColor outerBaseColor)
{
	BaseStrip::createMesh(innerBaseColor,outerBaseColor,OF_TRIANGLE_STRIP_MODE);	
	
	innerFrame.setMode(OF_TRIANGLE_FAN_MODE);	
	outline.setMode(OF_LINE_LOOP_MODE);
	
	for (int i=0; i < nodes.size(); i++) {
		particle* point = nodes.at(i);
		
		// added fixed vertexes
		innerFrame.addVertex(ofVec3f(point->position.x,point->position.y));
		innerFrame.addColor(ofColor(0.2,0.2,0.2,0.2));			
					
		outline.addVertex(ofVec3f(point->position.x,point->position.y));
//		outline.addColor(ofColor(0.4,0.4,0.4,1.2));		
		outline.addColor(ofColor(1,1,1,0.1));			

		
	}	
}