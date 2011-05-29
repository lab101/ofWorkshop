/*
 *  particle.h
 *  WorkshopFlyer
 *
 *  Created by Kris Meeusen on 17/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class particle{
	
public:
	//void draw();

	float width;
	ofRectangle rect;
	ofRectangle rect2;
	
	ofVec3f position;
	ofVec3f vector;
	ofVec3f	vectorDirecection;
	
	ofColor baseColorTone;
	
	void update()
	{
		position += vector;
		if (position.y > ofGetHeight()) {
			vector.rotate(0,0,-90); 
			position.y = ofGetHeight();
		}
		
		if (position.y < 0) {
			vector.rotate(0,0,-90); 
			position.y = -position.y;

		}
		
		if (position.x > ofGetWidth()) {
			vector.rotate(0,0,-90); 
			position.x = ofGetWidth();
		}
		
		if (position.x < 0) {
			vector.rotate(0,0,-90);
			position.x = -position.x;
		}
		
		rect.set(200, 200, 100,100);
		rect2.set(400, 300, 100,100);
		
		if(rect.inside(position) || rect2.inside(position)){
			vector.rotate(0,0,-90);
		}
		
	}
	
	
private:
	
	
};