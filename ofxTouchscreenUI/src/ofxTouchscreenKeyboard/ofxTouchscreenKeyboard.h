#pragma once

#include "ofMain.h"

struct ofxTouchscreenKeyboardKey {
	char key;
};

struct ofxTouchscreenKeyboardRow {
	bool hasSpacebar;
	vector<ofxTouchscreenKeyboardKey> keys;
};

class ofxTouchscreenKeyboard {

public:
	// functions
	ofxTouchscreenKeyboard();
	
	void keyPressed(ofKeyEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void draw();
	
	void drawColormap();
	ofxTouchscreenKeyboardRow addSpacebarRow(string keys);
	ofxTouchscreenKeyboardRow addKeysRow(string keys);
	
	void setFont(string newFontName, int size);
	void setKeyImage(string newKeyImage);
	void setSpacebarImage(string newSpacebarImage);
	void setColor(int newColor);
	
	// vars
	float x;
	float y;
	
private:
	
	// functions
	void addListeners();
	void updateColorMap();
	ofxTouchscreenKeyboardRow addKeysToRow(string keys);
	
	char getCharByMousePos(int x, int y);
	string charToString(char aChar);
	
	// vars
	vector<ofxTouchscreenKeyboardRow> rows;
	
	ofTrueTypeFont font;
	ofImage keyImageObject;
	ofImage spacebarImageObject;
	
	string keyImage;
	string spacebarImage;
	string fontName;
	int color;
	
	ofPixels colorMap;

};