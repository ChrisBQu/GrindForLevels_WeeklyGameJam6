#include "ScreenHeader.h"
#include "Text.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// Constants defining where the header is placed
const int HEADER_X = 0;
const int HEADER_Y = 0;

void renderHeader(string text) {
	al_draw_bitmap(getResourceManager()->getImage("HEADER"), HEADER_X, HEADER_Y, 0);
	drawText(al_map_rgb(255, 255, 255), "FONT3", HEADER_X + 20, HEADER_Y + 12, text);
}