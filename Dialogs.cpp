#include "Dialogs.h"
#include "Resources.h"
#include "Text.h"
#include <allegro5/allegro_primitives.h>
#include <stdarg.h>
#include <sstream>

// Constants to control how the gradient of the dialog boxes are colored (range: 9 - 246)
const int GRADIENT_RED_VAL = 220;
const int GRADIENT_GREEN_VAL = 220;
const int GRADIENT_BLUE_VAL = 220;

using namespace std;

// Constants to aid with drawing dialog box
const int CORNER_SIZE = 8;
const int LOAD_BAR_HEIGHT = 10;
const int LOAD_BAR_SIDE = 3;
const int LOAD_BAR_WIDTH = 10;

// Base DialogBox class to be inherited by more specialized versions
DialogBox::DialogBox(int xx, int yy, int ww, int hh) {
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	makeGradient();
}


// Create background gradient
// Works by taking a solid color, and modifying each line of pixels slightly to create the illusion of "texture"
void DialogBox::makeGradient() {
	ALLEGRO_BITMAP *switchBackTo = al_get_target_bitmap();
	myGradient = al_create_bitmap(width - CORNER_SIZE, height - CORNER_SIZE);
	al_set_target_bitmap(myGradient);
	for (int i = 0; i <= height - CORNER_SIZE; i++) {
		int randmod = rand() % 8;
		ALLEGRO_COLOR cur = al_map_rgb(GRADIENT_RED_VAL + randmod, GRADIENT_GREEN_VAL + randmod, GRADIENT_BLUE_VAL + randmod);
		al_draw_line(0, i, width - CORNER_SIZE, i, cur, 1);
	}
	al_set_target_bitmap(switchBackTo);
}

// Draws the box to the screen in three parts: gradient, frame, corners
void DialogBox::render() {
	ALLEGRO_BITMAP *img = getResourceManager()->getImage("UI");
	// Draw gradient
	al_draw_bitmap(myGradient, x + CORNER_SIZE / 2, y + CORNER_SIZE / 2, 0);

	// Draw the frame
	al_draw_scaled_bitmap(img, CORNER_SIZE, 0, 1, CORNER_SIZE, x + CORNER_SIZE, y, width - CORNER_SIZE * 2, CORNER_SIZE, 0);
	al_draw_scaled_bitmap(img, CORNER_SIZE, CORNER_SIZE, 1, CORNER_SIZE, x + CORNER_SIZE, y + height - CORNER_SIZE, width - CORNER_SIZE * 2, CORNER_SIZE, 0);
	al_draw_scaled_bitmap(img, 0, CORNER_SIZE, CORNER_SIZE, 1, x, y + CORNER_SIZE, CORNER_SIZE, height - CORNER_SIZE * 2, 0);
	al_draw_scaled_bitmap(img, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, 1, x + width - CORNER_SIZE, y + CORNER_SIZE, CORNER_SIZE, height - CORNER_SIZE * 2, 0);

	// Draw corners
	al_draw_bitmap_region(img, 0, 0, CORNER_SIZE, CORNER_SIZE, x, y, 0);
	al_draw_bitmap_region(img, CORNER_SIZE, 0, CORNER_SIZE, CORNER_SIZE, x + width - CORNER_SIZE, y, 0);
	al_draw_bitmap_region(img, 0, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, x, y + height - CORNER_SIZE, 0);
	al_draw_bitmap_region(img, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, x + width - CORNER_SIZE, y + height - CORNER_SIZE, 0);
}

// Draws a progress bar that looks like an ATB bar
void drawLoadBar(int x, int y, int width, float val, float maxval) {
	ALLEGRO_BITMAP *img = getResourceManager()->getImage("UI");
	al_draw_bitmap_region(img, 16, 0, LOAD_BAR_SIDE, LOAD_BAR_HEIGHT, x, y, 0);
	al_draw_bitmap_region(img, 16 + LOAD_BAR_SIDE + LOAD_BAR_WIDTH, 0, LOAD_BAR_SIDE, LOAD_BAR_HEIGHT, x + width, y, 0);
	al_draw_scaled_bitmap(img, 16 + LOAD_BAR_SIDE + 1, 0, 1, LOAD_BAR_HEIGHT, x + LOAD_BAR_SIDE, y, width - LOAD_BAR_SIDE, LOAD_BAR_HEIGHT, 0);
	al_draw_filled_rectangle(x + LOAD_BAR_SIDE, y + LOAD_BAR_SIDE, x + LOAD_BAR_SIDE +
		(width - LOAD_BAR_SIDE)*(val / maxval), y + LOAD_BAR_HEIGHT - LOAD_BAR_SIDE, al_map_rgb(245, 20, 45));
}

// Simple getters for dialog box attributes
int DialogBox::getX() { return x; }
int DialogBox::getY() { return y; }