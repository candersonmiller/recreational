/*
 *  point.h
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 5/14/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _point
#define _point

class point{
	
	public:
		point();
		point(int _x, int _y);
		void setX(int _x);
		void setY(int _y);
	
		int getX();
		int getY();
		
		void render();
		void renderNormal();
		void renderDebug();
		void toggleDebug();
		bool inRadius(int _x, int _y);

	private: 	
	
		int x;
		int y;
		bool debug;	
	
};

#endif