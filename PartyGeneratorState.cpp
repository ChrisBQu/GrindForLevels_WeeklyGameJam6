#include "PartyGeneratorState.h"
#include "Text.h"
#include "Resources.h"
#include "Sound.h"
#include "StateMachine.h"
#include "PartyGenerator.h"
#include "ScreenHeader.h"

// Constants to control the timing of the screen fading effect (in seconds)
const double FADE_IN_TIME_PARTY_GEN = 1;
const double FADE_OUT_TIME_PARTY_GEN = 0.75;

int party_gen_fader_state = 0; // Variable tracking what the screen fader for this state is doing

// Constructor for state
PartyGeneratorState::PartyGeneratorState() {}

// Executes when entering this state
void PartyGeneratorState::enter() {

	party_gen_fader_state = 0;

	// Load graphical resources
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "SCROLL_BACKGROUND");

	myBG = new ScrollingBG("SCROLL_BACKGROUND", 64, true);

	// Begin playing music
	getSoundPlayer()->playMusic("Resources/Sound/Song4.ogg");

	myFader.fadeFromBlack(FADE_IN_TIME_PARTY_GEN);

}

// Executes when exiting this state
void PartyGeneratorState::exit() {

	// Unload graphical resources
	getResourceManager()->unloadImage("SCROLL_BACKGROUND");

	// Clear scrolling background from memory
	if (myBG) { delete myBG; }

	// Stop playing music
	getSoundPlayer()->stopMusic();

}

// Update loop for state
void PartyGeneratorState::update() {
	myGenerator.update();
}

// Render loop for state
void PartyGeneratorState::render() {

	// Render the background
	myBG->render();

	// Render the party generation header
	renderHeader(getResourceManager()->getString("PARTY_GEN_HEADER"));

	// Render the generated details
	myGenerator.render();

	if (myGenerator.isDone() && party_gen_fader_state == 0) {
		party_gen_fader_state = 1;
		myFader.fadeToBlack(FADE_OUT_TIME_PARTY_GEN);
	}

	if (myFader.isDone() && party_gen_fader_state == 1) {
		StateMachine::getStateMachine()->changeState("MAIN_MENU_STATE");
	}

	// Rendeer the screen fader
	myFader.render();

}