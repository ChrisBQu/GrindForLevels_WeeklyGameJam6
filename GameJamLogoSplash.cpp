#include "GameJamSplash.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "ScreenFader.h"
#include "StateMachine.h"
#include "Text.h"

// Timers to control how long the image fades in for, fades out for, and is shown for (in seconds)
const double WAIT_BEFORE_FADING_IN_TIME = 0.75;
const double FADE_IN_TIME = 1.5;
const double FADE_OUT_TIME = 1.5;
const double WAIT_WHILE_SHOWING_TIME = 1;

// Constructor for state
GameJamLogoState::GameJamLogoState() {}

// Executes when entering this state
void GameJamLogoState::enter() {
	// Load logo into memory
	getResourceManager()->loadImage("Resources/Splash/GameJamLogo.png", "GAME_JAM_SPLASH");
	fadestate = 0;
	myFader.waitBlack(WAIT_BEFORE_FADING_IN_TIME);
}

// Executes when exiting this state
void GameJamLogoState::exit() {
	// Clear logo from memory
	getResourceManager()->unloadImage("STUDIO_LOGO_SPLASH");
}

// Update loop for state
void GameJamLogoState::update() {}

// Render loop for state
void GameJamLogoState::render() {

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(getResourceManager()->getImage("GAME_JAM_SPLASH"), 72, 30, 0);
	drawText(al_map_rgb(255, 255, 255), "FONT1", 50, 164, getResourceManager()->getString("GAME_JAM_INTRO"));

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
		StateMachine::getStateMachine()->changeState("TITLE_STATE");
	}

}