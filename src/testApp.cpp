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

/*
 TODO:
 

 - two modes: preview and realtime
 
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
    currentTimelineName = "";
    currentTime = 0;
    currentTimeString = "";
    
    
    ////////////////// FONTS /////////////////////////
    
    
    ofTrueTypeFont::setGlobalDpi(72);
    
	type_bebas.loadFont("BEBAS___.ttf", 90, true, true);
	type_bebas.setLineHeight(18.0f);
	type_bebas.setLetterSpacing(1.037);
    
    
    ////////////  setup the timelines ////////////
    for(int i = 0; i < 4; i++)
    {
        //set the name of the timeline before setting it up
        switch (i) {
            case 0:
                fileName = "one";
                break;
                
            case 1:
                fileName = "two";
                break;
            
            case 2:
                fileName = "three";
                break;
                
            case 3:
                fileName = "four";
                break;
                
            default:
                break;
        }
        setupNewTimeline();
    }
    
    //setup XML for last time and currentTimelineIndex
    if(timeXML.load("lastTime.xml")) ofLog() << "XML loaded successfully";
    else ofLog() << "XML did not load, check data/ folder";
    
    loadCurrentTime();
}

//--------------------------------------------------------------
void testApp::update(){
    
    int x = 10;
    int guiHeight = buttonGui->getRect()->getHeight();
    int buttHeight = 30;
    int guiWidth = buttonGui->getRect()->getWidth();
    
    //change size and position of rectbutton
    if( guiHeight > 2)
    {
        newButton.set(x, ofGetHeight() - guiHeight - buttHeight, guiWidth, buttHeight);
    }
    
    //get the currentTime
    if(timelines.size() > 0)
    {
        currentTime = floorf(timelines[currentTimelineIndex]->getCurrentTime() * 100) / 100;
        currentTimeString = timelines[currentTimelineIndex]->getCurrentTimecode();
        
        
    }
    
    saveCurrentTime();
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
                ofSetColor(9, 21, 110, timelines[currentTimelineIndex]->getValue("Deep_Blue"));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Deep Blue", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(-boxSize*1.5, 0);
                ofFill();
                ofSetColor(28, 45, 170, timelines[currentTimelineIndex]->getValue("Blue" ));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Blue", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(-boxSize*0.5, 0);
                ofFill();
                ofSetColor(241, 10, 26, timelines[currentTimelineIndex]->getValue("Red"));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
                ofPopMatrix();
            ofPushMatrix();
                ofTranslate(boxSize*0.5, 0);
                ofFill();
                ofSetColor(151, 0, 38, timelines[currentTimelineIndex]->getValue("Deep_Red"));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Deep Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
            ofPushMatrix();
                ofTranslate(boxSize*1.5, 0);
                ofFill();
                ofSetColor(100, 15, 21, timelines[currentTimelineIndex]->getValue("Infra_Red"));
                ofRect(0, 0, boxSize,boxSize);
                ofNoFill();
                ofSetColor(200);
                ofDrawBitmapString("Infra Red", 5,12);
                ofRect(0,0,boxSize,boxSize);
            ofPopMatrix();
        
        ofPopMatrix();

        timelines[currentTimelineIndex]->draw();
    }
    
    
    //draw the pagename
    ofSetColor(0);
    
    stringstream displayString;
    if(timelines.size() > 0)
    {
        displayString << currentTimelineName << " | " << currentTimeString << endl;
    }
    
    int stringW = type_bebas.stringWidth(displayString.str());
    int stringH = type_bebas.stringHeight(displayString.str());
    type_bebas.drawString(displayString.str(), ofGetWidth()/2-stringW/2,
                          ofGetHeight()/2-stringH/2);

    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(newButton);
 
}

//--------------------------------------------------------------
void testApp::setupNewTimeline(){
  	ofLogVerbose() << "setting up new timeline";
    currentTimelineName = fileName;
    
    ofxTimeline* t = new ofxTimeline();
    
    t->setup();
    t->setFrameRate(30);
    t->setDurationInSeconds(24*60*60);
	t->setLoopType(OF_LOOP_NORMAL);
    
    
	t->addCurves("Deep_Blue", ofRange(0, 255));
    t->addCurves("Blue", ofRange(0,255));
    t->addCurves("Red", ofRange(0,255));
	t->addCurves("Deep_Red", ofRange(0, 255));
    t->addCurves("Infra_Red", ofRange(0, 255));
    t->setFrameBased(false);
    //t->setAutosave(false);
    //t->setName(currentTimelineName);
    timelines.push_back(t);
    
    showOneTimeline(currentTimelineIndex);

    
    
    //add a new button with the new filename and new ID
    buttonGui->addButton(fileName, false)->setID(timelines.size()-1);
    
    //tell me the ID
    //ofLogVerbose() << "new ID: " << buttonGui->getWidget(t->getName())->getID();
    
    //resize gui canvas
    buttonGui->autoSizeToFitWidgets();
    //re-position the gui canvas
    buttonGui->setPosition(10, ofGetHeight() - buttonGui->getRect()->getHeight());
    
    //tell me the number of timelines we have
    ofLogVerbose() << "setup new timeline complete, number of timelines: " << timelines.size();
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
    
    if(e.getName() == "Recipe")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        fileName = textinput->getTextString();
        if(fileName != "")
        {
            ofLog() << "text input: " << fileName;
            setupNewTimeline();
        }
    }
    
    //if the event is a button:
    if(e.getKind() == OFX_UI_WIDGET_BUTTON)
    {
        currentTimelineIndex = buttonGui->getWidget(e.getName())->getID();
        showOneTimeline(currentTimelineIndex);
        currentTimelineName = e.getName();
        ofLogVerbose() << endl << "******************************" << endl <<
        "gui button clicked: " << currentTimelineName << " | ID: " << currentTimelineIndex << endl ;
        
    }
    
    if(e.getName() == "Go To Start")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
		if(toggle->getValue())
        {
            for(int i = 0; i < timelines.size(); i++)
            {
                timelines[i]->setDurationInSeconds(24);
            }
        }
        else
        {
            for(int i = 0; i < timelines.size(); i++)
            {
                timelines[i]->setDurationInSeconds(24*60*60);
            }
        }
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
            timelines[i]->stop();
        }
    }
    //show and draw current timeline
    timelines[timelineNum]->show();
}

//--------------------------------------------------------------
void testApp::saveTimelines(){
    
    for(int i = 0; i < timelines.size(); i++)
    {
        timelines[i]->saveTracksToFolder("timeline/timeline_" + timelines[i]->getName());
    }
    
    ofGetSystemTime();
}

//--------------------------------------------------------------
void testApp::saveCurrentTime(){
    int currentTime = timelines[currentTimelineIndex]->getCurrentTime();
    
    timeXML.clear();
    timeXML.setValue("time", currentTime);
    timeXML.setValue("timelineIndex", currentTimelineIndex);
    timeXML.setValue("isPlaying", timelines[currentTimelineIndex]->getIsPlaying());
    timeXML.setValue("name", currentTimelineName);
    if(!timeXML.save("lastTime.xml"))
    {
       ofLogVerbose() << "failing to save current settings";
    }
}

//--------------------------------------------------------------
void testApp::loadCurrentTime(){
    
    currentTimelineIndex = timeXML.getValue("timelineIndex", 0);
    currentTimelineName = timeXML.getValue("name", "");
    showOneTimeline(currentTimelineIndex);
    timelines[currentTimelineIndex]->setCurrentTimeSeconds(timeXML.getValue("time", 0));
    
    if(timeXML.getValue("isPlaying", 0))
    {
        timelines[currentTimelineIndex]->play();
    }
}

//--------------------------------------------------------------
void testApp::exit(){
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
        //bShowText = !bShowText;
        if(timelines[currentTimelineIndex]->getIsPlaying())
        {
            timelines[currentTimelineIndex]->stop();
        }
        else timelines[currentTimelineIndex]->play();
        
        
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
	