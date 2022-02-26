#include "LargeMenu.h"
#include "Mouse.h"
#include "Resources.h"
#include "Text.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// Constructor
LargeMenu::LargeMenu(int xx, int yy) {
	x = xx;
	y = yy;
	done = false;
	cursor = -1;
	chosen = -1;
	last_selected = 0;
}

// Update Loop
void LargeMenu::update() {

	// Track the mouse cursor
	int mx = getMouseX();
	int my = getMouseY();

	// Track which option the user is hovering over, if any
	cursor = -1;
	for (unsigned int i = 0; i < myChoices.size(); i++) {
		if (mx > x &&
			mx < x + 160 &&
			my > y + (20 + LARGE_MENU_SPACING_Y)*i &&
			my < y + (20 + LARGE_MENU_SPACING_Y)*i + 20) {
			cursor = i;
			last_selected = i;
		}
	}

	// Check if the user has made a choice. If so, set flag to done, and save the chosen value
	if (getMouseClicked() && cursor != -1) {
		done = true;
		chosen = cursor;
	}

}

// Render Loop
void LargeMenu::render() {

	// Draw the selection menu
	for (unsigned int i = 0; i < myChoices.size(); i++) {
		al_draw_bitmap_region(getResourceManager()->getImage("LARGE_BUTTON"), 0, 20 * (cursor == i), 160,
			20, x, y + (20 + LARGE_MENU_SPACING_Y)*i, 0);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", x+5,
			y + 7 + (20 + LARGE_MENU_SPACING_Y)*i, myChoices.at(i));
	}

}

// Add an option to the menu
void LargeMenu::addChoice(std::string s) { myChoices.push_back(s); }

// Get whether a selection has been clicked on
bool LargeMenu::isDone() { return done; }

// Get the value that was clicked on
int LargeMenu::getChosen() { return cursor; }

// Get the last value that was hovered over
int LargeMenu::getLastSelected() { return last_selected; }

// Reset the menu's values
void LargeMenu::reset() {
	done = false;
	cursor = -1;
	chosen = -1;
}