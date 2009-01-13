#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	// listen on the given port
	std::cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	strcpy( mouseButtonState, "" );
	glEnable(GL_DEPTH_TEST);
	
	
	font.loadFont("/Library/Fonts/Arial.ttf",72);
	ofBackground( 150, 150, 150 );
	rotationVal = 0;
	for(int i = 0; i < 15; i++){
		fftval[i] = 0;
	}
	
	hesbad = false;
	hesbad2 = false;
	timemark = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void testApp::update(){
	// hide old messages
	for ( int i=0; i<NUM_MSG_STRINGS; i++ )
	{
		if ( timers[i] < ofGetElapsedTimef() )
			msg_strings[i] = "";
	}
	
	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		// check for bounce
		if ( strcmp( m.getAddress(), "/bounce" ) == 0 )
		{
			// both the arguments are int32's
			bounceval = m.getArgAsFloat(0);
			mouseX = ceil(bounceval);
			
		}
		// check for mouse button message
		else if ( strcmp( m.getAddress(), "/fft" ) == 0 ) 
		{
			// the single argument is a string
			for(int i = 0; i < 15; i++){
				fftval[i] = m.getArgAsFloat(i);
			}
		}
		else
		{
			// unrecognized message: display on the bottom of the screen
			char msg_string[16384];
			strcpy( msg_string, m.getAddress() );
			strcat( msg_string, ": " );
			for ( int i=0; i<m.getNumArgs(); i++ )
			{
				// get the argument type
				strcat( msg_string, m.getArgTypeName( i ) );
				strcat( msg_string, ":" );
				// display the argument - make sure we get the right type
				if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
					sprintf( msg_string, "%s%d ", msg_string, m.getArgAsInt32( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
					sprintf( msg_string, "%s%f ", msg_string, m.getArgAsFloat( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
					sprintf( msg_string, "%s\"%s\" ", msg_string, m.getArgAsString( i ) );
				else 
					strcat( msg_string, "unknown" );
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}
		
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	
	char buf[256];
	//sprintf( buf, "listening for osc messages on port %d", PORT );
	//ofDrawBitmapString( buf, 10, 20 );
	
	// draw music values
	if(false){
		ofSetColor(255, 255, 255);
		sprintf( buf, "bounce value: % 8f", bounceval );
		ofDrawBitmapString( buf, 430, 20 );
		sprintf(buf, "fft value at: % 8f", fftval[8]);
		ofDrawBitmapString(buf, 430, 50);
		ofDrawBitmapString( mouseButtonState, 580, 20 );
	}

	for ( int i=0; i<NUM_MSG_STRINGS; i++ )
	{
		ofDrawBitmapString( (char*)msg_strings[i].c_str(), 10, 40+15*i );
	}
	
	bool boom = false;
	if(bounceval > 5000){
		boom = true;
	}


	
	glPushMatrix();
	ofSetColor(255, 255, 0);

	
	
	ofSetColor(255, 255, 255);
	int startX = 320;
	int startY = 240;
	if(rotationVal < 360){
		rotationVal += 0.1;
	}else{
		rotationVal =0;
	}
	
	glTranslated(320, 240, -200);
	glRotated((360 * fftval[4]) * 1.5, 0, 0, 1);
	glPushMatrix();
		float distance = 0;
		for(int i = 0; i < 15; i++){
			if(i != 11){
				distance += fftval[i];
		}
		}
	
	glPushMatrix();
	glTranslated(100 + 200 *  2* distance, 0, 0);
	
	
	glutSolidSphere(100 - (50 * fftval[5]), 60, 60);
	glPopMatrix();
	glTranslated(-100 + -200 * distance, 0, 0);

	
	glutSolidSphere(100 - (50 * fftval[3]), 60, 60);
	glPopMatrix();
					 int blue = 50;
					 startX = 100; 
					 int y = 480;
					 float totalfft = 0;
					 for(int i = 0; i < 15; i++){
					 if(i != 11){
					 blue += 30;
					 ofSetColor(0, 0, blue);
					 ofRect(startX, y, 20, - 1 * 1000 * fftval[i]);
					 startX += 30;
					 totalfft += fftval[i];
					 
					 }
					 }
	
	bool overallvolume = false;
	if(overallvolume){
		ofSetColor(255,0,255);
		ofRect(0,0, totalfft * 600, 30);
	}
	
	int bg = ceil(20 + totalfft * 20);
	ofBackground(bg,bg , bg);
	//ofSetColor(255, 0, 0);
	//ofRect(0, 50, 1000, 1);
	
	bool ceelo = false;
	if(ceelo){
	if(fftval[0] > 0.34){
	//printf("%f\n", fftval[0]);
		//sprintf( buf, "He's Bad");
		//ofDrawBitmapString( buf, 300, 200 );
		hesbad = true;
		timemark = ofGetElapsedTimeMillis();
	}
	
	if(hesbad){
		int timebad = 300;
		if(ofGetElapsedTimeMillis() - timemark < timebad){
			ofSetColor(255, 0, 0);
			font.drawString("He's Bad", 150, 200);
		}else{
			hesbad = false;
			timemark = ofGetElapsedTimeMillis();
		}
	}
	}
	

	

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
