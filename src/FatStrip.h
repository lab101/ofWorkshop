/*
 *  FatStrip.h
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 25/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#pragma once

#include "BaseStrip.h"

class FatStrip : public BaseStrip
{
	public:
	void draw();
	void update(float beatValue,float limit);
	void addPoint(float x,float y,float directionX,float directionY);
	void createMesh(ofColor innerBaseColor,ofColor outerBaseColor);

	
private:
	ofMesh innerFrame;
	ofMesh outline;

};
