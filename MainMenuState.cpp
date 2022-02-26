#include "MainMenuState.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Unit.h"
#include "Text.h"
#include <string>
#include <iostream>
#include "StateMachine.h"
#include "ScreenHeader.h"
#include "GameClass.h"
#include "UnitLevelBoxes.h"
#include "Sound.h"

using namespace std;

int mainmenu_fader_state;
int mainmenu_transition_state;

// Constants for how the screen is laid out
const int MAIN_MENU_COIN_COUNT_X = 201;
const int MAIN_MENU_COIN_COUNT_Y = 201;
const int MAIN_MENU_X = 48;
const int MAIN_MENU_Y = 35;
const int MAIN_MENU_UNIT_LEVEL_BOX_X = 5;
const int MAIN_MENU_UNIT_LEVEL_BOX_Y = 198;

// Constants to control the timing of the screen fading effect (in seconds)
const float FADE_IN_TIME_MAIN_MENU = 0.75;
const float FADE_OUT_TIME_MAIN_MENU = 0.75;

// Constructor for state
MainMenuState::MainMenuState() {}

// Executes when entering this state
void MainMenuState::enter() {

	// Fade in from black
	ScreenFader newF;
	myFader = newF;
	mainmenu_fader_state = 0;
	mainmenu_transition_state = -1;
	myFader.fadeFromBlack(FADE_IN_TIME_MAIN_MENU);

	// Load images of map previews and of header, into memory
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "MAIN_MENU_BG");
	getResourceManager()->loadImage("Resources/Interface/Coin.png", "COIN");

	// Create coin counter and scrolling background
	myCoinCount = new CoinCounter(MAIN_MENU_COIN_COUNT_X, MAIN_MENU_COIN_COUNT_Y);
	myBG = new ScrollingBG("MAIN_MENU_BG", 64, true);

	// Build the main menu
	myMenu = new LargeMenu(MAIN_MENU_X, MAIN_MENU_Y);
	myMenu->addChoice(getResourceManager()->getString("MAIN_MENU_STAGE_SELECT"));
	myMenu->addChoice(getResourceManager()->getString("MAIN_MENU_PARTY"));
	myMenu->addChoice(getResourceManager()->getString("MAIN_MENU_INVENTORY"));
	myMenu->addChoice(getResourceManager()->getString("MAIN_MENU_SHOP"));
	myMenu->addChoice(getResourceManager()->getString("MAIN_MENU_QUIT"));

	// Start playing music if none is playing
	if (getSoundPlayer()->musicIsPlaying() == false) {
		getSoundPlayer()->playMusic("Resources/Sound/Song3.ogg");
	}

}

// Executes when exiting this state
void MainMenuState::exit() {

	// Unload resources used by this game state
	getResourceManager()->unloadImage("COIN");

	// Free coin counter, scrolling background, and menu from memory
	if (myCoinCount) { delete myCoinCount; }
	if (myBG) { delete myBG; }
	if (myMenu) { delete myMenu; }

}

// Update loop for state
void MainMenuState::update() {
	myMenu->update();
}

// Render loop for state
void MainMenuState::render() {

	// Render the background
	myBG->render();

	// Render the menu header
	renderHeader(getResourceManager()->getString("MAIN_MENU_HEADER"));

	// Render the menu
	myMenu->render();

	// Render the coin counter
	myCoinCount->render();

	// Render the unit level boxes
	renderUnitLevelBoxes(MAIN_MENU_UNIT_LEVEL_BOX_X, MAIN_MENU_UNIT_LEVEL_BOX_Y);

	// Check for user clicking a menu item
	if (myMenu->isDone() && mainmenu_fader_state == 0) { mainmenu_transition_state = myMenu->getChosen(); }
	if (mainmenu_transition_state != -1 && mainmenu_fader_state == 0) {
		mainmenu_fader_state = 1;
		myFader.fadeToBlack(FADE_OUT_TIME_MAIN_MENU);
	}

	// Make the transition to another state
	if (myFader.isDone() && mainmenu_fader_state == 1) {
		if (mainmenu_transition_state == 0) { StateMachine::getStateMachine()->changeState("STAGE_SELECT_STATE"); }
		if (mainmenu_transition_state == 1) { StateMachine::getStateMachine()->changeState("PARTY_ORDER_STATE"); }
		if (mainmenu_transition_state == 2) { StateMachine::getStateMachine()->changeState("INVENTORY_STATE"); }
		if (mainmenu_transition_state == 3) { StateMachine::getStateMachine()->changeState("SHOP_STATE"); }
		else if (mainmenu_transition_state == 4) { getGameClass()->end(); }
	}

	// Render the screen fader
	myFader.render();

}