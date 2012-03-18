#pragma once

#include "ofMain.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

class ofxTouchscreenUI;
class ofxTouchscreenElement;
class ofxTouchscreenKeyboard;
class ofxTouchscreenTextInput;
class ofxTouchscreenButton;
class ofxTouchscreenListener;

enum ofxTouchcreenUI_Types {
	OFX_TSUI_BUTTON,
	OFX_TSUI_KEYBOARD,
	OFX_TSUI_TEXT_INPUT
};

enum ofxTouchcreenUI_Events {
	OFX_TSUI_EVENT_CHANGE,
	OFX_TSUI_EVENT_CLICK,
	OFX_TSUI_EVENT_FOCUS
};

/******************************************************************************
 * ofxTouchscreenEvent
 *
 *****************************************************************************/
struct ofxTouchscreenUI_EventParams {
	int		eventType;
	int		elementType;
	int		elementId;
	string	elementValue;
	
	ofxTouchscreenElement* element;
	ofxTouchscreenElement* target;
};

struct ofxTouchscreenUI_Event {
	ofxTouchscreenUI_Event(ofxTouchscreenUI_EventParams &e) {
		event = e;
	};
	ofxTouchscreenUI_EventParams event;
};

class ofxTouchscreenListener {
	
public:
	virtual void onTouchscreenEvent(ofxTouchscreenUI_Event &e){
	};
	void onTouchscreenEvent(const void * sender, ofxTouchscreenUI_Event &e) {
		onTouchscreenEvent(e);
	};
};

/******************************************************************************
 * ofxTouchscreenElement
 *
 *****************************************************************************/

class ofxTouchscreenElement {

public:
	
	ofxTouchscreenElement();
	
	virtual void setup();
	virtual void draw();
	
	virtual float getWidth() {
		return width;
	};
	virtual float getHeight() {
		return height;
	};
	virtual void focusIn() {
		hasFocus = true;
	};
	virtual void focusOut() {
		hasFocus = false;
	};
	virtual void mouseIn() {
		isMouseDown = true;
	};
	virtual void mouseOut() {
		isMouseDown = false;
	};
	virtual bool isTransparantPixel(int pixX, int pixY) {
		return false;
	};
	
	void setFont(string newFontName);
	void setFont(string newFontName, int newFontColor);
	
	
	// Hit map color
	ofColor mapColor;
	
	// Is mouse down
	bool isMouseDown;
	
	// Focus
	bool hasFocus;
	bool useFocus;
	
	// Position
	float x;
	float y;
	
	// Dimensions
	float width;
	float height;
	
	// Element type
	int elementType;
	
	// UI
	ofxTouchscreenUI *ui;
	
	// Font
	string fontName;
	int fontColor;

};

/******************************************************************************
 * ofxTouchscreenLabel
 *
 *****************************************************************************/
class ofxTouchscreenLabel : public ofxTouchscreenElement {
public:
	ofxTouchscreenLabel();
	void draw();
	
	// Text
	void setText(string labelText);
	string getText();
	
private:
	// Text
	string text;
};

/******************************************************************************
 * ofxTouchscreenTextInput
 *
 *****************************************************************************/
class ofxTouchscreenTextInput : 
public ofxTouchscreenElement, 
ofxTouchscreenListener {

public:
	
	ofxTouchscreenTextInput();
	void draw();
	void setup();
	void bindKeyboard(ofxTouchscreenKeyboard* keyboardEl);
	void onTouchscreenEvent(ofxTouchscreenUI_Event &e);
	bool isTransparantPixel(int pixX, int pixY);
	
	// Input text
	string text;
	
	// Input images
	string imageFileOn;
	string imageFileOff;
	
	ofImage imageOn;
	ofImage imageOff;
	
	// Padding
	int padding;
	
private:
	ofxTouchscreenKeyboard* keyboard;
};

/******************************************************************************
 * ofxTouchscreenButton
 *
 *****************************************************************************/
class ofxTouchscreenButton : public ofxTouchscreenElement {
	
public:
	
