#include "SelectStageState.h"
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
#include "LargeMenu.h"
#include "ScreenHeader.h"
#include "UnitLevelBoxes.h"
#include "MapBattleState.h"

using namespace std;

// Variables for controlling screen transitions to other states
int stageselect_fader_state;
int stageselect_transition_state;

// Constants for how the screen is laid out
const int STAGE_SELECT_COIN_COUNT_X = 201;
const int STAGE_SELECT_COIN_COUNT_Y = 201;
const int STAGE_SELECT_BACK_BUTTON_X = 205;
const int STAGE_SELECT_BACK_BUTTON_Y = 176;
const int STAGE_SELECT_UNIT_LEVEL_BOX_X = 5;
const int STAGE_SELECT_UNIT_LEVEL_BOX_Y = 198;

// Constants to control the timing of the screen fading effect (in seconds)
const float FADE_FROM_STAGE_SELECT = 0.75;
const float FADE_IN_TIME_STAGE_SELECT = 1;

// Constructor for state
StageSelectState::StageSelectState() {}

// Executes when entering this state
void StageSelectState::enter() {

	// Fade in from black with a new screen fader
	ScreenFader newF;
	myFader = newF;
	stageselect_fader_state = 0;
	stageselect_transition_state = -1;
	myFader.fadeFromBlack(FADE_IN_TIME_STAGE_SELECT);

	// Create stage selector and coin counter
	myCoinCount = new CoinCounter(STAGE_SELECT_COIN_COUNT_X, STAGE_SELECT_COIN_COUNT_Y);
	mySelector = new StageSelector();


	// Load images of map previews and of header, into memory
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "STAGE_SELECT_BG");
	getResourceManager()->loadImage("Resources/Interface/Coin.png", "COIN");

	// Crate scrolling background
	myBG = new ScrollingBG("STAGE_SELECT_BG", 64, true);

	// Load images of maps into memory
	getResourceManager()->loadImage("Resources/Maps/Map01.png", "MAP_PREVIEW_01");
	getResourceManager()->loadImage("Resources/Maps/Map02.png", "MAP_PREVIEW_02");
	getResourceManager()->loadImage("Resources/Maps/Map03.png", "MAP_PREVIEW_03");

	// Create the dialog buttons needed on this screen
	myBackButton = new DialogButton(STAGE_SELECT_BACK_BUTTON_X, STAGE_SELECT_BACK_BUTTON_Y,
		SMALL_BUTTON, getResourceManager()->getString("BACK_BUTTON_TEXT"));

}

// Executes when exiting this state
void StageSelectState::exit() {

	// Unload resources used by this game state
	getResourceManager()->unloadImage("COIN");
	getResourceManager()->unloadImage("MAP_PREVIEW_01");
	getResourceManager()->unloadImage("MAP_PREVIEW_02");
	getResourceManager()->unloadImage("MAP_PREVIEW_03");

	// Free stage selector, coin counter, and scrolling background from memory
	if (mySelector) { delete mySelector; }
	if (myCoinCount) { delete myCoinCount; }
	if (myBG) { delete myBG; }

	// Free dialog buttons from memory
	if (myBackButton) { delete myBackButton; }

}

// Update loop for state
void StageSelectState::update() {
	myBackButton->update();
	mySelector->update();
}

// Render loop for state
void StageSelectState::render() {

	// Render the background
	myBG->render();

	// Render dialog buttons
	myBackButton->render();

	// Render the stage select header
	renderHeader(getResourceManager()->getString("STAGE_SELECT_HEADER"));

	// Render the stage selector (stage preview and menu)
	mySelector->render();

	// Render the coin counter
	myCoinCount->render();

	// Render the unit level boxes
	renderUnitLevelBoxes(STAGE_SELECT_UNIT_LEVEL_BOX_X, STAGE_SELECT_UNIT_LEVEL_BOX_Y);

	// Check for transition to the map screen
	if (mySelector->getMenu()->isDone() && stageselect_fader_state == 0) {
		stageselect_fader_state = 1;
		stageselect_transition_state = 0;
		setBattleMap(mySelector->getMenu()->getChosen()+1);
		myFader.fadeToBlack(FADE_FROM_STAGE_SELECT);
	}

	// Check for transition to  the main menu
	else if (myBackButton->isClicked() && stageselect_fader_state == 0) {
		stageselect_fader_state = 1;
		stageselect_transition_state = 1;
		myFader.fadeToBlack(FADE_FROM_STAGE_SELECT);
	}

	// Make the transition
	if (myFader.isDone() && stageselect_fader_state == 1) { 
		if (stageselect_transition_state == 0) { StateMachine::getStateMachine()->changeState("MAP_BATTLE_STATE"); }
		if (stageselect_transition_state == 1) { StateMachine::getStateMachine()->changeState("MAIN_MENU_STATE"); }
	}



	// Render the screen fader
	myFader.render();

}