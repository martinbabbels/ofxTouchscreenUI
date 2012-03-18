#include "ofxTouchscreenKeyboard.h"

/*
 * ofxTouchscreenKeyboard
 *
 */
ofxTouchscreenKeyboard::ofxTouchscreenKeyboard() {
	
	// Defaults
	setFont("TerminalDosis-Medium.ttf", 30);
	setKeyImage("key.png");
	setSpacebarImage("spacebar.png");
	setColor(0x000000);
	
	// Add listeners
	addListeners();
}

/*
 * Add listeners
 *
 */
void ofxTouchscreenKeyboard::addListeners() {
	ofAddListener(ofEvents.mousePressed,this,&ofxTouchscreenKeyboard::mousePressed);
}

/*
 * Mouse pressed listener
 *
 */
void ofxTouchscreenKeyboard::mousePressed(ofMouseEventArgs &e) {
	string str = charToString(getCharByMousePos(e.x, e.y));
	ofSendMessage(str);
}

/*
 * Draw
 *
 */
void ofxTouchscreenKeyboard::draw() {
	
	ofEnableAlphaBlending();
	
	// Draw the keys
	int row, key;
	
	for(row=0; row<rows.size(); ++row) {
		
		if(rows[row].hasSpacebar) {
			
			// Draw the spacebar
			ofSetHexColor(0xFFFFFF);
			spacebarImageObject.draw(0, row*keyImageObject.height);
		}
		
		for(key=0; key<rows[row].keys.size(); ++key) {
			
			ofSetHexColor(0xFFFFFF);
			
			keyImageObject.draw(key*keyImageObject.width, row*keyImageObject.height);
			
			string sc = charToString(rows[row].keys[key].key);
			ofRectangle sc_box = font.getStringBoundingBox(sc.c_str(),0,0);
			ofSetHexColor(color);
			
			int sc_x = key*keyImageObject.width + (keyImageObject.width/2 - sc_box.width/2);
			int sc_y = row*keyImageObject.height + (keyImageObject.height/2 + sc_box.height/2);
			
			font.drawString(sc, sc_x, sc_y);
		}
	}
	ofDisableAlphaBlending();
	
}

/*
 * Adds a row  with a spacebar and 
 * keys to the keyboard layout
 *
 */
ofxTouchscreenKeyboardRow ofxTouchscreenKeyboard::addSpacebarRow(string keys) {
	ofxTouchscreenKeyboardRow row = addKeysToRow(keys);
	row.hasSpacebar = true;
	return row;
}

/*
 * Adds a row of keys to the keyboard layout
 *
 */
ofxTouchscreenKeyboardRow ofxTouchscreenKeyboard::addKeysRow(string keys) {
	ofxTouchscreenKeyboardRow row = addKeysToRow(keys);
	
	return row;
}

/*
 * Adds a row of keys to the keyboard layout
 *
 */
ofxTouchscreenKeyboardRow ofxTouchscreenKeyboard::addKeysToRow(string keys) {
	ofxTouchscreenKeyboardRow row;
	vector<ofxTouchscreenKeyboardKey> v_keys;	
	
	int i;
	
	for(i=0; i<keys.size(); ++i) {
		
		ofxTouchscreenKeyboardKey key;
		key.key = keys.at(i);
		
		v_keys.push_back(key);
	}
	
	row.keys = v_keys;
	rows.push_back(row);
	
	// Update the color hit map
	updateColorMap();
	
	return row;
}

/*
 * Sets the keyboard font
 *
 */
void ofxTouchscreenKeyboard::setFont(string newFontName, int size) {
	fontName = newFontName;
	font.loadFont(newFontName, size);
}

/*
 * Sets the background image for a key
 *
 */
void ofxTouchscreenKeyboard::setKeyImage(string newKeyImage) {
	keyImage = newKeyImage;
	keyImageObject.loadImage(keyImage);
}

/*
 * Sets the spacebar image
 *
 */
void ofxTouchscreenKeyboard::setSpacebarImage(string newSpacebarImage) {
	spacebarImage = newSpacebarImage;
	spacebarImageObject.loadImage(spacebarImage);
}

/*
 * Sets  the font color
 *
 */
void ofxTouchscreenKeyboard::setColor(int newColor) {
	color = newColor;
}

/*
 * Updates the color hit map
 *
 */
void ofxTouchscreenKeyboard::updateColorMap() {
	if(rows.size()==0)
		return;
	
	int row, key, w, h;
	
	int map_w = rows[0].keys.size() * keyImageObject.width;
	
	
	//@todo optimize
	if(rows.size()>1) {
		
		for(row=1; row<rows.size(); ++row) {
			if(rows[row].keys.size() > rows[row-1].keys.size()) {
				map_w = rows[row].keys.size() * keyImageObject.width;
			}
		}
	}
	int map_h = (rows.size()) * keyImageObject.height;
	
	colorMap.clear();
	colorMap.allocate(map_w, map_h, OF_IMAGE_COLOR);
	
	
	// Draw keys
	for(row=0; row<rows.size(); ++row) {
		
		if(rows[row].hasSpacebar) {
			for(w=0; w<spacebarImageObject.width; ++w) {
				for(h=0; h<spacebarImageObject.height; ++h) {
					colorMap.setColor(w, h, 32);
				}
			}
			
		}
		
		for(key=0; key<rows[row].keys.size(); ++key) {
			
		
			ofColor char_color;
			char_color.set((int)rows[row].keys[key].key, 255.0);
			cout << char_color.r << endl;
			for(w=0; w<keyImageObject.width; ++w) {
				for(h=0; h<keyImageObject.height; ++h) {
					colorMap.setColor((key*keyImageObject.width)+w, (row*keyImageObject.height)+h, char_color);
				}
			}
		}
	}
}

/*
 * Gets the pressed key
 *
 */
char ofxTouchscreenKeyboard::getCharByMousePos(int x, int y) {
	ofColor hit_color = colorMap.getColor(x, y);
	char hit_char = hit_color.getHex();
	
	return hit_char;
}

/*
 * Draws the color map for debugging
 *
 */
void ofxTouchscreenKeyboard::drawColormap() {
	// Debug to draw the color map
	ofImage debug_map;
	debug_map.setFromPixels(colorMap.getPixels(), colorMap.getWidth(), colorMap.getHeight(), OF_IMAGE_COLOR);
	ofSetHexColor(0xFFFFFF);
	debug_map.draw(0, 0);
}

/*
 * A small char to string helper
 *
 */
string ofxTouchscreenKeyboard::charToString(char aChar) {
	string str;
	str.push_back(aChar);
	
	return str;
}