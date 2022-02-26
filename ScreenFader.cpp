#include "ScreenFader.h"
#include "GameClass.h"
#include "allegro5/allegro_primitives.h"

// Constructor
ScreenFader::ScreenFader() {
	done = false;
	onStep = 0;
	maxStep = 1;
	mode = 0;
}

// Call the fader to transition from black
void ScreenFader::fadeFromBlack(float seconds) {
	mode = FROM_BLACK;
	onStep = 0;
	done = false;
	maxStep = seconds * getGameClass()->getFPS();
}

// Call the fader to transition to black
void ScreenFader::fadeToBlack(float seconds) {
	mode = TO_BLACK;
	onStep = 0;
	done = false;
	maxStep = seconds * getGameClass()->getFPS();
}

// Fader will wait for a bit, with the screen clear
void ScreenFader::waitClear(float seconds) {
	mode = WAIT_CLEAR;
	onStep = 0;
	done = false;
	maxStep = seconds * getGameClass()->getFPS();
}

// Fader will wait for a bit, with the screen black
void ScreenFader::waitBlack(float seconds) {
	mode = WAIT_BLACK;
	onStep = 0;
	done = false;
	maxStep = seconds * getGameClass()->getFPS();
}

// Render function is dependant on the mode that the fader is in
void ScreenFader::render() {

	if (onStep < maxStep) { onStep++; }
	else { done = true; }

	float percent = ((onStep * 1.0) / maxStep)*255;

	// Fader is fading in from black
	if (mode == FROM_BLACK) { al_draw_filled_rectangle(0, 0, getGameClass()->getScreenWidth(), getGameClass()->getScreenHeight(), al_map_rgba(0, 0, 0, 255 - percent)); }

	// Fader is fading out to black
	else if (mode == TO_BLACK) { al_draw_filled_rectangle(0, 0, getGameClass()->getScreenWidth(), getGameClass()->getScreenHeight(), al_map_rgba(0, 0, 0, percent)); }

	// Fader is fading out to black
	else if (mode == WAIT_BLACK) { al_draw_filled_rectangle(0, 0, getGameClass()->getScreenWidth(), getGameClass()->getScreenHeight(), al_map_rgba(0, 0, 0, 255)); }
}

// Return whether or not the fader is currently done transitioning
bool ScreenFader::isDone() { return done; }
