/*
 *  line.h
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 5/14/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "point.h"

#ifndef _line
#define _line

class line{
public:
	line();
	line(point _start, point _end);
	
	void render();

	void renderNormal();
	void renderDebug();

	void toggleDebug();
	
	point getStart();
	point getEnd();

	bool inRadius(int _x, int _y);
	void setPoint(int _x, int _y);


	bool debug;	
private: 	

	point start;
	point end;
	

};

#endif