#include "StageSelector.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "Mouse.h"
#include "Text.h"
#include "SaveData.h"

using namespace std;

// Constructor
StageSelector::StageSelector() {

	// Create the menu associated with stage selection
	myMenu = new LargeMenu(MAP_PREVIEW_X + MAP_PREVIEW_WIDTH + STAGE_SELECT_MENU_SPACING_X, MAP_PREVIEW_Y);

	// Add stage names to the menu as choices
	int unlocked = getLoadedSave()->unlocked_stages;
	if (unlocked >= 1) { myMenu->addChoice(getResourceManager()->getString("STAGE_NAME_1")); }
	if (unlocked >= 2) { myMenu->addChoice(getResourceManager()->getString("STAGE_NAME_2")); }
	if (unlocked >= 3) { myMenu->addChoice(getResourceManager()->getString("STAGE_NAME_3")); }

}

// Update loop
void StageSelector::update() {
	myMenu->update();
}

// Render loop
void StageSelector::render() {

	myMenu->render();

	// Render the stage preview
	int cursor = myMenu->getLastSelected();
	ALLEGRO_BITMAP *prevmap;
	if (cursor == 0) { prevmap = getResourceManager()->getImage("MAP_PREVIEW_01"); }
	else if (cursor == 1) { prevmap = getResourceManager()->getImage("MAP_PREVIEW_02"); }
	else { prevmap = getResourceManager()->getImage("MAP_PREVIEW_03"); }
	al_draw_bitmap(prevmap, MAP_PREVIEW_X, MAP_PREVIEW_Y, 0);
	al_draw_rectangle(MAP_PREVIEW_X, MAP_PREVIEW_Y, MAP_PREVIEW_X + MAP_PREVIEW_WIDTH,
		MAP_PREVIEW_Y + MAP_PREVIEW_HEIGHT, al_map_rgb(0, 0, 0), 1);

}

// Get a pointer to the selector's menu
LargeMenu *StageSelector::getMenu() { return myMenu; }
