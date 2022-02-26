#include "DialogButton.h"
#include "Resources.h"
#include "Mouse.h"
#include "Text.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// Constructor
DialogButton::DialogButton(int xx, int yy, int size, string text) {
	x = xx;
	y = yy;
	mySize = size;
	myText = text;
	clicked = false;
	highlighted = false;

	// Calculate the width from the size
	if (mySize == SMALL_BUTTON) { width = 43; }
	else if (mySize == MEDIUM_BUTTON) { width = 78; }
	else { width = 160; }
}

// Update loop
void DialogButton::update() {

	// Track the mouse
	int mx = getMouseX();
	int my = getMouseY();

	// Check if the box is being hovered over
	highlighted = false;
	if (mx > x && mx < x + width && my > y && my < y + 20) { highlighted = true; }

	// Check if the button was clicked on
	if (highlighted && getMouseClicked()) { 
		clicked = true; 
		resetMouseClicks();
	}
}

// Render loop
void DialogButton::render() {

	// Get the appropriate background to render
	ALLEGRO_BITMAP *buttonbmp = NULL;
	if (mySize == SMALL_BUTTON) { buttonbmp = getResourceManager()->getImage("SMALL_BUTTON"); }
	else if (mySize == MEDIUM_BUTTON) { buttonbmp = getResourceManager()->getImage("MEDIUM_BUTTON"); }
	else { buttonbmp = getResourceManager()->getImage("LARGE_BUTTON"); }

	// Render the button and the text
	al_draw_bitmap_region(buttonbmp, 0, 20 * highlighted, width, 20, x, y, 0);
	drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", x + 5, y + 7, myText);
}

// Get if the button was clicked
bool DialogButton::isClicked() { return clicked; }

// Reset the button's clicked status
void DialogButton::reset() { clicked = false; }