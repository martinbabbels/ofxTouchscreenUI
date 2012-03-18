#include "ofxTouchScreenUI.h"

/********************************************************************************
 * ofxTouchscreenElement
 *
 ********************************************************************************/

// Constructor
ofxTouchscreenElement::ofxTouchscreenElement():
width(0),
height(0),
fontColor(0x000000),
mapColor(0x000000),
isMouseDown(false),
hasFocus(false),
useFocus(true)
{
	
}

// Set the font
void ofxTouchscreenElement::setFont(string newFontName) {
	fontName = newFontName;
}

void ofxTouchscreenElement::setFont(string newFontName, int newFontColor) {
	fontName = newFontName;
	fontColor = newFontColor;
}

// Setup
void ofxTouchscreenElement::setup() {
}

// Draw
void ofxTouchscreenElement::draw() {
	
}

/********************************************************************************
 * ofxTouchscreenLabel
 *
 ********************************************************************************/
ofxTouchscreenLabel::ofxTouchscreenLabel():
text("Label")
{
}

void ofxTouchscreenLabel::draw() {
	// Get the font
	ofxTouchscreenUI_Font* font = ui->getFont(fontName);
	
	// Set the font color
	ofSetHexColor(fontColor);
	
	// Draw text
	font->font.drawString(text, x, y);
}

void ofxTouchscreenLabel::setText(string labelText) {
	
	text = labelText;
	
	ofxTouchscreenUI_Font* font = ui->getFont(fontName);
	ofRectangle txt_box = font->font.getStringBoundingBox(text, 0, 0);
	
	width = txt_box.width;
	height = txt_box.height;
	
}

string ofxTouchscreenLabel::getText() {
	return text;
}

/********************************************************************************
 * ofxTouchscreenTextInput
 *
 ********************************************************************************/

// Constructor
ofxTouchscreenTextInput::ofxTouchscreenTextInput():
text(""),
imageFileOn(""),
imageFileOff(""),
padding(50)
{
	elementType = OFX_TSUI_TEXT_INPUT;
}

// Draw
void ofxTouchscreenTextInput::draw() {
	
	ofSetHexColor(0xFFFFFF);
	
	// Draw the correct image
	if(isMouseDown || hasFocus) {
		imageOn.draw(x, y);
	} else {
		imageOff.draw(x, y);
	}
	
	// Draw the text
	if(!text.empty()) {
		
		// Get the font
		ofxTouchscreenUI_Font* font = ui->getFont(fontName);
		
		// Set the font color
		ofSetHexColor(fontColor);
		
		// Get the text dimensions
		string text_val = text;
		ofRectangle sc_box = font->font.getStringBoundingBox(text_val,0,0);
		int text_w = sc_box.width + (2*padding);
		
		// Truncate
		if(text_w > imageOff.width) {
			text_val = text.substr(text.size()-10);
			sc_box = font->font.getStringBoundingBox(text_val,0,0);
		}
		
		// Draw text
		font->font.drawString(text_val, x+padding, y+padding);
		
	}
}

// Binds a keyboard to the input
void ofxTouchscreenTextInput::bindKeyboard(ofxTouchscreenKeyboard* keyboardEl) {
	// Bind the keyboard
	keyboard = keyboardEl;
	ui->addListener(this);
}

void ofxTouchscreenTextInput::onTouchscreenEvent(ofxTouchscreenUI_Event &e) {
	if(!hasFocus) return;
	
	// Get the ket
	ofxTouchscreenKeyboardKey *key = static_cast<ofxTouchscreenKeyboardKey*>(e.event.element);
	
	// Check if the event is fired by the
	// keybaord that is binded to the textinput
	if(e.event.target == keyboard) {
		if(key->type == OFX_TSUI_KEY_BACKSPACE) {
			text = text.substr(0, text.size()-1);
		} else {
			text.append(e.event.elementValue);
		}
	}
}

bool ofxTouchscreenTextInput::isTransparantPixel(int pixX, int pixY) {
	ofPixels pix = imageOff.getPixelsRef();
	ofColor c = pix.getColor(pixX, pixY);
	
	return (c.a == 0);
}

