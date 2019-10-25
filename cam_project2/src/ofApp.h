#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		bool bLearnBackground;
		ofVideoGrabber vidGrabber;
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImg, grayBg, grayDiff;
		ofxCvContourFinder contourFinder;
		int camWidth, camHeight, threshold;
		ofImage image;
		ofTrueTypeFont myFont, myFont2;
		//not sure if these last two are needed
		ofPixels vidPixels;
		ofTexture vidTexture;

		//make the text queue
		queue<ofTrueTypeFont> words_queue;
		/*make a queue for the notes playing*/
		queue<ofSoundPlayer> note_queue;
		/*piano*/
		ofSoundPlayer note1;
		ofSoundPlayer note2;
		ofSoundPlayer note3;
		ofSoundPlayer note4;
		ofSoundPlayer note5;
		ofSoundPlayer note6;
		ofSoundPlayer note7;
		ofSoundPlayer note8;
		ofSoundPlayer note9;
		ofSoundPlayer note10;
		ofSoundPlayer note11;
		ofSoundPlayer note12;
		ofSoundPlayer note13;
		/*voiceovers*/
		ofSoundPlayer voice1;
		ofSoundPlayer voice2;
		ofSoundPlayer voice3;
		ofSoundPlayer voice4;
		ofSoundPlayer voice5;
		ofSoundPlayer voice6;
		ofSoundPlayer voice7;
		ofSoundPlayer voice8;
		ofSoundPlayer voice9;
		ofSoundPlayer voice10;
		ofSoundPlayer voice11;
		ofSoundPlayer voice12;
		ofSoundPlayer voice13;

		ofSoundPlayer silence;
		
};
