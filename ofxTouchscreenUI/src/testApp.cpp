#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	bg.loadImage("background.jpg");
	
	ui.addFont("default", "ui_font.ttf", 15);
	ui.addFont("textinput", "ui_font.ttf", 20);
	
	ui.setDefaultFont("default", 0xd0d2d3);

	keyboard = ui.addKeyboard(50,200);
	keyboard->addKeys("!@#$%^&*()");		// row 0
	keyboard->addKeys("1234567890");		// row 1
	keyboard->addKeys("QWERTYUIOP");		// row 2
	keyboard->addKeys("ASDFGHJKL");			// row 3
	keyboard->addKeys("ZXCVBNM");			// row 4
	
	keyboard->addButtonToRow(OFX_TSUI_KEY_BACKSPACE
							 ,"key_on_medium.png"
							 ,"key_off_medium.png"
							 ,0x00FF00
							 ,"Delete"
							 ,0xd0d2d3
							 ,0);
	
	ofxTouchscreenButton* backspace = keyboard->addButton(OFX_TSUI_KEY_SPACEBAR
						,"key_on_spacebar.png"
						,"key_off_spacebar.png"
						,0xE8E8E8);
	
	name = ui.addTextInput(50
						   ,100
						   ,"textinput_on.png"
						   ,"textinput_off.png"
						   ,0xFFFF00
						   ,"text"
						   ,0x000000
						   ,keyboard);
	
	name->padding = 37;
	name->setFont("textinput");
	
	ui.addLabel(300, 20, "ofxTouchscreenUI Demo");
	
	ui.addListener(this);
	
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	bg.draw(0, 0);
	ui.draw();
	//ui.drawHitMap();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	//
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
	cout << msg.message << endl;
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::onTouchscreenEvent(ofxTouchscreenUI_Event &e) {
	cout << e.event.elementId << endl;
}