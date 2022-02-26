#include "StudioLogoSplash.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "ScreenFader.h"

// Timers to control how long the image fades in for, fades out for, and is shown for (in seconds)
const double WAIT_BEFORE_FADING_IN_TIME = 0.75;
const double FADE_IN_TIME = 1.5;
const double FADE_OUT_TIME = 1.5;
const double WAIT_WHILE_SHOWING_TIME = 1;

// Constructor for state
StudioLogoState::StudioLogoState() {}

// Executes when entering this state
void StudioLogoState::enter() {
	// Load logo into memory
	getResourceManager()->loadImage("Resources/Splash/StudioLogo.png", "STUDIO_LOGO_SPLASH");
	fadestate = 0;
	myFader.waitBlack(WAIT_BEFORE_FADING_IN_TIME);
}

// Executes when exiting this state
void StudioLogoState::exit() {
	// Clear logo from memory
	getResourceManager()->unloadImage("STUDIO_LOGO_SPLASH");
}

// Update loop for state
void StudioLogoState::update() {}

// Render loop for state
void StudioLogoState::render() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(getResourceManager()->getImage("STUDIO_LOGO_SPLASH"), 38, 40, 0);
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
		StateMachine::getStateMachine()->changeState("GAME_JAM_LOGO_STATE");
	}

}