	ofxTouchscreenButton();
	void draw();
	void setup();
	bool isTransparantPixel(int pixX, int pixY);

	// Button text
	string text;
	
	// Button images
	string imageFileOn;
	string imageFileOff;
	
	ofImage imageOn;
	ofImage imageOff;
	
};

/******************************************************************************
 * ofxTouchscreenKeyboard
 *
 *****************************************************************************/
enum ofxTouchcreenKeyboard_Align {
	OFX_TSUI_ALIGN_LEFT,
	OFX_TSUI_ALIGN_CENTER,
	OFX_TSUI_ALIGN_RIGHT
};

enum ofxTouchcreenKeyboard_Keys {
	OFX_TSUI_KEY_CHAR,
	OFX_TSUI_KEY_ESC,
	OFX_TSUI_KEY_BACKSPACE,
	OFX_TSUI_KEY_SPACEBAR,
	OFX_TSUI_KEY_ENTER,
	OFX_TSUI_KEY_BUTTON
};

class ofxTouchscreenKeyboardKey : public ofxTouchscreenButton {
public:
	ofxTouchscreenKeyboardKey():type(OFX_TSUI_KEY_CHAR) {};
	int type;
};

struct ofxTouchscreenKeyboardRow {
	vector<ofxTouchscreenKeyboardKey* > keys;
};

class ofxTouchscreenKeyboard : public ofxTouchscreenElement {
	
public:
	
	ofxTouchscreenKeyboard();
	
	void draw();
	void setup();
	void mouseOut();
	void focusOut();
	void update();
	
	// Keys
	ofxTouchscreenKeyboardKey* getKey(ofColor color);
	ofxTouchscreenKeyboardKey* createKey(string key);
	
	// Keyboard ASCII key
	ofxTouchscreenKeyboardKey* addKey(char newKey);
	ofxTouchscreenKeyboardRow* addKeys(string newKeys);
	ofxTouchscreenKeyboardKey* addKeyToRow(char newKey, int row);
	
	// Custom button
	void addButton(ofxTouchscreenKeyboardKey* button);
	
	ofxTouchscreenKeyboardKey* addButton(string imageFileOn, 
										 string imageFileOff, 
										 int mapColor);
	
	ofxTouchscreenKeyboardKey* addButton(int type, 
										 string imageFileOn, 
										 string imageFileOff, 
										 int mapColor);
	
	ofxTouchscreenKeyboardKey* addButton(string imageFileOn, 
										 string imageFileOff, 
										 int mapColor, 
										 string text, 
										 int fontColor);
	
	ofxTouchscreenKeyboardKey* addButton(int type, 
										 string imageFileOn, 
										 string imageFileOff, 
										 int mapColor, 
										 string text, 
										 int fontColor);
	
	ofxTouchscreenKeyboardKey* addButtonToRow(string imageFileOn, 
											  string imageFileOff, 
											  int mapColor, 
											  int row);
	
	ofxTouchscreenKeyboardKey* addButtonToRow(string imageFileOn, 
											  string imageFileOff, 
											  int mapColor, 
											  string text, 
											  int fontColor, 
											  int row);
	
	ofxTouchscreenKeyboardKey* addButtonToRow(int type, 
											  string imageFileOn, 
											  string imageFileOff, 
											  int mapColor, 
											  int row);
	
	ofxTouchscreenKeyboardKey* addButtonToRow(int type, 
											  string imageFileOn, 
											  string imageFileOff, 
											  int mapColor, 
											  string text, 
											  int fontColor, 
											  int row);
	
	void addButtonToRow(ofxTouchscreenKeyboardKey* key, int row);
	
	ofxTouchscreenKeyboardKey* createButton(float x, 
											float y, 
											string imageFileOn, 
											string imageFileOff, 
											int mapColor);
	
	// Images
	void setKeyImages(string imageFileOn, string imageFileOff);
	string defaultImageFileOn;
	string defaultImageFileOff;
	
