#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	counter = 0;
	//ofSetCircleResolution(50);
	ofBackground(100,100,100);
	bSmooth = false;
	ofSetWindowTitle("Control Points Example By C. Anderson Miller");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	//testPoint = point(200,200);
	//testLine = line();
	
	
	
	
	float x1,y1;
	float radius = 200;
	
	x1 = (float)radius * cos(99 * PI/5.0f);
	y1 = (float)radius * sin(99 * PI/5.0f);
	for(int j = 0; j < 10; j++)
	{
		points.push_back(point(500 + x1,450 + y1));
		x1 = (float)radius * cos(j * PI/5.0f);
		y1 = (float)radius * sin(j * PI/5.0f);
		points.push_back(point(500+x1,450+y1));
	}
	
	
	
	
	
	
	int pointSize = points.size();
	
	for(int i = 0; i < pointSize; i++){
		for(int j = 0; j < pointSize; j++){
			lines.push_back(line( points[i], points[j] ) );
		}
	}
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	counter = counter + 0.033f;
}

//--------------------------------------------------------------
void testApp::draw(){

	/*
	//--------------------------- circles
	//let's draw a circle:
	ofSetColor(255,130,0);
	float radius = 50 + 10 * sin(counter);
	ofFill();		// draw "filled shapes"
	ofCircle(100,400,radius);

	// now just an outline
	ofNoFill();
	ofSetColor(0xCCCCCC);
	ofCircle(100,400,80);

	// use the bitMap type
	// note, this can be slow on some graphics cards
	// because it is using glDrawPixels which varies in
	// speed from system to system.  try using ofTrueTypeFont
	// if this bitMap type slows you down.
	ofSetColor(0x000000);
	ofDrawBitmapString("circle", 75,500);


	//--------------------------- rectangles
	ofFill();
	for (int i = 0; i < 200; i++){
		ofSetColor((int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
		ofRect(ofRandom(250,350),ofRandom(350,450),ofRandom(10,20),ofRandom(10,20));
	}
	ofSetColor(0x000000);
	ofDrawBitmapString("rectangles", 275,500);

	//---------------------------  transparency
	ofSetColor(0x00FF33);
	ofRect(400,350,100,100);
	// alpha is usually turned off - for speed puposes.  let's turn it on!
	ofEnableAlphaBlending();
	ofSetColor(255,0,0,127);   // red, 50% transparent
	ofRect(450,430,100,33);
	ofSetColor(255,0,0,(int)(counter * 10.0f) % 255);   // red, variable transparent
	ofRect(450,370,100,33);
	ofDisableAlphaBlending();

	ofSetColor(0x000000);
	ofDrawBitmapString("transparency", 410,500);

	//---------------------------  lines
	// a bunch of red lines, make them smooth if the flag is set

	if (bSmooth){
		ofEnableSmoothing();
	}

	ofSetColor(0xFF0000);
	for (int i = 0; i < 20; i++){
		ofLine(600,300 + (i*5),800, 250 + (i*10));
	}

	if (bSmooth){
		ofDisableSmoothing();
	}

	ofSetColor(0x000000);
	ofDrawBitmapString("lines\npress 's' to toggle smoothness", 600,500);
	 */
	
	for(int i = 0; i < lines.size(); i++){
		lines[i].render();
	}
	for(int i = 0; i < points.size(); i++){
		points[i].render();
	}
	
	
	
	//testPoint.render();
	//testLine.render();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == 's'){
		bSmooth = !bSmooth;
	}
	
	if (key == 'd'){
		testPoint.toggleDebug();
		testLine.toggleDebug();
		for(int i = 0; i < lines.size(); i++){
			lines[i].toggleDebug();
		}
		
		for(int i = 0; i < points.size(); i++){
			points[i].toggleDebug();
		}
	}
	
	if (key == 'n'){
		lines.push_back(line());
		if(testLine.debug){
			lines[lines.size() - 1].toggleDebug();
		}
	}
	
	if(key=='f'){
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if( testPoint.inRadius(x,y) ){
		testPoint.setX(x);
		testPoint.setY(y);
	}
	
	for(int i = 0; i < lines.size(); i++){
		//lines[i].render();
		if(lines[i].inRadius(x,y) ){
			lines[i].setPoint(x,y);
		}
	}
	
	if( testLine.inRadius(x,y) ){
		testLine.setPoint(x,y);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}