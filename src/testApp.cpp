/**
 * ofxTimeline -- AudioWaveform Example
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George http://www.jamesgeorge.org
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/ +
 *
 * http://github.com/YCAMinterLab
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
	
	glEnable(GL_DEPTH_TEST);
	ofEnableLighting();
	
	light.setPosition(ofGetWidth()*.5, ofGetHeight()*.25, 0);
	light.enable();
		
    //Timeline setup and playback details
    ofxTimeline::removeCocoaMenusFromGlut("CurvesColorsDemo");
    
	timeline.setup();
    timeline.setFrameRate(30);
	//timeline.setDurationInFrames(90);
    timeline.setDurationInSeconds(15);
	timeline.setLoopType(OF_LOOP_NORMAL);
    
	//each call to "add keyframes" add's another track to the timeline
	timeline.addCurves("Deep Blue", ofRange(0, 255));
    timeline.addCurves("Blue", ofRange(0,255));
    timeline.addCurves("Red", ofRange(0,255));
	timeline.addCurves("Deep Red", ofRange(0, 255));
    timeline.addCurves("Infra Red", ofRange(0, 255));
    


    //setting framebased to true results in the timeline never skipping frames
    //and also speeding up with the 
    //try setting this to true and see the difference
    timeline.setFrameBased(false);
	
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	int boxSize = 100;
    ofBackground(.15*255);
	ofPushMatrix();
	
        //translate to the center of the screen
        ofTranslate(ofGetWidth()*.5, ofGetHeight()*.66, 40);
        
        ofPushMatrix();
    ofPushStyle();
            ofTranslate(-boxSize*2.5, 0);
            ofFill();
            ofSetColor(9, 21, 110, timeline.getValue("Deep Blue"));
            ofRect(0, 0, boxSize,boxSize);
            ofNoFill();
            ofSetColor(200);
            ofDrawBitmapString("Deep Blue", 5,12);
            ofRect(0,0,boxSize,boxSize);
    ofPopStyle();
        ofPopMatrix();
        ofPushMatrix();
            ofTranslate(-boxSize*1.5, 0);
            ofFill();
            ofSetColor(28, 45, 170, timeline.getValue("Blue"));
            ofRect(0, 0, boxSize,boxSize);
            ofNoFill();
            ofSetColor(200);
            ofDrawBitmapString("Blue", 5,12);
            ofRect(0,0,boxSize,boxSize);
        ofPopMatrix();
        ofPushMatrix();
            ofTranslate(-boxSize*0.5, 0);
            ofFill();
            ofSetColor(241, 10, 26, timeline.getValue("Red"));
            ofRect(0, 0, boxSize,boxSize);
            ofNoFill();
            ofSetColor(200);
            ofDrawBitmapString("Red", 5,12);
            ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
        ofPushMatrix();
            ofTranslate(boxSize*0.5, 0);
            ofFill();
            ofSetColor(151, 0, 38, timeline.getValue("Deep Red"));
            ofRect(0, 0, boxSize,boxSize);
            ofNoFill();
            ofSetColor(200);
            ofDrawBitmapString("Deep Red", 5,12);
            ofRect(0,0,boxSize,boxSize);
        ofPopMatrix();
        ofPushMatrix();
            ofTranslate(boxSize*1.5, 0);
            ofFill();
            ofSetColor(100, 15, 21, timeline.getValue("Infra Red"));
            ofRect(0, 0, boxSize,boxSize);
            ofNoFill();
            ofSetColor(200);
            ofDrawBitmapString("Infra Red", 5,12);
            ofRect(0,0,boxSize,boxSize);
        ofPopMatrix();
    
    
        ofPopMatrix();
    ofRect(0, 0, 100, 100);
	
	timeline.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
	