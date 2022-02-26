#include "ShopState.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include "Text.h"
#include <string>
#include <iostream>
#include "StateMachine.h"
#include "ScreenHeader.h"
#include "UnitLevelBoxes.h"

using namespace std;

int shop_fader_state;

// Constants for how the screen is laid out
const int SHOP_COIN_COUNT_X = 201;
const int SHOP_COIN_COUNT_Y = 201;
const int SHOP_COUNTER_X = 5;
const int SHOP_COUNTER_Y = 37;
const int SHOP_UNIT_LEVEL_BOX_X = 5;
const int SHOP_UNIT_LEVEL_BOX_Y = 198;
const int SHOP_BACK_BUTTON_X = 205;
const int SHOP_BACK_BUTTON_Y = 176;


// Constants to control the timing of the screen fading effect (in seconds)
const float FADE_IN_TIME_SHOP = 0.75;
const float FADE_OUT_TIME_SHOP = 0.75;

// Constructor for state
ShopState::ShopState() {}

// Executes when entering this state
void ShopState::enter() {

	// Fade in from black
	ScreenFader newF;
	myFader = newF;
	shop_fader_state = 0;
	myFader.fadeFromBlack(FADE_IN_TIME_SHOP);

	// Create a shop
	myShop = new Shop();
	myBackButton = new DialogButton(SHOP_BACK_BUTTON_X, SHOP_BACK_BUTTON_Y, SMALL_BUTTON, getResourceManager()->getString("BACK_BUTTON_TEXT"));

	// Load graphical resources into memory
	getResourceManager()->loadImage("Resources/BGs/ShopBG.png", "SHOP_SCENE");
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "SHOP_BG");
	getResourceManager()->loadImage("Resources/Interface/Coin.png", "COIN");

	// Create coin counter and scrolling background
	myCoinCount = new CoinCounter(SHOP_COIN_COUNT_X, SHOP_COIN_COUNT_Y);
	myBG = new ScrollingBG("SHOP_BG", 64, true);

}

// Executes when exiting this state
void ShopState::exit() {

	// Unload resources used by this game state
	getResourceManager()->unloadImage("COIN");
	getResourceManager()->unloadImage("SHOP_BG");
	getResourceManager()->unloadImage("SHOP_SCENE");

	// Clear up memory
	if (myShop) { delete myShop; }
	if (myBackButton) { delete myBackButton; }
	if (myCoinCount) { delete myCoinCount; }
	if (myBG) { delete myBG; }

}

// Update loop for state
void ShopState::update() {
	myShop->update();
	myBackButton->update();

	// Check for the user clicking back
	if (myBackButton->isClicked() && shop_fader_state == 0) {
		shop_fader_state = 1;
		myFader.fadeToBlack(FADE_OUT_TIME_SHOP);
	}

}

// Render loop for state
void ShopState::render() {

	// Render the background
	myBG->render();

	// Render the menu header
	renderHeader(getResourceManager()->getString("SHOP_HEADER"));

	// Render the shop scene and menu
	myShop->render();

	// Render the coin counter
	myCoinCount->render();

	// Render the back button
	myBackButton->render();

	// Render the unit level boxes
	renderUnitLevelBoxes(SHOP_UNIT_LEVEL_BOX_X, SHOP_UNIT_LEVEL_BOX_Y);

	// Handle transition back to main menu
	if (myFader.isDone() && shop_fader_state == 1) { StateMachine::getStateMachine()->changeState("MAIN_MENU_STATE"); }

	// Render the screen fader
	myFader.render();

}