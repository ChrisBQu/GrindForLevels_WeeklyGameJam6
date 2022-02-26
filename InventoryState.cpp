#include "InventoryState.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include "Text.h"
#include <string>
#include <iostream>
#include "StateMachine.h"
#include "ScreenHeader.h"
#include "UnitLevelBoxes.h"
#include "SaveData.h"
#include "Inventory.h"

using namespace std;

int inventory_fader_state;

// Constants for how the screen is laid out
const int INVENTORY_COIN_COUNT_X = 201;
const int INVENTORY_COIN_COUNT_Y = 201;
const int INVENTORY_SCENE_X = 5;
const int INVENTORY_SCENE_Y = 37;
const int INVENTORY_SCENE_WIDTH = 80;
const int INVENTORY_SCENE_HEIGHT = 80;
const int INVENTORY_UNIT_LEVEL_BOX_X = 5;
const int INVENTORY_UNIT_LEVEL_BOX_Y = 198;
const int INVENTORY_BACK_BUTTON_X = 205;
const int INVENTORY_BACK_BUTTON_Y = 176;
const int INVENTORY_LOG_POS_X = 90;
const int INVENTORY_LOG_POS_Y = 37;
const int INVENTORY_LOG_WIDTH = 140;
const int INVENTORY_LOG_HEIGHT = 96;



// Constants to control the timing of the screen fading effect (in seconds)
const float FADE_IN_TIME_INVENTORY = 0.75;
const float FADE_OUT_TIME_INVENTORY = 0.75;

// Constructor for state
InventoryState::InventoryState() {}

// Executes when entering this state
void InventoryState::enter() {

	// Fade in from black
	ScreenFader newF;
	myFader = newF;
	inventory_fader_state = 0;
	myFader.fadeFromBlack(FADE_IN_TIME_INVENTORY);

	// Create inventory list
	myLog = new CombatLog(INVENTORY_LOG_POS_X, INVENTORY_LOG_POS_Y, INVENTORY_LOG_WIDTH, INVENTORY_LOG_HEIGHT);
	myLog->addText("Kunai x" + to_string(getLoadedSave()->inventory.getItemCount(KUNAI)));
	myLog->addText("Firebomb x" + to_string(getLoadedSave()->inventory.getItemCount(FIREBOMB)));
	myLog->addText("Ice Ray x" + to_string(getLoadedSave()->inventory.getItemCount(ICE_RAY)));
	myLog->addText("Shuriken x" + to_string(getLoadedSave()->inventory.getItemCount(SHURIKEN)));
	myLog->addText("Speed Drink x" + to_string(getLoadedSave()->inventory.getItemCount(SPEED_DRINK)));

	// Create back button
	myBackButton = new DialogButton(INVENTORY_BACK_BUTTON_X, INVENTORY_BACK_BUTTON_Y, SMALL_BUTTON, getResourceManager()->getString("BACK_BUTTON_TEXT"));

	// Load graphical resources into memory
	getResourceManager()->loadImage("Resources/BGs/ShopBG.png", "INVENTORY_SCENE");
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "INVENTORY_BG");
	getResourceManager()->loadImage("Resources/Interface/Coin.png", "COIN");

	// Create coin counter and scrolling background
	myCoinCount = new CoinCounter(INVENTORY_COIN_COUNT_X, INVENTORY_COIN_COUNT_Y);
	myBG = new ScrollingBG("INVENTORY_BG", 64, true);

}

// Executes when exiting this state
void InventoryState::exit() {

	// Unload resources used by this game state
	getResourceManager()->unloadImage("COIN");
	getResourceManager()->unloadImage("INVENTORY_BG");
	getResourceManager()->unloadImage("INVENTORY_SCENE");

	// Clear up memory
	if (myBackButton) { delete myBackButton; }
	if (myCoinCount) { delete myCoinCount; }
	if (myBG) { delete myBG; }
	if (myLog) { delete myLog; }

}

// Update loop for state
void InventoryState::update() {

	myBackButton->update();

	// Check for the user clicking back
	if (myBackButton->isClicked() && inventory_fader_state == 0) {
		inventory_fader_state = 1;
		myFader.fadeToBlack(FADE_OUT_TIME_INVENTORY);
	}

}

// Render loop for state
void InventoryState::render() {

	// Render the background
	myBG->render();

	// Render the menu header
	renderHeader(getResourceManager()->getString("INVENTORY_HEADER"));

	// Render the inventory scene
	al_draw_bitmap(getResourceManager()->getImage("INVENTORY_SCENE"), INVENTORY_SCENE_X, INVENTORY_SCENE_Y, 0);
	al_draw_rectangle(INVENTORY_SCENE_X, INVENTORY_SCENE_Y, INVENTORY_SCENE_X + INVENTORY_SCENE_WIDTH,
		INVENTORY_SCENE_Y + INVENTORY_SCENE_HEIGHT, al_map_rgb(0, 0, 0), 1);

	// Render the item list
	myLog->render();

	// Render the coin counter
	myCoinCount->render();

	// Render the back button
	myBackButton->render();

	// Render the unit level boxes
	renderUnitLevelBoxes(INVENTORY_UNIT_LEVEL_BOX_X, INVENTORY_UNIT_LEVEL_BOX_Y);

	// Handle transition back to main menu
	if (myFader.isDone() && inventory_fader_state == 1) { StateMachine::getStateMachine()->changeState("MAIN_MENU_STATE"); }

	// Render the screen fader
	myFader.render();

}