// Setup
void ofxTouchscreenTextInput::setup() {
	// Load images
	imageOn.loadImage(imageFileOn);
	imageOff.loadImage(imageFileOff);
	
	// Set the dimensions
	width = imageOff.getWidth();
	height = imageOff.getHeight();
}

/********************************************************************************
 * ofxTouchscreenButton
 *
 ********************************************************************************/

// Constructor
ofxTouchscreenButton::ofxTouchscreenButton():
	text(""),
	imageFileOn(""),
	imageFileOff("")
{
	elementType = OFX_TSUI_BUTTON;
}

// Draw
void ofxTouchscreenButton::draw() {
	
	ofSetHexColor(0xFFFFFF);
	if(isMouseDown) {
		imageOn.draw(x, y);
	} else {
		imageOff.draw(x, y);
	}
	
	if(!text.empty()) {
		
		ofxTouchscreenUI_Font* font = ui->getFont(fontName);
		
		ofSetHexColor(fontColor);
		
		ofRectangle sc_box = font->font.getStringBoundingBox(text, 0, 0);
		
		int sc_x = x + (imageOff.width/2 - sc_box.width/2);
		int sc_y = y + (imageOff.height/2 + sc_box.height/2);
		
		font->font.drawString(text, sc_x, sc_y);

	}
}

bool ofxTouchscreenButton::isTransparantPixel(int pixX, int pixY) {
	ofPixels pix = imageOff.getPixelsRef();
	ofColor c = pix.getColor(pixX, pixY);
	
	return (c.a == 0);
}

// Setup
void ofxTouchscreenButton::setup() {
	imageOn.loadImage(imageFileOn);
	imageOff.loadImage(imageFileOff);
	
	width = imageOff.getWidth();
	height = imageOff.getHeight();
}

/********************************************************************************
 * ofxTouchscreenKeyboard
 *
 ********************************************************************************/

// Contructor
ofxTouchscreenKeyboard::ofxTouchscreenKeyboard() {
	defaultImageFileOn = "key_on.png";
	defaultImageFileOff = "key_off.png";
	
	rowSpacing = 5;
	keySpacing = 5;
	
	x = 0;
	y = 0;
	
	elementType = OFX_TSUI_KEYBOARD;
	alignment = OFX_TSUI_ALIGN_CENTER;
}

// Setup
void ofxTouchscreenKeyboard::setup() {
}

// Draw
void ofxTouchscreenKeyboard::draw() {
	
	int row,key;
	for(row=0; row<rows.size(); ++row) {
		for(key=0; key<rows[row]->keys.size(); ++key) {
			rows[row]->keys[key]->draw();
		}
	}
}

// Set the default key images
void ofxTouchscreenKeyboard::setKeyImages(string imageFileOn, string imageFileOff) {
	defaultImageFileOn = imageFileOn;
	defaultImageFileOff = imageFileOff;
}

// Adds a row of keys to the keyboard
ofxTouchscreenKeyboardRow* ofxTouchscreenKeyboard::addKeys(string newKeys) {
	
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	
	int i;
	float ypos = rows.size();
	
	for(i=0; i<newKeys.size(); ++i) {
		
		ofxTouchscreenKeyboardKey *key = createKey(charToString(newKeys.at(i)));
		key->x = (i * key->width) + x + (i*keySpacing);
		key->y = (ypos * key->height) + y + (ypos*rowSpacing);
		
		row->keys.push_back(key);
	}
	
	rows.push_back(row);
	
	update();
	
	return row;
}

// Adds a key
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addKey(char newKey) {
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	ofxTouchscreenKeyboardKey *key = createKey(&newKey);
	
	key->x = getRowX(rows.size()-1) + x;
	key->y = getRowY(rows.size()-1) + y;
	
	row->keys.push_back(key);
	rows.push_back(row);
	
	return key;
}

