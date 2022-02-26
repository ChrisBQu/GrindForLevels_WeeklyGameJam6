#include "TitleState.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "ScreenFader.h"
#include "StateMachine.h"
#include "Text.h"

// Constants to control how screen is laid out
const int TITLE_X = 5;
const int TITLE_Y = 5;

// Timers to control how long the image fades in for, fades out for, and is shown for (in seconds)
const double WAIT_BEFORE_FADING_IN_TIME = 0.75;
const double FADE_IN_TIME = 1.5;
const double FADE_OUT_TIME = 1.5;
const double WAIT_WHILE_SHOWING_TIME = 1;

// Constructor for state
TitleState::TitleState() {}

// Executes when entering this state
void TitleState::enter() {
	// Load logo into memory
	fadestate = 0;
	myFader.waitBlack(WAIT_BEFORE_FADING_IN_TIME);
}

// Executes when exiting this state
void TitleState::exit() {}

// Update loop for state
void TitleState::update() {}

// Render loop for state
void TitleState::render() {

	// Render the title
	drawText(al_map_rgb(255,255,255), "FONT4", TITLE_X, TITLE_Y, "Grind for Levels!");
	myFader.render();

	if (myFader.isDone() && fadestate == 0) {
		myFader.fadeFromBlack(FADE_IN_TIME);
		fadestate = 1;
	}

	// Screen fades in from black
	if (myFader.isDone() && fadestate == 1) {
		myFader.waitClear(WAIT_WHILE_SHOWING_TIME);
		fadestate = 2;
	}

	// Screen holds on the logo for a moment
	else if (myFader.isDone() && fadestate == 2) {
		myFader.fadeToBlack(FADE_OUT_TIME);
		fadestate = 3;
	}

	// Screen fades out to black
	else if (myFader.isDone() && fadestate == 3) {
		StateMachine::getStateMachine()->changeState("PARTY_GEN_STATE");
	}

}