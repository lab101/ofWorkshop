/*
 *  baseStrip.h
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 25/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "particle.h"


class BaseStrip{
	
public:
		
	virtual void draw();
	virtual void createMesh(ofColor innerBaseColor,ofColor outerBaseColor,ofPrimitiveMode primitive);
	virtual void update(float beatValue,float limit);
	virtual void addPoint(float x,float y,float directionX,float directionY);

	BaseStrip();
	
	
	vector<particle*> nodes;
	float upperX;
	float upperY;
	//char c;
	float beat;
	
private:
	int nrOfStrips;
	ofMesh mesh;
	ofMesh meshOutline;
		
};