// Adds a key to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addKeyToRow(char newKey, int row) {
	
	ofxTouchscreenKeyboardKey *key = createKey(charToString(newKey));
	key->x = getRowX(row) + x;
	key->y = getRowY(row) + y;
	
	rows[row]->keys.push_back(key);
	update();
	
	return key;
}

// Adds a custom button
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButton(int type,
															 string imageFileOn, 
															 string imageFileOff,
															 int mapColor) 
{
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	ofxTouchscreenKeyboardKey *button = createButton(x, 
													 getRowY(rows.size()-1)+y,
													 imageFileOn, 
													 imageFileOff,
													 mapColor);

	button->y += button->height;
	button->type = type;
	row->keys.push_back(button);
	rows.push_back(row);
	
	update();
	
	return button;
}

// Adds a custom button to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButton(string imageFileOn, 
															 string imageFileOff, 
															 int mapColor) 
{
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(rows.size()-1)+x, 
													 getRowY(rows.size()-1)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	
	row->keys.push_back(button);
	rows.push_back(row);
	
	update();
	
	return button;
}

ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButton(int type,
															 string imageFileOn, 
															 string imageFileOff, 
															 int mapColor, 
															 string text, 
															 int fontColor)
{
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(rows.size()-1)+x, 
													 getRowY(rows.size()-1)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	
	button->text		= text;
	button->fontColor	= fontColor;
	button->type		= type;
	
	row->keys.push_back(button);
	rows.push_back(row);
	
	update();
	
	return button;
}

ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButton(string imageFileOn, 
															 string imageFileOff, 
															 int mapColor, 
															 string text, 
															 int fontColor)
{
	ofxTouchscreenKeyboardRow *row = new ofxTouchscreenKeyboardRow();
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(rows.size()-1)+x, 
													 getRowY(rows.size()-1)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	
	button->text		= text;
	button->fontColor	= fontColor;
	
	row->keys.push_back(button);
	rows.push_back(row);
	
	update();
	
	return button;
}

// Adds a custom button to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButtonToRow(int type,
																  string imageFileOn, 
																  string imageFileOff, 
																  int mapColor, 
																  int row) {
	
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(row)+x, 
													 getRowY(row)+y, 
													 imageFileOn, 
													 imageFileOff,
													 mapColor);
	button->type = type;
	
	rows[row]->keys.push_back(button);
	update();
	
	return button;
}

// Adds a custom button to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButtonToRow(int type,
																  string imageFileOn, 
																  string imageFileOff, 
																  int mapColor, 
																  string text, 
																  int fontColor, 
																  int row) 
{
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(row)+x, 
													 getRowY(row)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	button->type = type;
	button->fontColor = fontColor;
	button->text = text;
	
	rows[row]->keys.push_back(button);
	update();
	
	return button;
}

// Adds a custom button to a given row
void ofxTouchscreenKeyboard::addButtonToRow(ofxTouchscreenKeyboardKey* button, int row) {
	rows[row]->keys.push_back(button);
	update();
}

// Adds a custom button to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButtonToRow(string imageFileOn, 
																  string imageFileOff, 
																  int mapColor, 
																  int row) 
{
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(row)+x, 
													 getRowY(row)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);

	rows[row]->keys.push_back(button);
	update();
	
	return button;
}

// Adds a custom button to a given row
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::addButtonToRow(string imageFileOn, 
																  string imageFileOff, 
																  int mapColor, 
																  string text, 
																  int fontColor, 
																  int row) 
{
	ofxTouchscreenKeyboardKey *button = createButton(
													 getRowX(row)+x, 
													 getRowY(row)+y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);

	button->fontColor = fontColor;
	button->text = text;
	
	update();
	
	return button;
}

// Create a key
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::createKey(string keyChar) {
	
	ofxTouchscreenKeyboardKey *key = new ofxTouchscreenKeyboardKey();
	
	key->ui = ui;
	key->text = keyChar;
	
	float v = (float)keyChar.at(0);
	
	key->mapColor.set(v, v, v, 255.0);
	key->imageFileOff = defaultImageFileOff;
	key->imageFileOn  = defaultImageFileOn;
	key->setFont(fontName, fontColor);
	key->useFocus = false;
	
	key->setup();
	
	return key;
}

