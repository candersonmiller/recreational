/*
 *  line.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 5/14/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "line.h"
#include "ofMain.h"

line::line(){
	debug = false;
	start = point(100,100);
	end = point(300,100);
}

line::line(point _start, point _end){
	debug = false;
	start = _start;
	end = _end;
}

void line::render(){
	if(debug){
		renderDebug();
	}else{
		renderNormal();
	}
	
}

point line::getStart(){
	return start;
}

point line::getEnd(){
	return end;
}

void line::renderNormal(){
	start.render();
	end.render();

	glPushMatrix();
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_LINES);
		glVertex2f(start.getX(), start.getY());
		glVertex2f(end.getX(), end.getY());
	glEnd();
	
	glPopMatrix();
}

void line::renderDebug(){
	start.render();
	end.render();

	glPushMatrix();
	
	glBegin(GL_LINES);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
		glVertex2f(start.getX(), start.getY());
		glVertex2f(end.getX(), end.getY());
	glEnd();
	
	glPopMatrix();
	
}

void line::toggleDebug(){
	if(debug){
		debug = false;
		start.toggleDebug();
		end.toggleDebug();
	}else{
		debug = true;
		start.toggleDebug();
		end.toggleDebug();
	}
}

bool line::inRadius(int _x, int _y){
	if(start.inRadius(_x, _y) ){
		return true;
	}
	
	if(end.inRadius(_x, _y) ){
		return true;
	}
	
	return false;
	
}
void line::setPoint(int _x, int _y){
	if(start.inRadius(_x, _y) ){
		start.setX(_x);
		start.setY(_y);
	}
	
	if(end.inRadius(_x, _y) ){
		end.setX(_x);
		end.setY(_y);
	}

}
