#include "testApp.h"
#include "ofxSimpleGuiToo.h"
#include "ofxCv.h"
int preset = 0;
int lastPreset = 0;
ofImage *Particle::img = NULL;




//--------------------------------------------------------------
void testApp::setup(){


	pd.load("patches/mouth1.pd", 0, 2, 44100, 256);
	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60.f);

	WIDTH = 320;
	HEIGHT = 240;

	int sourceWidth = 320;
	int sourceHeight = 240;

	vidGrabber.setVerbose(true);

	sourceWidth = WIDTH;
	sourceHeight = HEIGHT;

	vidGrabber.initGrabber(WIDTH, HEIGHT);




    tracker.setup();
    tracker.setScale(0.5);
    
    mouths.push_back(Mouth());
	ofSoundStreamSetup(2,0,this, 44100,256, 1);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0,0,0);

   vidGrabber.grabFrame();
   bool bNewFrame = vidGrabber.isFrameNew();
    
	
	if (bNewFrame){
        tracker.update(ofxCv::toCv(vidGrabber.getPixelsRef()));

        ofRectangle rect(10, 10, 100, 100);
        mouths[0].update(rect);
        
		float pitch = 0;
		float filter = 0;
        
		for(int i = 0; i < mouths.size(); i++) {
			
			pitch = mouths[i].getPitch();
			filter = mouths[i].getFilter();
			
			pd.sendFloat("volume"+ofToString(i), mouths[i].isOpen()?1:0);
			if(mouths[i].isOpen()) {
				pd.sendFloat("pitch"+ofToString(i), pitch);
				pd.sendFloat("filter"+ofToString(i), filter);
				pd.sendFloat("pan"+ofToString(i), mouths[i].getPan());
			}
		}
		for(int i = 0; i < mouths.size(); i++) {
			if(mouths[i].isOpen() && ofRandom(0, 1)>0.5) { //mouthJustOpened()) {
				printf("Just opened\n");
				particles.push_back(Particle(mouths[i].getPos(), mouths[i].getFilter()));
			}
		}
		
		
	}
	
	for(int i = 0; i < particles.size(); i++) {
		if(particles[i].isAlive()) {
			particles[i].update();
		
		} else {
			particles.erase(particles.begin()+i);
			i--;
		}

	}

}

//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending();
	
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    glPushMatrix();
    glScalef(ofGetWidth()/vidGrabber.getWidth(), ofGetHeight()/vidGrabber.getHeight(), 1);
    vidGrabber.draw(0, 0);
    for(int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    ofSetHexColor(0xFFFFFF);
    tracker.getImageMesh().drawWireframe();
    
    for(int i = 0; i < mouths.size(); i++) {
        mouths[i].draw();
    }

    glPopMatrix();
    // gui.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case ' ':
			//gui.toggleDraw();
			//bLearnBakground = true;
			break;
		case 'v':
			vidGrabber.videoSettings();

            break;
        case 'f':
			ofToggleFullscreen();
			break;
		
	}
	if(key>='1' && key <= '4') {
		preset = key - '1' + 1;		
	}
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
void testApp::windowResized(int w, int h){

}

float stuff[256];

//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	if(lastPreset!=preset) {
		string theFile = "patches/mouth";
		theFile += ofToString(preset);
		theFile += ".pd";
		pd.load(theFile, 0, 2, 44100, 256);

	}
	lastPreset = preset;
	


	pd.process(stuff, output, bufferSize);
	
	
}

