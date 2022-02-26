#include "ScrollingBackground.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include "GameClass.h"

using namespace std;

// Constructor
ScrollingBG::ScrollingBG(string name, int image_size, bool scroll) {
	scrollval = 1;
	scrolling = scroll;
	size = image_size;
	image_name = name;
}

// Render loop
void ScrollingBG::render() {

	// Get how many tiles are needed to fill the screen, with some padding
	int min_needed_x = (getGameClass()->getScreenWidth() / size) + 2; 
	int min_needed_y = (getGameClass()->getScreenHeight() / size) + 2;

	// Fill in background with the image associated with the map
	// Only scroll if that option is turned on
	if (scrolling) {
		if (scrollval++ > 64) { scrollval = 1; }
	}
	ALLEGRO_BITMAP *backgroundimg = getResourceManager()->getImage(image_name);
	for (int i = 0; i < min_needed_x; i++) {
		for (int j = 0; j < min_needed_y; j++) {
			al_draw_bitmap(backgroundimg, 64 * i - scrollval , 64 * j - scrollval, 0);
		}
	}

}