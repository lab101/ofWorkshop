#pragma once

#include "ofMain.h"
//#include "strip.h"
#include "BaseStrip.h"
#include "FatStrip.h"
#include "SmallStrip.h"
#include "ofQtVideoSaver.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		template <class stripType>
		void AddSentence(string text,float xStart,float yStart,ofTrueTypeFont* font);

		
		vector<BaseStrip*> strips;
	
		int snapCounter;
		ofImage screenGrabber;
		bool bSnapshot;
		bool interactive;
		char snapString[255];
	
		ofTrueTypeFont*  fontSmall;
		ofTrueTypeFont*  fontMedium;
		ofTrueTypeFont*  fontBig;
	
		ofTTFCharacter testChar;
	
		ofSoundPlayer	song1;
			
		int stripbeat;
	//	float colorIndex;
		float volumeLoop;
		float lastRecordedFrame;
	
	ofImage bg;
	
	ofQtVideoSaver capture;

	

};
