#include "MapMenu.h"
#include "Text.h"
#include "Mouse.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// Variables controlling appearance of menu
const int DEFAULT_MENU_WIDTH = 60;
const int DEFAULT_MENU_HEIGHT = 5;

// Constructor
MapMenu::MapMenu(BattleMap *parent) {
	x = 0;
	y = 0;
	chosenval = -1;
	width = DEFAULT_MENU_WIDTH;
	height = DEFAULT_MENU_HEIGHT;
	visible = false;
	mapParent = parent;
}

// Add an option to the menu
void MapMenu::addOption(string s) {
	myOptions.push_back(s);
	height = myOptions.size() * 12;
}

// Update the menu
void MapMenu::update() {

	// Only update if the menu is actually open
	if (visible) {
		int mx = getMouseX();
		int my = getMouseY();
		cursor = -1;
		if (mx > x && mx < x + width && my > y && my < y + height) {
			if (myOptions.size() > 0) { cursor = (y + height - my) / (height / myOptions.size()); }
			cursor = myOptions.size() - cursor - 1;
			// Close menu when an option is picked
			if (getMouseClicked()) {
				chosenval = cursor;
				if (myOptions.size() > 0) { mapParent->processMenuClick(myOptions.at(cursor)); }
				resetMouseClicks();
				close();
			}
		}

		// Close menu on a right click
		if (getMouseRightClicked()) {
			mapParent->processMenuClick("RIGHTCLICK");
			chosenval = -1;
			resetMouseClicks();
			close();
		}
	}

}
// Render the menu 
void MapMenu::render() {

	if (visible) {
		al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255));
		if (cursor != -1 && myOptions.size() > 0) {
			al_draw_filled_rectangle(x, y + height/myOptions.size()*cursor, x + width,
				y + height / myOptions.size()*(cursor + 1), al_map_rgb(205, 205, 255));
		}
		al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(0, 0, 0), 1);
		for (unsigned int i = 0; i < myOptions.size(); i++) {
			drawText(al_map_rgb(0, 0, 0), "FONT2", x + 3, y + 3 + 11 * i, myOptions.at(i));
		}
	}


}

// Set position of the menu
void MapMenu::setPos(int xx, int yy) {
	x = xx;
	y = yy;
}

// Empty the menu
void MapMenu::clearOptions() { myOptions.clear(); }

// Getter for menu attributes
bool MapMenu::isOpen() { return visible; }

// Open and close the menu
void MapMenu::open() { visible = true; }
void MapMenu::close() { visible = false; }