	// Rows
	int getRowX(int row);
	int getRowY(int row);
	vector<ofxTouchscreenKeyboardRow* > rows;
	
	// Spacing
	int rowSpacing;
	int keySpacing;
	
	// Alignment
	int alignment;
	
	
private:

	string charToString(char aChar);

};

/********************************************************************************
 * ofxTouchscreenUI_Font
 *
 ********************************************************************************/
struct ofxTouchscreenUI_Font {
	ofTrueTypeFont	font;
	string			fontName;
	string			fontFile;
	int				fontSize;
};

/********************************************************************************
 * ofxTouchscreenUI
 *
 ********************************************************************************/
class ofxTouchscreenUI {
	
public:
	
	ofxTouchscreenUI();
	
	void update();
	void draw();
	
	// Elements
	ofxTouchscreenElement* getElement(ofColor color);
	
	// Events
	void addListener(ofxTouchscreenListener *listener);
	void removeListener(ofxTouchscreenListener *listener);
	
	// Hit map
	ofxTouchscreenElement* getHitMapElement(ofColor color);
	ofColor getHitMapColor(int xPos, int yPos);
	
	void drawHitMap();
	void updateHitMap();
	
	// Buttons
	void addButton(ofxTouchscreenButton* button);
	ofxTouchscreenButton* addButton(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor);
	
	ofxTouchscreenButton* addButton(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor, 
									string text, 
									int fontColor);
	
	// Text input
	void addTextInput(ofxTouchscreenTextInput* button);
	ofxTouchscreenTextInput* addTextInput(float x, 
										  float y, 
										  string imageFileOn, 
										  string imageFileOff, 
										  int mapColor);
	
	ofxTouchscreenTextInput* addTextInput(float x, 
										  float y, string 
										  imageFileOn, 
										  string imageFileOff, 
										  int mapColor, 
										  string text, 
										  int fontColor);
	
	ofxTouchscreenTextInput* addTextInput(float x, 
										  float y, 
										  string imageFileOn, 
										  string imageFileOff, 
										  int mapColor, 
										  ofxTouchscreenKeyboard* keyboard);
	
	ofxTouchscreenTextInput* addTextInput(float x, 
										  float y, 
										  string imageFileOn, 
										  string imageFileOff, 
										  int mapColor, 
										  string text, 
										  int fontColor, 
										  ofxTouchscreenKeyboard* keyboard);
	
	// Label
	ofxTouchscreenLabel* addLabel(float xPos, float yPos, string text);
	
	// Keyboard
	ofxTouchscreenKeyboard* addKeyboard(float xPos, float yPos);
	
	// Font
	void addFont(string fontName, string fontFile, int size);
	void setDefaultFont(string fontName, int fontColor);
	ofxTouchscreenUI_Font* getFont(string fontName);
	
	// Position
	float x;
	float y;
	
	// Default font
	string defaultFontName;
	int defaultFontSize;
	int defaultFontColor;
	
	// Focus
	void setFocus(ofxTouchscreenElement* el);
	ofxTouchscreenElement* getFocus();
	
private:
	
	// Button
	ofxTouchscreenButton* createButton(float x, 
									   float y, 
									   string imageFileOn, 
									   string imageFileOff, 
									   int mapColor);
	
	ofxTouchscreenTextInput* createTextInput(float x, 
											 float y, 
											 string imageFileOn, 
											 string imageFileOff, 
											 int mapColor);
	
	// Mouse listeners
	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	
	// Hit map
	void setHitMapElement(ofxTouchscreenElement* el);
	
	// Events
	Poco::BasicEvent<ofxTouchscreenUI_Event> messageEvent;
	void dispatchEvent(ofxTouchscreenUI_Event message);
	ofxTouchscreenUI* sender;
	
	// Focus
	ofxTouchscreenElement* focus;
	
protected:
	
	// Elements
	vector<ofxTouchscreenElement* > elements;
	
	// Hit map
	ofImage hitMap;
	
	// Font
	vector<ofxTouchscreenUI_Font* > fonts;
	
};
