#include "ofApp.h"

bool display_font = true;
int choice = 0;
ofSoundPlayer current_sound;
//--------------------------------------------------------------
void ofApp::setup(){
	//bLearnBackground saves the background image on the first frame
	//initially setting to true 
	bLearnBackground = true;
	//set up the camera
	camWidth = 960;
	camHeight = 582;
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth, camHeight);
	//allocate space for the images
	colorImg.allocate(camWidth, camHeight);
	grayImg.allocate(camWidth, camHeight);
	grayBg.allocate(camWidth, camHeight);
	grayDiff.allocate(camWidth, camHeight);
	image.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
	//set the threshold, which can be manually changed
	threshold = 80;
	//load the font
	myFont.load("Montserrat-Bold.ttf", 18);

	/*load all the sound files*/
	/***********************************************piano******************************************************/
	note1.load("piano_sounds/held_C.wav");
	note1.setMultiPlay(true);
	note2.load("piano_sounds/held_C#.wav");
	note2.setMultiPlay(true);
	note3.load("piano_sounds/held_D.wav");
	note3.setMultiPlay(true);
	note4.load("piano_sounds/held_D#.wav");
	note4.setMultiPlay(true);
	note5.load("piano_sounds/held_E.wav");
	note5.setMultiPlay(true);
	note6.load("piano_sounds/held_F.wav");
	note6.setMultiPlay(true);
	note7.load("piano_sounds/held_F#.wav");
	note7.setMultiPlay(true);
	note8.load("piano_sounds/held_G.wav");
	note8.setMultiPlay(true);
	note9.load("piano_sounds/held_G#.wav");
	note9.setMultiPlay(true);
	note10.load("piano_sounds/held_A.wav");
	note10.setMultiPlay(true);
	note11.load("piano_sounds/held_A#.wav");
	note11.setMultiPlay(true);
	note12.load("piano_sounds/held_B.wav");
	note12.setMultiPlay(true);
	note13.load("piano_sounds/held_C_HIGH.wav");
	note13.setMultiPlay(true);
	/************************************************** voiceovers *****************************************************/
	voice1.load("voice_overs/john_redcorn.wav");
	voice1.setMultiPlay(true);
	voice2.load("voice_overs/tina.wav");
	voice2.setMultiPlay(true);
	voice3.load("voice_overs/bob.wav");
	voice3.setMultiPlay(true);
	voice4.load("voice_overs/dale.wav");
	voice4.setMultiPlay(true);
	voice5.load("voice_overs/bill.wav");
	voice5.setMultiPlay(true);
	voice6.load("voice_overs/craig.wav");
	voice6.setMultiPlay(true);
	voice7.load("voice_overs/hal.wav");
	voice7.setMultiPlay(true);
	voice8.load("voice_overs/linda.wav");
	voice8.setMultiPlay(true);
	voice9.load("voice_overs/lois.wav");
	voice9.setMultiPlay(true);
	voice10.load("voice_overs/hank.wav");
	voice10.setMultiPlay(true);
	voice11.load("voice_overs/bobby.wav");
	voice11.setMultiPlay(true);
	voice12.load("voice_overs/luanne.wav");
	voice12.setMultiPlay(true);
	voice13.load("voice_overs/dewey.wav");
	voice13.setMultiPlay(true);
	//silence is needed because there is always a current_sound playing
	silence.load("silence.wav");
	silence.setMultiPlay(true);
	silence.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	//update the image
	vidGrabber.update();
	ofPixelsRef pixelRef = vidGrabber.getPixels();
	image.setFromPixels(pixelRef);
	//for the opencv tools
	if (vidGrabber.isFrameNew()) {
		colorImg.setFromPixels(pixelRef);
		grayImg = colorImg;
		if (bLearnBackground == true) {	//to update the background
			grayBg = grayImg;
			bLearnBackground = false;
		}
		grayDiff.absDiff(grayBg, grayImg);
		grayDiff.threshold(threshold);
		//findContours(ofxCvGrayscaleImage &input, int minArea, int maxArea,
			//int nConsidered, bool bFindHoles, bool bUseApproximation=true)
		contourFinder.findContours(grayDiff, 20, (camWidth*camHeight)/4, 4, true);
	}
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor(188, 143, 143));
	ofSetHexColor(0xffffff);
	colorImg.draw(20, 20, camWidth, camHeight);
	ofFill();
	ofSetHexColor(0x333333);
	ofDrawRectangle(20, 20 + camHeight, camWidth, camHeight);
	contourFinder.draw(20, 20 + camHeight, camWidth, camHeight);

	//put the text of what the users options are on the screen
	if (display_font) {
		ofSetColor(0, 0, 100);
		myFont.drawString(" Point here", 30, 40);
		myFont.drawString("to play piano", 30, 60);
		ofSetColor(100, 0, 0);
		myFont.drawString("    Point here", 800, 40);
		myFont.drawString("to hear voiceovers", 800, 60);
		//get the bounding boxes of the options texts
		ofRectangle pianoRect1 = myFont.getStringBoundingBox(" Point here", 30, 40);
		ofRectangle pianoRect2 = myFont.getStringBoundingBox("to play piano", 30, 60);
		ofRectangle voiceRect1 = myFont.getStringBoundingBox("    Point here", 800, 40);
		ofRectangle voiceRect2 = myFont.getStringBoundingBox("to hear voiceovers", 800, 60);
		//get the bounding box by going through the blobs in contour
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			ofRectangle blobRect = contourFinder.blobs[i].boundingRect;
			//check if the rects of the contourRect and the textRect intersect
			if (blobRect.intersects(pianoRect1) || blobRect.intersects(pianoRect2)) {
				//there is an intersection with piano
				display_font = false;
				choice = 1;
				break;
			}
			else if (blobRect.intersects(voiceRect1) || blobRect.intersects(voiceRect2)) {
				//there is an intersection with voiceovers
				display_font = false;
				choice = 2;
				break;
			}
			else {
				//display_font = true;
				choice = 0;
			}
		}
	}
	//we are in the voice or piano mode
	//1 for piano, 2 for voiceovers
	else {
		if (choice == 1) {	//piano mode
			ofSetColor(0, 0, 100);
			myFont.drawString("C", 30, 60);
			myFont.drawString("C#", 80, 60);
			myFont.drawString("D", 140, 60);
			myFont.drawString("D#", 200, 60);
			myFont.drawString("E", 260, 60);
			myFont.drawString("F", 320, 60);
			myFont.drawString("F#", 380, 60);
			myFont.drawString("G", 440, 60);
			myFont.drawString("G#", 500, 60);
			myFont.drawString("A", 560, 60);
			myFont.drawString("A#", 620, 60);
			myFont.drawString("B", 680, 60);
			myFont.drawString("C", 740, 60);
			myFont.drawString("Exit Piano", 820, 560);
			//get the bounding boxes for the notes text boxes
			ofRectangle c = myFont.getStringBoundingBox("C", 20, 60);
			ofRectangle c2 = myFont.getStringBoundingBox("C#", 80, 60);
			ofRectangle d = myFont.getStringBoundingBox("D", 140, 60);
			ofRectangle d2 = myFont.getStringBoundingBox("D#", 200, 60);
			ofRectangle e = myFont.getStringBoundingBox("E", 260, 60);
			ofRectangle f = myFont.getStringBoundingBox("F", 320, 60);
			ofRectangle f2 = myFont.getStringBoundingBox("F#", 380, 60);
			ofRectangle g = myFont.getStringBoundingBox("G", 440, 60);
			ofRectangle g2 = myFont.getStringBoundingBox("G#", 500, 60);
			ofRectangle a = myFont.getStringBoundingBox("A", 560, 60);
			ofRectangle a2 = myFont.getStringBoundingBox("A#", 620, 60);
			ofRectangle b = myFont.getStringBoundingBox("B", 680, 60);
			ofRectangle c_high = myFont.getStringBoundingBox("C", 740, 60);
			ofRectangle exit = myFont.getStringBoundingBox("Exit Piano", 820, 560);
			//go through the contour blobs to check if there is overlap to play a note
			for (int i = 0; i < contourFinder.nBlobs; i++) {
				ofRectangle blobRect = contourFinder.blobs[i].boundingRect;
				//check if the rects of the contourRect and the textRect intersect
				if (blobRect.intersects(exit)) {	//there is an intersection with exit
					//stop whatever notes are currently playing from playing
					while (!note_queue.empty()) {
						ofSoundPlayer temp = note_queue.front();
						temp.stop();
						note_queue.pop();
					}
					display_font = true;
					choice = 0;
					break;
				}
				//set the note that was chosen to play (or play silence)
				else if (blobRect.intersects(c)) { current_sound = note1; }
				else if (blobRect.intersects(c2)) { current_sound = note2; }
				else if (blobRect.intersects(d)) { current_sound = note3; }
				else if (blobRect.intersects(d2)) { current_sound = note4; }
				else if (blobRect.intersects(e)) { current_sound = note5; }
				else if (blobRect.intersects(f)) { current_sound = note6; }
				else if (blobRect.intersects(f2)) { current_sound = note7; }
				else if (blobRect.intersects(g)) { current_sound = note8; }
				else if (blobRect.intersects(g2)) { current_sound = note9; }
				else if (blobRect.intersects(a)) { current_sound = note10; }
				else if (blobRect.intersects(a2)) { current_sound = note11; }
				else if (blobRect.intersects(b)) { current_sound = note12; }
				else if (blobRect.intersects(c_high)) { current_sound = note13; }
				else { current_sound = silence; }
				if (!current_sound.isPlaying()) {
					current_sound.play();
					note_queue.push(current_sound);
				}
			}
		}
		if (choice == 2) {	//voiceovers
			ofSetColor(100, 0, 0);
			myFont.drawString("1", 30, 60);
			myFont.drawString("2", 80, 60);
			myFont.drawString("3", 140, 60);
			myFont.drawString("4", 200, 60);
			myFont.drawString("5", 260, 60);
			myFont.drawString("6", 320, 60);
			myFont.drawString("7", 380, 60);
			myFont.drawString("8", 440, 60);
			myFont.drawString("9", 500, 60);
			myFont.drawString("10", 560, 60);
			myFont.drawString("11", 620, 60);
			myFont.drawString("12", 680, 60);
			myFont.drawString("13", 740, 60);
			myFont.drawString("Exit Voices", 20, 560);
			//get bounding boxes of text options
			ofRectangle one = myFont.getStringBoundingBox("1", 20, 60);
			ofRectangle two = myFont.getStringBoundingBox("2", 80, 60);
			ofRectangle three = myFont.getStringBoundingBox("3", 140, 60);
			ofRectangle four = myFont.getStringBoundingBox("4", 200, 60);
			ofRectangle five = myFont.getStringBoundingBox("5", 260, 60);
			ofRectangle six = myFont.getStringBoundingBox("6", 320, 60);
			ofRectangle seven = myFont.getStringBoundingBox("7", 380, 60);
			ofRectangle eight = myFont.getStringBoundingBox("8", 440, 60);
			ofRectangle nine = myFont.getStringBoundingBox("9", 500, 60);
			ofRectangle ten = myFont.getStringBoundingBox("10", 560, 60);
			ofRectangle eleven = myFont.getStringBoundingBox("11", 620, 60);
			ofRectangle twelve = myFont.getStringBoundingBox("12", 680, 60);
			ofRectangle thirteen = myFont.getStringBoundingBox("13", 740, 60);
			ofRectangle exit = myFont.getStringBoundingBox("Exit Voices", 20, 560);
			//go through contour blobs to check for overlap
			for (int i = 0; i < contourFinder.nBlobs; i++) {
				ofRectangle blobRect = contourFinder.blobs[i].boundingRect;
				if (blobRect.intersects(exit)) {
					//there is an intersection with exit
					while (!note_queue.empty()) {
						ofSoundPlayer temp = note_queue.front();
						temp.stop();
						note_queue.pop();
					}
					display_font = true;
					choice = 0;
					break;
				}
				//get the voiceover that the user is selecting
				else if (blobRect.intersects(one)) { current_sound = voice1; }
				else if (blobRect.intersects(two)) { current_sound = voice2; }
				else if (blobRect.intersects(three)) { current_sound = voice3; }
				else if (blobRect.intersects(four)) { current_sound = voice4; }
				else if (blobRect.intersects(five)) { current_sound = voice5; }
				else if (blobRect.intersects(six)) { current_sound = voice6; }
				else if (blobRect.intersects(seven)) { current_sound = voice7; }
				else if (blobRect.intersects(eight)) { current_sound = voice8; }
				else if (blobRect.intersects(nine)) { current_sound = voice9; }
				else if (blobRect.intersects(ten)) { current_sound = voice10; }
				else if (blobRect.intersects(eleven)) { current_sound = voice11; }
				else if (blobRect.intersects(twelve)) { current_sound = voice12; }
				else if (blobRect.intersects(thirteen)) { current_sound = voice13; }
				else { current_sound = silence; }
				if (!current_sound.isPlaying()) {
					current_sound.play();
					note_queue.push(current_sound);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		//if spacebar is pressed, the program will relearn the background
		case ' ':
			bLearnBackground = true;
			display_font = true;
			while (!note_queue.empty()) {
				ofSoundPlayer temp = note_queue.front();
				temp.stop();
				note_queue.pop();
			}
			break;
		//change the threshold with + and -
		case '+':
			threshold++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold--;
			if (threshold < 0) threshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
