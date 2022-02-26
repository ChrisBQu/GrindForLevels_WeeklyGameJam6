#include "MapBattleState.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Sound.h"
#include "Unit.h"
#include "Text.h"
#include <string>
#include <iostream>
#include "StateMachine.h"
#include "ScreenHeader.h"
#include "Stages.h"

using namespace std;

int map_number = 0;
int map_fader_state;
int map_transition_state;

// Constants for how the screen is laid out
const int UNIT_PREVIEW_DIALOG_X = 90;
const int UNIT_PREVIEW_DIALOG_Y = 34;
const int UNIT_PREVIEW_DIALOG_WIDTH = 160;
const int UNIT_PREVIEW_DIALOG_HEIGHT = 77;
const int UNIT_PREVIEW_DIALOG_SPACING = 4;
const int MAP_SCREEN_COIN_COUNTER_X = 201;
const int MAP_SCREEN_COIN_COUNTER_Y = 201;

// Constants to control the timing of the screen fading effect (in seconds)
const float FADE_TO_COMBAT_TIME = 0.25;
const float FADE_IN_TIME_MAP = 1;

// Constructor for state
MapBattleState::MapBattleState() {

	// Create the map and build the stage
	myMap = new BattleMap();

	// Create the unit preview boxes
	unitPreviewBox = new DialogBox(UNIT_PREVIEW_DIALOG_X, UNIT_PREVIEW_DIALOG_Y, UNIT_PREVIEW_DIALOG_WIDTH, UNIT_PREVIEW_DIALOG_HEIGHT);
	secondUnitPreviewBox = new DialogBox(UNIT_PREVIEW_DIALOG_X, UNIT_PREVIEW_DIALOG_Y + UNIT_PREVIEW_DIALOG_HEIGHT +
		UNIT_PREVIEW_DIALOG_SPACING, UNIT_PREVIEW_DIALOG_WIDTH, UNIT_PREVIEW_DIALOG_HEIGHT);

}

// Executes when entering this state
void MapBattleState::enter() {

	// Fade in from black
	ScreenFader newF;
	myFader = newF;
	map_fader_state = 0;
	myFader.fadeFromBlack(FADE_IN_TIME_MAP);

	// Load graphical resources into memory
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "MAP_SCREEN_BG");
	getResourceManager()->loadImage("Resources/Interface/Coin.png", "COIN");
	getResourceManager()->loadImage("Resources/Interface/Poof.png", "POOF");

	// Create a scrolling background and a coin counter
	myBG = new ScrollingBG("MAP_SCREEN_BG", 64, true);
	myCoinCounter = new CoinCounter(MAP_SCREEN_COIN_COUNTER_X, MAP_SCREEN_COIN_COUNTER_Y);

	// Begin playing music
	getSoundPlayer()->playMusic("Resources/Sound/Song1.ogg");

	// Build the stage if one does not yet exist
	if (myMap->getControlState() == UNLOADED_BATTLE) {
		if (map_number == 1) { buildStageOne(myMap); }
		if (map_number == 2) { buildStageTwo(myMap); }
		if (map_number == 3) { buildStageThree(myMap); }
		myMap->setControlState(SELECTION);
	}

}

// Executes when exiting this state
void MapBattleState::exit() {

	// Unload graphical resoruces from memory
	getResourceManager()->unloadImage("MAP_SCREEN_BG");
	getResourceManager()->unloadImage("COIN");
	getResourceManager()->unloadImage("POOF");

	// Free the scrolling background and coin counters from memory
	if (myBG) { delete myBG; }
	if (myCoinCounter) { delete myCoinCounter; }

}

// Update loop for state
void MapBattleState::update() {
	myMap->update();
}