// Create a button
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::createButton(float x, 
																float y, 
																string imageFileOn, 
																string imageFileOff, 
																int mapColor) 
{
	
	ofxTouchscreenKeyboardKey* button = new ofxTouchscreenKeyboardKey();
	
	button->type = OFX_TSUI_KEY_BUTTON;
	button->ui = ui;
	button->imageFileOn  = imageFileOn;
	button->imageFileOff = imageFileOff;
	button->x = x;
	button->y = y;
	button->mapColor.setHex(mapColor, 255.0);
	button->setFont(fontName, fontColor);
	button->useFocus = false;
	
	button->setup();
	
	return button;
}

// Returns the key corresponding to the given color
ofxTouchscreenKeyboardKey* ofxTouchscreenKeyboard::getKey(ofColor color) {
	
	int row,key;
	for(row=0; row<rows.size(); ++row) {
		for(key=0; key<rows[row]->keys.size(); ++key) {
			if(rows[row]->keys[key]->mapColor.getHex() == color.getHex())
				return rows[row]->keys[key];
		}
	}
	
	return NULL;
}

// Returns the row width
int ofxTouchscreenKeyboard::getRowX(int row) {
	
	int row_width = 0;
	int key;
	
	for(key=0; key<rows[row]->keys.size(); ++key) {
		row_width += rows[row]->keys[key]->width + keySpacing;
	}
	
	return row_width;
}

// Returns the row height
int ofxTouchscreenKeyboard::getRowY(int row) {
	
	int total_height = 0;
	int row_height = 0;
	int r,k;
	
	for(r=0; r<row; ++r) {
		for(k=0; k<rows[r]->keys.size(); ++k) {
			if(rows[r]->keys[k]->height>row_height)
				row_height = rows[r]->keys[k]->height + rowSpacing;
		}
		
		total_height += row_height;
	}
	
	return total_height;
}

// Update
void ofxTouchscreenKeyboard::update() {
	float w = 0;
	int i;
	for(i=0;i<rows.size(); ++i) {
		int row_w = getRowX(i);
		if(row_w>w) {
			w = row_w;
		}
	}
	
	width = w;
	height = getRowY(rows.size());
	
	ui->updateHitMap();
}

// Reset the keys
void ofxTouchscreenKeyboard::mouseOut() {
	int row,key;
	for(row=0; row<rows.size(); ++row) {
		for(key=0; key<rows[row]->keys.size(); ++key) {
			rows[row]->keys[key]->mouseOut();
		}
	}
}

void ofxTouchscreenKeyboard::focusOut() {
	int row,key;
	for(row=0; row<rows.size(); ++row) {
		for(key=0; key<rows[row]->keys.size(); ++key) {
			rows[row]->keys[key]->focusOut();
		}
	}
}

// Char to string helper
string ofxTouchscreenKeyboard::charToString(char aChar) {
	string str;
	str.push_back(aChar);
	
	return str;
}

/********************************************************************************
 * ofxTouchscreenUI
 *
 ********************************************************************************/

// Constructor
ofxTouchscreenUI::ofxTouchscreenUI() {
	ofAddListener(ofEvents.mousePressed,this,&ofxTouchscreenUI::mousePressed);
	ofAddListener(ofEvents.mouseReleased,this,&ofxTouchscreenUI::mouseReleased);
}

// Mouse released listener
void ofxTouchscreenUI::mouseReleased(ofMouseEventArgs &e) {
	int i;
	if(focus==NULL) {
		for(i=0; i<elements.size(); ++i) {
			elements[i]->focusOut();
		}
	} else {
		for(i=0; i<elements.size(); ++i) {
			elements[i]->mouseOut();
		}
	}
	
}

// Mouse pressed listener
void ofxTouchscreenUI::mousePressed(ofMouseEventArgs &e) {

	ofColor hit_color = getHitMapColor(e.x, e.y);
	ofxTouchscreenElement* el = getHitMapElement(hit_color);
	
	setFocus(el);
	
	if(el==NULL) {
		return;
	}

	if(el->useFocus) {
		el->focusIn();
	}
	
	el->mouseIn();
}

