#include "CombatLog.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "Dialogs.h"
#include "GameClass.h"
#include "Text.h"
#include <iostream>

using namespace std;

// How long it takes the log windows to open
const float OPEN_TIME_SECONDS = 0.1;

// Constructor
CombatLog::CombatLog(int xx, int yy, int ww, int hh) {
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	open_ticker = 0;
}

// Render loop

void CombatLog::render() {

	float maxTicks = OPEN_TIME_SECONDS * getGameClass()->getFPS();
	if (open_ticker < maxTicks) { open_ticker++; }
	float open_percent = (open_ticker / maxTicks);
	int CORNER_SIZE = 8;

	ALLEGRO_BITMAP *img = getResourceManager()->getImage("UI");
	// Fill background black
	al_draw_filled_rectangle(x, y + 2, x + width, y + 2 + (height - 4) * open_percent, al_map_rgb(0, 0, 0));

	// Draw the frame
	al_draw_scaled_bitmap(img, CORNER_SIZE, 0, 1, CORNER_SIZE, x + CORNER_SIZE, y, width - CORNER_SIZE * 2, CORNER_SIZE, 0);
	al_draw_scaled_bitmap(img, CORNER_SIZE, CORNER_SIZE, 1, CORNER_SIZE, x + CORNER_SIZE, y + height* open_percent - CORNER_SIZE, width - CORNER_SIZE * 2, CORNER_SIZE, 0);
	al_draw_scaled_bitmap(img, 0, CORNER_SIZE, CORNER_SIZE, 1, x, y + CORNER_SIZE, CORNER_SIZE, height* open_percent - CORNER_SIZE * 2, 0);
	al_draw_scaled_bitmap(img, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, 1, x + width - CORNER_SIZE, y + CORNER_SIZE, CORNER_SIZE, height* open_percent - CORNER_SIZE * 2, 0);

	// Draw corners
	al_draw_bitmap_region(img, 0, 0, CORNER_SIZE, CORNER_SIZE, x, y, 0);
	al_draw_bitmap_region(img, CORNER_SIZE, 0, CORNER_SIZE, CORNER_SIZE, x + width - CORNER_SIZE, y, 0);
	al_draw_bitmap_region(img, 0, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, x, y + height* open_percent - CORNER_SIZE, 0);
	al_draw_bitmap_region(img, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, x + width - CORNER_SIZE, y + height* open_percent - CORNER_SIZE, 0);

	// Draw text when window is fully opened
	if (open_percent > 0.99) {
		for (unsigned int i = 0; i < myText.size(); i++) {
			drawText(al_map_rgb(255, 255, 255), "FONT2", x + 10, y + 10 + 12*i, myText.at(i));
		}
	}

}

// Functions to add and clear text to and from the log
void CombatLog::addText(string s) { myText.push_back(s); }
void CombatLog::clearText() { myText.clear(); }