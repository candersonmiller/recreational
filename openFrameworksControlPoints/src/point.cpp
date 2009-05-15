/*
 *  point.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 5/14/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"
#include "point.h"

point::point(){
	x = 0;
	y = 0;
	debug = false;
}


point::point(int _x, int _y){
	debug = false;
	x = _x;
	y = _y;
}

void point::setX(int _x){
	x = _x;
	
}
void point::setY(int _y){
	y = _y;
}

void point::render(){
	if(debug){
		renderDebug();
	}else{
		renderNormal();
	}
}

void point::renderNormal(){
	float x1,y1;
	float radius = 1;
	glPushMatrix();
	glTranslated(x,y,0);
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	
	x1 = (float)radius * cos(359 * PI/180.0f);
	y1 = (float)radius * sin(359 * PI/180.0f);
	for(int j = 0; j < 360; j++)
	{
		glVertex2f(x1,y1);
		x1 = (float)radius * cos(j * PI/180.0f);
		y1 = (float)radius * sin(j * PI/180.0f);
		glVertex2f(x1,y1);
	}
	glEnd();
	glPopMatrix();
}

void point::renderDebug(){
	float x1,y1;
	float radius = 20;
	glPushMatrix();
	glTranslated(x,y,0);
	glBegin(GL_LINES);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	
	x1 = (float)radius * cos(359 * PI/180.0f);
	y1 = (float)radius * sin(359 * PI/180.0f);
	for(int j = 0; j < 360; j++)
	{
		glVertex2f(x1,y1);
		x1 = (float)radius * cos(j * PI/180.0f);
		y1 = (float)radius * sin(j * PI/180.0f);
		glVertex2f(x1,y1);
	}
	glEnd();
	glPopMatrix();
}

void point::toggleDebug(){
	if(debug){
		debug = false;
	}else{
		debug = true;
	}
}


bool point::inRadius(int _x, int _y){
	int aSquared = pow(abs(_x - x),2);
	int bSquared = pow(abs(_y - y),2);
	float c = sqrt( aSquared + bSquared);
	
	if( c < 20 ){
		return true;
	}else{
		return false;
	}
}


int point::getX(){
	return x;
}

int point::getY(){
	return y;
}

