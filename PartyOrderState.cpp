#include "PartyOrderState.h"
#include "Resources.h"
#include "ScreenHeader.h"
#include <vector>
#include "Text.h"
#include "SaveData.h"
#include <iostream>

using namespace std;

// Constants to control how the party order screen is laid out
const int PARTY_ORDER_DIALOG_POS_X = 5;
const int PARTY_ORDER_DIALOG_POS_Y = 37;
const int PARTY_ORDER_DIALOG_WIDTH = 245;
const int PARTY_ORDER_DIALOG_HEIGHT = 42;
const int PARTY_ORDER_DIALOG_SPACING = 5;

// Constants to control the timing of the screen fading effect (in seconds)
const double FADE_IN_TIME_PARTY_ORDER = 1;
const double FADE_OUT_TIME_PARTY_ORDER = 0.75;

int party_order_fader_state = 0; // Variable tracking what the screen fader for this state is doing

// Constructor for state
PartyOrderState::PartyOrderState() {}

// Executes when entering this state
void PartyOrderState::enter() {

	// Fade in from black
	ScreenFader newF;
	myFader = newF;
	party_order_fader_state = 0;
	myFader.fadeFromBlack(FADE_IN_TIME_PARTY_ORDER);

	// Load graphical resources
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "SCROLL_BACKGROUND");

	// Create scrolling background
	myBG = new ScrollingBG("SCROLL_BACKGROUND", 64, true);

	// Create dialogs and buttons
	dialog1 = new DialogBox(PARTY_ORDER_DIALOG_POS_X, PARTY_ORDER_DIALOG_POS_Y, PARTY_ORDER_DIALOG_WIDTH, PARTY_ORDER_DIALOG_HEIGHT);
	dialog2 = new DialogBox(PARTY_ORDER_DIALOG_POS_X, PARTY_ORDER_DIALOG_POS_Y + (PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		PARTY_ORDER_DIALOG_WIDTH, PARTY_ORDER_DIALOG_HEIGHT);
	dialog3 = new DialogBox(PARTY_ORDER_DIALOG_POS_X, PARTY_ORDER_DIALOG_POS_Y + 2*(PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		PARTY_ORDER_DIALOG_WIDTH, PARTY_ORDER_DIALOG_HEIGHT);

	switch1and2 = new DialogButton(PARTY_ORDER_DIALOG_POS_X + 5, PARTY_ORDER_DIALOG_POS_Y + 3 * (PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		SMALL_BUTTON, "1 <--> 2");
	switch1and3 = new DialogButton(PARTY_ORDER_DIALOG_POS_X + 55, PARTY_ORDER_DIALOG_POS_Y + 3 * (PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		SMALL_BUTTON, "1 <--> 3");
	switch2and3 = new DialogButton(PARTY_ORDER_DIALOG_POS_X + 105, PARTY_ORDER_DIALOG_POS_Y + 3 * (PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		SMALL_BUTTON, "2 <--> 3");
	backButton = new DialogButton(PARTY_ORDER_DIALOG_POS_X + 155, PARTY_ORDER_DIALOG_POS_Y + 3 * (PARTY_ORDER_DIALOG_HEIGHT + PARTY_ORDER_DIALOG_SPACING),
		SMALL_BUTTON, getResourceManager()->getString("BACK_BUTTON_TEXT"));

}

// Executes when exiting this state
void PartyOrderState::exit() {

	// Unload graphical resources
	getResourceManager()->unloadImage("SCROLL_BACKGROUND");

	// Clear scrolling background from memory
	if (myBG) { delete myBG; }

	// Clear buttons and dialogs from memory
	if (dialog1) { delete dialog1; }
	if (dialog2) { delete dialog2; }
	if (dialog3) { delete dialog3; }
	if (switch1and2) { delete switch1and2; }
	if (switch1and3) { delete switch1and3; }
	if (switch2and3) { delete switch2and3; }
	if (backButton) { delete backButton; }

}

// Update loop for state
void PartyOrderState::update() {
	switch1and2->update();
	switch2and3->update();
	switch1and3->update();
	backButton->update();

	// User switches around party members
	if (switch1and2->isClicked()) {
		switch1and2->reset();
		Unit *tmp = getLoadedSave()->unitOne;
		getLoadedSave()->unitOne = getLoadedSave()->unitTwo;
		getLoadedSave()->unitTwo = tmp;
	}

	if (switch2and3->isClicked()) {
		switch2and3->reset();
		Unit *tmp = getLoadedSave()->unitTwo;
		getLoadedSave()->unitTwo = getLoadedSave()->unitThree;
		getLoadedSave()->unitThree = tmp;
	}

	if (switch1and3->isClicked()) {
		switch1and3->reset();
		Unit *tmp = getLoadedSave()->unitOne;
		getLoadedSave()->unitOne = getLoadedSave()->unitThree;
		getLoadedSave()->unitThree = tmp;
	}

	// User presses back
	if (backButton->isClicked()) {
		backButton->reset();
		party_order_fader_state = 1;
		myFader.fadeToBlack(FADE_OUT_TIME_PARTY_ORDER);
	}

}

// Render loop for state
void PartyOrderState::render() {

	// Render the background
	myBG->render();

	// Render the party generation header
	renderHeader(getResourceManager()->getString("PARTY_ORDER_HEADER"));

	// Render the dialog windows
	dialog1->render();
	dialog2->render();
	dialog3->render();

	// Render the buttons
	switch1and2->render();
	switch1and3->render();
	switch2and3->render();
	backButton->render();

	// Cycle through the units, and render their information
	vector<Unit*> units = { getLoadedSave()->unitOne, getLoadedSave()->unitTwo, getLoadedSave()->unitThree };
	for (unsigned int i = 0; i < units.size(); i++) {
		int dx = PARTY_GENERATOR_POS_X;
		int dy = PARTY_GENERATOR_POS_Y + (PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING)*i;
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 16 * units.at(i)->CLASSTYPE, 16 * units.at(i)->enemy_unit, 16, 16, dx + 8, dy + 6, 0);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 10, units.at(i)->NAME);
		string linetwo = " " + UNIT_CLASS_NAMES[units.at(i)->CLASSTYPE] + " Lv " + to_string(units.at(i)->LEVEL);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 23, linetwo);
		string linethree = "STR " + to_string(units.at(i)->STR) + "      DEF " + to_string(units.at(i)->DEF) +
			"      INT " + to_string(units.at(i)->INT) + "      HP " + to_string(units.at(i)->HP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 96, dy + 10, linethree);
		string linefour = "SPD " + to_string(units.at(i)->SPD) + "     MND " + to_string(units.at(i)->MND) +
			"      MOV " + to_string(units.at(i)->MOV) + "      MP " + to_string(units.at(i)->MP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 96, dy + 23, linefour);
	}

	// Transition back to main menu
	if (myFader.isDone() && party_order_fader_state == 1) {
		StateMachine::getStateMachine()->changeState("MAIN_MENU_STATE");
	}

	// Rendeer the screen fader
	myFader.render();



}