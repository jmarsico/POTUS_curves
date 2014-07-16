/**
 * Curves demo
 * ofxTimeline
 *
 * Shows how to use ofxTimeline to create a simple curves and color change
 */
#include "ofMain.h"
#include "testApp.h"
//#include "ofAppGlutWindow.h"
#ifdef TARGET_OPENGLES
#include "ofGLProgrammableRenderer.h"
#endif

//========================================================================
int main( ){

    #ifdef TARGET_OPENGLES
        ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofGLProgrammableRenderer()));
        #endif
   // ofAppGlutWindow window;
        ofSetupOpenGL(1024,768, OF_WINDOW);                     // <-------- setup the GL context

        // this kicks off the running of my app
        // can be OF_WINDOW or OF_FULLSCREEN
        // pass in width and height too:
        ofRunApp( new testApp());

}