// Render loop for state
void MapBattleState::render() {

	// Render the background
	myBG->render();

	// Render the mission header
	renderHeader(myMap->getHeaderText());

	// Render unit preview boxes
	unitPreviewBox->render();

	// Render the coin counter
	myCoinCounter->render();

	// Render date for the selected unit if there is one
	if (myMap->getSelectedUnit() == NULL) { 
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0,0,0), "FONT2",
		unitPreviewBox->getX() + 12, unitPreviewBox->getY() + 10, "No unit selected."); 
	}
	else {
		int dx = unitPreviewBox->getX();
		int dy = unitPreviewBox->getY();
		Unit *selu = myMap->getSelectedUnit();

		// Draw selected unit icon
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 0, 16 * selu->enemy_unit, 16, 16, dx + 8, dy + 6, 0);

		// Draw selected name, unit name, level, and stats
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 10, selu->NAME);
		string linetwo = + " " + UNIT_CLASS_NAMES[selu->CLASSTYPE] + " Lv " + to_string(selu->LEVEL);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 23, linetwo);
		string linethree = "STR " + to_string(selu->STR) + "       DEF " + to_string(selu->DEF) + "       INT " + to_string(selu->INT);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0,0,0), "FONT2", dx + 10, dy + 40, linethree);
		string linefour = "SPD " + to_string(selu->SPD) + "      MND " + to_string(selu->MND) + "       MOV " + to_string(selu->MOV);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 10, dy + 53, linefour);

		// Draw HP and MP bars
		drawLoadBar(dx + 110, dy + 11, 32, selu->HP, selu->MAXHP);
		drawLoadBar(dx + 110, dy + 23, 32, selu->MP, selu->MAXMP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 98, dy + 12, "HP");
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 98, dy + 24, "MP");
		drawShadowedText(al_map_rgb(255,255,255), al_map_rgb(0,0,0), "FONT2", dx + 115, dy + 9, to_string(selu->HP));
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 115, dy + 21, to_string(selu->MP));
	}

	// Render date for the second selected unit if there is one
	if (myMap->getSecondSelectedUnit() != NULL && myMap->getSecondSelectedUnit() != myMap->getSelectedUnit()) {

		secondUnitPreviewBox->render();

		int dx = secondUnitPreviewBox->getX();
		int dy = secondUnitPreviewBox->getY();
		Unit *selu = myMap->getSecondSelectedUnit();

		// Draw selected unit icon
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 0, 16 * selu->enemy_unit, 16, 16, dx + 8, dy + 6, 0);

		// Draw selected name, unit name, level, and stats
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 10, selu->NAME);
		string linetwo = +" " + UNIT_CLASS_NAMES[selu->CLASSTYPE] + " Lv " + to_string(selu->LEVEL);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 23, linetwo);
		string linethree = "STR " + to_string(selu->STR) + "       DEF " + to_string(selu->DEF) + "       INT " + to_string(selu->INT);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 10, dy + 40, linethree);
		string linefour = "SPD " + to_string(selu->SPD) + "      MND " + to_string(selu->MND) + "       MOV " + to_string(selu->MOV);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 10, dy + 53, linefour);

		// Draw HP and MP bars
		drawLoadBar(dx + 110, dy + 11, 32, selu->HP, selu->MAXHP);
		drawLoadBar(dx + 110, dy + 23, 32, selu->MP, selu->MAXMP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 98, dy + 12, "HP");
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 98, dy + 24, "MP");
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 115, dy + 9, to_string(selu->HP));
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 115, dy + 21, to_string(selu->MP));

	}

	// Handle transition to the combat state
	if (map_fader_state == 0 && myMap->getControlState() == FADE_TO_BATTLE) {
		myFader.fadeToBlack(FADE_TO_COMBAT_TIME);
		map_fader_state = 1;
		map_transition_state = 0;
	}

	// Handle transition to the loss state
	if (map_fader_state == 0 && myMap->getControlState() == FADE_TO_LOSS) {
		myFader.fadeToBlack(FADE_TO_COMBAT_TIME);
		map_fader_state = 1;
		getSoundPlayer()->playEffect("Resources/Sound/Lose.ogg");
		map_transition_state = 2;
	}

	// Handle transition to the win state
	if (map_fader_state == 0 && myMap->getControlState() == FADE_TO_WIN) {
		myFader.fadeToBlack(FADE_TO_COMBAT_TIME);
		map_fader_state = 1;
		map_transition_state = 3;
	}

	if (map_fader_state == 1 && myFader.isDone()) {
		myMap->setControlState(SELECTION);
		if (map_transition_state == 0) { StateMachine::getStateMachine()->changeState("COMBAT_STATE"); }
		if (map_transition_state == 1) { 
			unbuildStage(myMap);
			StateMachine::getStateMachine()->changeState("STAGE_SELECT_STATE");
		}
		if (map_transition_state == 2 || map_transition_state == 3) {
			unbuildStage(myMap);
			StateMachine::getStateMachine()->changeState("STAGE_SELECT_STATE");
		}

	}

	// Render my map
	myMap->render();

	myFader.render();

}

void setBattleMap(int num) { map_number = num; }