// Set focus
void ofxTouchscreenUI::setFocus(ofxTouchscreenElement* el) {
	focus = el;
}

// Get focus
ofxTouchscreenElement* ofxTouchscreenUI::getFocus() {
	return focus;
}

// Add a button with an image
void ofxTouchscreenUI::addButton(ofxTouchscreenButton* button) {
	elements.push_back(button);
}

// Add a button with an image
ofxTouchscreenButton* ofxTouchscreenUI::addButton(float x, 
								 float y, 
								 string imageFileOn, 
								 string imageFileOff, 
								 int mapColor) {
	
	ofxTouchscreenButton* button = createButton(x, 
				 y, 
				 imageFileOn, 
				 imageFileOff, 
				 mapColor);
	
	return button;
}

// Add a button with an image and text
ofxTouchscreenButton* ofxTouchscreenUI::addButton(float x, 
								 float y, 
								 string imageFileOn, 
								 string imageFileOff, 
								 int mapColor, 
								 string text, 
								 int fontColor) {
	
	ofxTouchscreenButton* button = createButton(x, 
												y, 
												imageFileOn, 
												imageFileOff, 
												mapColor);

	button->text		= text;
	button->fontColor	= fontColor;	
	
	return button;
	
}

// Create a button
ofxTouchscreenButton* ofxTouchscreenUI::createButton(float x, 
													 float y, 
													 string imageFileOn, 
													 string imageFileOff, 
													 int mapColor) {
	
	ofxTouchscreenButton* button = new ofxTouchscreenButton();
	
	button->ui = this;
	button->imageFileOn  = imageFileOn;
	button->imageFileOff = imageFileOff;
	button->x = x;
	button->y = y;
	button->mapColor.setHex(mapColor, 255.0);
	
	button->setFont(defaultFontName, defaultFontColor);
	
	button->setup();
	
	elements.push_back(button);
	
	updateHitMap();
	
	return button;
}

// Add a text input with an image
void ofxTouchscreenUI::addTextInput(ofxTouchscreenTextInput* input) {
	elements.push_back(input);
}

