#include "testApp.h"


float lastSwitch;


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(20, 20, 10, 255);
	ofSetFrameRate(30);
	ofSetVerticalSync(false);
	
	bg.loadImage("bg.png");
	
	lastSwitch = ofGetElapsedTimef();
	bSnapshot = false;
	interactive =false;
	
	song1.loadSound("plump.mp3", true);
	song1.play();

	stripbeat=0;
	volumeLoop = 0;
	snapCounter =0;
	
	fontSmall = new ofTrueTypeFont();
	fontBig = new ofTrueTypeFont();
	fontMedium = new ofTrueTypeFont();
	
	fontSmall->loadFont("Futura.ttc", 60, true, true, true);
	fontMedium->loadFont("Futura.ttc", 40, true, true, true);
	fontBig->loadFont("Futura-CondensedExtraBold.ttf", 170, true, true, true);
	
	////	
	AddSentence<FatStrip>("OF", 100, 278,fontBig);
	AddSentence<FatStrip>("Playground", 120, 350,fontSmall);
	AddSentence<FatStrip>("&Workshop", 200, 450,fontSmall);	
	
	AddSentence<SmallStrip>("13/14/15 juli", 200, 550,fontMedium);	
	AddSentence<SmallStrip>("Antwerpen", 200, 600,fontMedium);	
	AddSentence<SmallStrip>("10 players", 200, 650,fontMedium);	
	///
	
	//capture.setup(ofGetWidth(), ofGetHeight(), "test.mov");
	//capture.addAudioTrack("/Users/kris/Documents/Xcode/openFrameworks-exp/apps/Lab101/WorkshopFlyer/bin/data/cube2.mp3");

	ofSetBackgroundAuto(true);
	ofNoFill();
	ofSetLineWidth(1);
	ofEnableAlphaBlending();
	lastRecordedFrame = 0;
	
	
}

template <class stripType>
void testApp::AddSentence(string text,float xStart,float yStart,ofTrueTypeFont* font)
{	
	//boundingBox =  font1.getStringBoundingBox(text, xStart, yStart);	
	
	for (int cIndex=0; cIndex < text.size() ; cIndex++) {
		
		char c = text[cIndex];
		
		if (c == ' ') {
			xStart +=30;
			continue;
		}
		
		stripType* stripObjectBlue = new stripType();
		
		testChar = font->getCharacterAsPoints(c);
		
		string shitConversion = "";
		shitConversion += c;
		ofRectangle charBoundingBox =  font->getStringBoundingBox(shitConversion, xStart, yStart);	
		
		for(int k = 0; k <(int)testChar.getOutline().size(); k++){
			if( k!= 0)ofNextContour(true) ;
			for(int i = 0; i < (int)testChar.getOutline()[k].size(); i++){
				stripObjectBlue->upperX = xStart;
				stripObjectBlue->upperY = yStart;
								
				float x = xStart + testChar.getOutline()[k].getVertices()[i].x;
				float y = yStart + testChar.getOutline()[k].getVertices()[i].y;
				
				float directionX = -(charBoundingBox.getCenter().x - x) / charBoundingBox.width;
				float directionY = -(charBoundingBox.getCenter().y - y) / charBoundingBox.height;
				
				//cout << boundingBox.getCenter().x << " " << boundingBox.getCenter().y << " "  << directionX << " " << directionY << "\n";				
				
				stripObjectBlue->addPoint(x , y ,directionX, directionY);
			}
		}
		
		xStart += charBoundingBox.width + 2;
		
		stripObjectBlue->createMesh(ofColor(3.4, 3.3, 1.3, 0.2),ofColor(255, 25, 255, 0.3));		
		strips.push_back(stripObjectBlue);		
	}
		
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofSoundUpdate();
	float * val = ofSoundGetSpectrum(2);	
	//cout << val[0] << "\n";
	
	for (int i=0; i < strips.size(); i++) 
	{
		BaseStrip* strip = strips.at(i);
		if (stripbeat == i) {
			strip->update(val[0],200);
			
		}else {
			//cout << (ofGetElapsedTimef() - lastRecordedFrame) << "\n";
			strip->update(val[0] / ((ofGetElapsedTimef() - lastRecordedFrame) * 70),200);	
		}
		
		
	}

	volumeLoop += val[0] * 0.4;
	
	// Select next active strip
	if (ofGetElapsedTimeMillis() - lastSwitch > 130 || val[0] > 0.1) {
		if(++stripbeat >= strips.size())
		{
			stripbeat = 0;
		}
		lastSwitch = ofGetElapsedTimeMillis();
	}	
		//screenGrabber.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		//capture.addFrame(screenGrabber.getPixels(), ofGetElapsedTimef()-lastRecordedFrame/30.0);
		
	
	lastRecordedFrame = ofGetElapsedTimef();
	
	//if (!song1.getIsPlaying()) {
	//	capture.finishMovie();
	//}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	
	//glLoadIdentity();
	//glTranslated(0, 0, -500);
	ofFill();
	ofSetBackgroundAuto(false);
	ofSetColor(0,0, 0,90);
	ofRect(0,0,ofGetWidth(),ofGetHeight());
	ofNoFill();
	ofSetColor(255, 255, 255,255);

	//bg.draw(0, 0);
	// uncomment to see the frame - currently framerate limited to 60fps
	
//	char fpsStr[255]; // an array of chars	
	//	sprintf(fpsStr, "frame rate: %f ", ofGetFrameRate());
	//sprintf(fpsStr, "rotate y %f - x %f ", (ofGetWidth() /2.0 - mouseX) /4.0,(ofGetHeight() /2.0 - mouseY) /4.0);
	
	
	//ofDrawBitmapString(fpsStr, 10,10);
	
	
	ofPushMatrix();
	
	ofTranslate(ofGetWidth()/2, 0, 0);
	ofTranslate(0, ofGetHeight()/2, 0);

	if (interactive) {
		ofRotateY((ofGetWidth() /2 - mouseX) /4); 
		ofRotateX((ofGetHeight() /2 - mouseY) /4); 		
	}else {
		ofRotateY(6.2 + sin(volumeLoop) * 2);
		ofRotateX(40.5+ cos(volumeLoop) * 5);
//		ofTranslate(0, 0, 0);
	}


	ofTranslate(-ofGetWidth()/2, 0, 0);	
	ofTranslate(0, -ofGetHeight()/2, 0);

	ofRotateY(10+ sin(volumeLoop) * 10);
	//ofScale(1.2 * volumeLoop, 1.2 * volumeLoop,1);
	
	
	for (int i=0; i < strips.size(); i++) 
	{

		strips.at(i)->draw();
	}
	
	ofSetColor(255, 255, 255,255);


	ofPopMatrix();
	
	// create screenshot
	if (bSnapshot == true){
		screenGrabber.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		char fileName[255];
		sprintf(fileName, "snapshot_%i.png", snapCounter++);
		screenGrabber.saveImage(fileName);
		//capture.addFrame(screenGrabber.getPixels(), 1);
		bSnapshot = false;
	}
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}else if(key == 'p') {
		// create a screenshot
		bSnapshot = true;
	}else if (key == ' ') {
		//createNewStrips();
	}else if(key== ','){
		song1.setPosition(song1.getPosition() - 0.1);		
	}
	else if(key=='i'){
		interactive = !interactive;
	}
	else if(key== '.'){
		song1.setPosition(song1.getPosition() + 0.1);
		cout << song1.getPosition() + 0.1 << "\n";		
	}else if(key == 'q'){
		capture.finishMovie();
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int windowResized, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}