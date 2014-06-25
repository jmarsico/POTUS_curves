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
    ofSetLogLevel(OF_LOG_VERBOSE);
		
    //Timeline setup and playback details
    ofxTimeline::removeCocoaMenusFromGlut("CurvesColorsDemo");
    
    //this is the gui that will select which timeline to run
    buttonGui = new ofxUICanvas(10, ofGetHeight() - 100);
    
    //this gui will take the name of the new timeline
    gui2 = new ofxUICanvas(ofGetWidth()/2, ofGetHeight()-80, 100, 80);
    gui2->addLabel("Recipe Name", OFX_UI_FONT_MEDIUM);
	gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui2->addTextInput("Recipe", "");
    gui2->getWidget("Recipe")->setTriggerType(OFX_UI_TEXTINPUT_ON_ENTER);
    //gui2->autoSizeToFitWidgets();
    gui2->disable();
    
    //need to add a listener for the gui
    ofAddListener(gui2->newGUIEvent, this, &testApp::guiEvent);
    ofAddListener(buttonGui->newGUIEvent, this, &testApp::guiEvent);
    
    
    //this is the rectangle/button that adds a new timeline
    newButton.set(10, ofGetHeight() - 200, 200, 30);
    
    //index to keep track of which timeline to show/run
    currentTimelineIndex = 0;
    
}



//--------------------------------------------------------------
void testApp::update(){
    if(bShowText)
    {
        gui2->enable();
        
    }
    else
    {
        gui2->disable();
    }
    
    int x = 10;
    int guiHeight = buttonGui->getRect()->getHeight();
    int buttHeight = 30;
    int guiWidth = buttonGui->getRect()->getWidth();
    
    //change size and position of rectbutton
    if( guiHeight > 2)
    {
        newButton.set(x, ofGetHeight() - guiHeight - buttHeight, guiWidth, buttHeight);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
	
	int boxSize = 150;
    //ofBackground(.15*255);
	
    if(timelines.size() > 0)
    {
        ofPushMatrix();
        
            //translate to the center of the screen
            ofTranslate(ofGetWidth()*.5, ofGetHeight()*.66, 40);
            
            ofPushMatrix();
                ofTranslate(-boxSize*2.5, 0);
                ofFill();
                ofSetColor(9, 21, 110, timelines[currentTimelineIndex]->getValue("Deep_Blue" + ofToString(currentTimelineIndex)));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Deep Blue", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(-boxSize*1.5, 0);
                ofFill();
                ofSetColor(28, 45, 170, timelines[currentTimelineIndex]->getValue("Blue" + ofToString(currentTimelineIndex)));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Blue", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(-boxSize*0.5, 0);
                ofFill();
                ofSetColor(241, 10, 26, timelines[currentTimelineIndex]->getValue("Red" + ofToString(currentTimelineIndex)));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
                ofPopMatrix();
            ofPushMatrix();
                ofTranslate(boxSize*0.5, 0);
                ofFill();
                ofSetColor(151, 0, 38, timelines[currentTimelineIndex]->getValue("Deep_Red" + ofToString(currentTimelineIndex)));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Deep Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(boxSize*1.5, 0);
                ofFill();
                ofSetColor(100, 15, 21, timelines[currentTimelineIndex]->getValue("Infra_Red" + ofToString(currentTimelineIndex)));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Infra Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
        
        ofPopMatrix();
        

        timelines[currentTimelineIndex]->draw();
    }
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(newButton);

 
}


//--------------------------------------------------------------
void testApp::setupNewTimeline(){
  	ofLogVerbose() << "setting up new timeline";
    ofxTimeline* t = new ofxTimeline();
    
    t->setWorkingFolder("timeline");
    t->setup();
    t->setFrameRate(30);
    t->setDurationInSeconds(15);
	t->setLoopType(OF_LOOP_NORMAL);
    
	t->addCurves("Deep_Blue" + ofToString(timelines.size()), ofRange(0, 255));
    t->addCurves("Blue" + ofToString(timelines.size()), ofRange(0,255));
    t->addCurves("Red" + ofToString(timelines.size()), ofRange(0,255));
	t->addCurves("Deep_Red" + ofToString(timelines.size()), ofRange(0, 255));
    t->addCurves("Infra_Red" + ofToString(timelines.size()), ofRange(0, 255));
    t->setFrameBased(false);
    t->setAutosave(false);
    timelines.push_back(t);
    
    //set the current timeline to the newest timeline
    currentTimelineIndex = timelines.size()-1;
    
    //we want to save the first timeline
    if(timelines.size() == 1)
    {
        timelines[0]->saveTracksToFolder("timeline");
    }
    
    showOneTimeline(currentTimelineIndex);
    syncNewTimeline(currentTimelineIndex);

    
    
    
    //add a new button with the new filename and new ID
    buttonGui->addButton(fileName, false)->setID(timelines.size()-1);
    
    //tell me the ID
    ofLogVerbose() << "new ID: " << buttonGui->getWidget(fileName)->getID();
    
    //resize gui canvas
    buttonGui->autoSizeToFitWidgets();
    
    //re-position the gui canvas
    buttonGui->setPosition(10, ofGetHeight() - buttonGui->getRect()->getHeight());
    
    //tell me the number of timelines we have
    ofLogVerbose() << "setup new timeline complete, number of timelines: " << timelines.size();
}


//--------------------------------------------------------------
void testApp::syncNewTimeline(int timelineNum){
    
    file.copyFromTo("timeline/timeline0_Deep_Blue", "timeline/timeline"+ofToString(timelineNum)+"_Deep_Blue.xml", true, true);
    file.copyFromTo("timeline/timeline0_Blue", "timeline/timeline"+ofToString(timelineNum)+"_Blue.xml", true, true);
    file.copyFromTo("timeline/timeline0_Red", "timeline/timeline"+ofToString(timelineNum)+"_Red.xml", true, true);
    file.copyFromTo("timeline/timeline0_Deep_Red", "timeline/timeline"+ofToString(timelineNum)+"_Deep_Red.xml", true, true);
    file.copyFromTo("timeline/timeline0_Infra_Red", "timeline/timeline"+ofToString(timelineNum)+"_Infra_Red.xml", true, true);
    
    timelines[timelineNum]->loadTracksFromFolder("timeline/");
    
}



//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    
    if(e.getName() == "Recipe")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        fileName = textinput->getTextString();
        if(fileName != "")
        {
            ofLog() << "text input: " << fileName;
            setupNewTimeline();
            bShowText = false;
        }
    }
    
    //if the event is a button:
    if(e.getKind() == OFX_UI_WIDGET_BUTTON)
    {
        currentTimelineIndex = buttonGui->getWidget(e.getName())->getID();
        showOneTimeline(currentTimelineIndex);
        ofLogVerbose() << "gui button clicked: " << e.getName() << " ID: " << currentTimelineIndex;
    }
  
}

//--------------------------------------------------------------
void testApp::showOneTimeline(int timelineNum){
    //hide all other timelines
    for(int i = 0; i < timelines.size(); i++)
    {
        if(i != timelineNum)
        {
            timelines[i]->hide();
        }
    }
    //show and draw current timeline
    timelines[timelineNum]->show();
}



//--------------------------------------------------------------
void testApp::exit()
{
    delete gui2;
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
void testApp::mousePressed(int x, int y, int _button){
    ofPoint mousePoint;
    mousePoint.set(x, y);
    if(newButton.inside(mousePoint))
    {
        ofLog() << "newButton Pressed";
        bShowText = !bShowText;
    }

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
	