// Add a text input with an image
ofxTouchscreenTextInput* ofxTouchscreenUI::addTextInput(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor) {
	
	ofxTouchscreenTextInput* input = createTextInput(x, 
													 y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	return input;
}

// Add a text input with an image and text
ofxTouchscreenTextInput* ofxTouchscreenUI::addTextInput(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor, 
									string text, 
									int fontColor) {
	
	ofxTouchscreenTextInput* input = createTextInput(x, 
													 y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	
	input->text		 = text;
	input->fontColor = fontColor;	
	
	return input;
	
}

// Add a text input with an image and text
ofxTouchscreenTextInput* ofxTouchscreenUI::addTextInput(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor, 
									string text, 
									int fontColor,
									ofxTouchscreenKeyboard* keyboard) {
	
	ofxTouchscreenTextInput* input = createTextInput(x, 
													 y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	input->text		 = text;
	input->fontColor = fontColor;
	input->bindKeyboard(keyboard);
	
	return input;
	
}

// Add a text input with an image and text
ofxTouchscreenTextInput* ofxTouchscreenUI::addTextInput(float x, 
									float y, 
									string imageFileOn, 
									string imageFileOff, 
									int mapColor,
									ofxTouchscreenKeyboard* keyboard) {
	
	ofxTouchscreenTextInput* input = createTextInput(x, 
													 y, 
													 imageFileOn, 
													 imageFileOff, 
													 mapColor);
	

	input->bindKeyboard(keyboard);
	
	return input;
}

// Create a text input
ofxTouchscreenTextInput* ofxTouchscreenUI::createTextInput(float x, 
														float y, 
														string imageFileOn, 
														string imageFileOff, 
														int mapColor) {
	
	ofxTouchscreenTextInput* input = new ofxTouchscreenTextInput();
	
	input->ui = this;
	input->imageFileOn  = imageFileOn;
	input->imageFileOff = imageFileOff;
	input->x = x;
	input->y = y;
	input->mapColor.setHex(mapColor, 255.0);
	
	input->setFont(defaultFontName, defaultFontColor);
	
	input->setup();
	
	elements.push_back(input);
	
	updateHitMap();
	
	return input;
}

// Add a keyboard
ofxTouchscreenKeyboard* ofxTouchscreenUI::addKeyboard(float xPos, float yPos) {
	ofxTouchscreenKeyboard* keyboard = new ofxTouchscreenKeyboard();
	
	keyboard->ui = this;
	keyboard->x = xPos;
	keyboard->y = yPos;
	
	keyboard->setFont(defaultFontName, defaultFontColor);
	
	elements.push_back(keyboard);
	
	updateHitMap();
	
	return keyboard;
}

// Add a label
ofxTouchscreenLabel* ofxTouchscreenUI::addLabel(float xPos, float yPos, string text) {
	ofxTouchscreenLabel* label = new ofxTouchscreenLabel();
	
	label->ui = this;
	label->x = xPos;
	label->y = yPos;
	label->setFont(defaultFontName, defaultFontColor);
	label->setText(text);
	
	elements.push_back(label);
	
	
	updateHitMap();
	
	return label;
}

// Draw the UI
void ofxTouchscreenUI::draw() {
	ofSetHexColor(0xFFFFFF);
	ofEnableAlphaBlending();
	
	int i;
	for(i=0; i<elements.size(); ++i) {
		elements[i]->draw();
	}
	
	ofDisableAlphaBlending();
	ofSetHexColor(0xFFFFFF);
}

// Draw the hit map
void ofxTouchscreenUI::drawHitMap() {
	ofEnableAlphaBlending();
	hitMap.draw(0, 0);	
	ofDisableAlphaBlending();
}

// Update the hit map
void ofxTouchscreenUI::updateHitMap() {
	
	float w = ofGetWidth();
	float h = ofGetHeight();
	
	hitMap.clear();
	hitMap.allocate(w, h, OF_IMAGE_COLOR);
	
	int i;
	for(i=0; i<elements.size(); ++i) {
		
		// Update button
		if(elements[i]->elementType==OFX_TSUI_BUTTON) {
			ofxTouchscreenButton* button = static_cast<ofxTouchscreenButton*>(elements[i]);
			setHitMapElement(button);
		}
		
		// Update text input
		if(elements[i]->elementType==OFX_TSUI_TEXT_INPUT) {
			ofxTouchscreenTextInput* input = static_cast<ofxTouchscreenTextInput*>(elements[i]);
			setHitMapElement(input);
		}
		
		// Update keyboard
		if(elements[i]->elementType==OFX_TSUI_KEYBOARD) {
			ofxTouchscreenKeyboard* keyboard = static_cast<ofxTouchscreenKeyboard*>(elements[i]);
			int row, key;
			for(row=0; row<keyboard->rows.size(); ++row) {
				
				for(key=0; key<keyboard->rows[row]->keys.size(); ++key) {
					ofxTouchscreenButton* button = static_cast<ofxTouchscreenButton*>(keyboard->rows[row]->keys[key]);
					setHitMapElement(button);
				}
			}
		}
	}
}

// Add an element to the hit map
void ofxTouchscreenUI::setHitMapElement(ofxTouchscreenElement* el) {
	float w = el->width;
	float h = el->height;
	
	int xpos,ypos;
	for(xpos=0; xpos<w; ++xpos) {
		for(ypos=0; ypos<h; ++ypos) {
			if(el->x <= hitMap.getWidth() && el->y <= hitMap.getHeight() &&
			   !el->isTransparantPixel(xpos, ypos)) {
				hitMap.setColor(el->x + xpos, 
								el->y + ypos, 
								el->mapColor);
			}
		}
	}
}

// Returns the color clicked in the hit map
ofColor ofxTouchscreenUI::getHitMapColor(int xPos, int yPos) {
	ofColor hit_color = hitMap.getColor(xPos, yPos);
	return hit_color;
}

// Return the element corresponding 
// to the given hit map color
ofxTouchscreenElement* ofxTouchscreenUI::getHitMapElement(ofColor color) {
	int i;
	
	ofxTouchscreenUI_EventParams p;
	p.eventType = OFX_TSUI_EVENT_CLICK;
	
	ofxTouchscreenElement* el;
	
	for(i=0; i<elements.size(); ++i) {
		
		// Button
		if(elements[i]->elementType==OFX_TSUI_BUTTON) {
			
			if(color.getHex() == elements[i]->mapColor.getHex()) {
				ofxTouchscreenButton* button = static_cast<ofxTouchscreenButton*>(elements[i]);
				
				p.element = button;
				p.target = button;
				p.elementValue = button->text;
				p.elementType = OFX_TSUI_BUTTON;
				
				el = button;
			}
		}
		
		// Text input
		if(elements[i]->elementType==OFX_TSUI_TEXT_INPUT) {
			
			if(color.getHex() == elements[i]->mapColor.getHex()) {
				ofxTouchscreenTextInput *input = static_cast<ofxTouchscreenTextInput*>(elements[i]);
				
				p.element = input;
				p.target = input;
				p.elementValue = input->text;
				p.elementType = OFX_TSUI_TEXT_INPUT;
				
				el = input;
			}
		}
	
		// Keyboard
		if(elements[i]->elementType==OFX_TSUI_KEYBOARD) {
			
			ofxTouchscreenKeyboard* keyboard = static_cast<ofxTouchscreenKeyboard*>(elements[i]);
			ofxTouchscreenKeyboardKey* key = keyboard->getKey(color);
			
			if(key) {
				
				p.target = keyboard;
				p.element = key;
				p.elementType = OFX_TSUI_KEYBOARD;
				p.elementValue = key->text;
			}
			
			el = key;
		}
	}
	
	if(el!=NULL) {
		
		p.elementId = el->mapColor.getHex();
		
		ofxTouchscreenUI_Event e = ofxTouchscreenUI_Event(p);
		dispatchEvent(e);
		
		return el;
	}
	
	return NULL;
}

// Returns the element corresponding to the given color
ofxTouchscreenElement* ofxTouchscreenUI::getElement(ofColor color) {
	
	ofxTouchscreenElement* el;
	int i;
	for(i=0; i<elements.size(); ++i) {
		if(color.getHex() == elements[i]->mapColor.getHex()) {
			el = elements[i];
		}
	}
	
	return el;
}

// Add a font
void ofxTouchscreenUI::addFont(string fontName, string fontFile, int size) {
	ofxTouchscreenUI_Font *font = new ofxTouchscreenUI_Font();
	
	font->fontFile = fontFile;
	font->fontName = fontName;
	font->fontSize = size;
	font->font.loadFont(fontFile, size);
	
	fonts.push_back(font);
}

// Set the default UI font
void ofxTouchscreenUI::setDefaultFont(string fontName, int fontColor) {
	defaultFontName = fontName;
	defaultFontColor = fontColor;
}

// Returns a UI font
ofxTouchscreenUI_Font* ofxTouchscreenUI::getFont(string fontName) {
	int i;
	for(i=0; i<fonts.size(); ++i) {
		if(fonts[i]->fontName == fontName) {
			return fonts[i];
		}
	}
	
	return NULL;
}

// Add event listener
void ofxTouchscreenUI::addListener(ofxTouchscreenListener * listener) {
	messageEvent += Poco::Delegate<ofxTouchscreenListener, ofxTouchscreenUI_Event>(listener,&ofxTouchscreenListener::onTouchscreenEvent);
}

// Remove event listener
void ofxTouchscreenUI::removeListener(ofxTouchscreenListener * listener) {
	messageEvent += Poco::Delegate<ofxTouchscreenListener, ofxTouchscreenUI_Event>(listener,&ofxTouchscreenListener::onTouchscreenEvent);
}

// Dispatch event
void ofxTouchscreenUI::dispatchEvent(ofxTouchscreenUI_Event message) {
	messageEvent.notify(sender, message);
}
