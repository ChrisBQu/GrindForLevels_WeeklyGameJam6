#include "UnitLevelBoxes.h"
#include "SaveData.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "SaveData.h"
#include "Text.h"
#include <vector>

using namespace std;

// Constants defining how the boxes look
const int UNIT_LEVEL_BOX_SPACING = 3;
const int UNIT_LEVEL_BOX_WIDTH = 55;
const int UNIT_LEVEL_BOX_HEIGHT = 23;

void renderUnitLevelBoxes(int x, int y) {

	// Cycle through the units and render the information
	vector<Unit*> units = { getLoadedSave()->unitOne, getLoadedSave()->unitTwo, getLoadedSave()->unitThree };
	for (int i = 0; i < 3; i++) {
		// Draw the bounding boxes
		al_draw_filled_rectangle(x + (UNIT_LEVEL_BOX_WIDTH+UNIT_LEVEL_BOX_SPACING)*i, y, 
			x + UNIT_LEVEL_BOX_WIDTH - 1 + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i,
			y + UNIT_LEVEL_BOX_HEIGHT - 1, al_map_rgba(200, 200, 200, 200));
		al_draw_rectangle(x + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i, y,
			x + UNIT_LEVEL_BOX_WIDTH + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i, y + UNIT_LEVEL_BOX_HEIGHT, al_map_rgb(0, 0, 0), 1);
		// Draw the unit icons and levels
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 16 * units.at(i)->CLASSTYPE, 0, 16, 16,
			x + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i, y + 2, 0);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", x + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i + 18,
			y + 2, units.at(i)->NAME);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", 
			x + (UNIT_LEVEL_BOX_WIDTH + UNIT_LEVEL_BOX_SPACING)*i + 24, y + 12, "Lv " + to_string(units.at(i)->LEVEL));

	}

}