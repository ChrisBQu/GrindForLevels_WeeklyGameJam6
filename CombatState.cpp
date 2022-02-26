#include "CombatState.h"
#include "Text.h"
#include "Resources.h"
#include "Sound.h"
#include "StateMachine.h"
#include "ScreenHeader.h"

// Constants to control the timing of the screen fading effect (in seconds)
const double FADE_IN_TIME = 1;
const double FADE_OUT_TIME = 0.75;

int combat_fader_state = 0; // Variable tracking what the screen fader for this state is doing

// Constructor for state
CombatState::CombatState() {
	myCombatScene = new CombatScene();
}

// Executes when entering this state
void CombatState::enter() {

	combat_fader_state = 0;

	// Load graphical resources
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "COMBAT_SCROLLING_BG");
	getResourceManager()->loadImage("Resources/BGs/CBG01a.png", "COMBAT_BG_LEFT");

	// Begin playing music
	getSoundPlayer()->playMusic("Resources/Sound/Song2.ogg");

	// Create a scrolling background
	myBG = new ScrollingBG("COMBAT_SCROLLING_BG", 64, true);

	// Fade in from black
	myFader.fadeFromBlack(FADE_IN_TIME);

}

// Executes when exiting this state
void CombatState::exit() {

	// Free the scrolling background from memory
	if (myBG) { delete myBG; }

	// Unload graphical resources
	getResourceManager()->unloadImage("COMBAT_SCROLLING_BG");
	getResourceManager()->unloadImage("COMBAT_BG_LEFT");

}

// Update loop for state
void CombatState::update() {
	myCombatScene->update();
}

// Render loop for state
void CombatState::render() {

	// Render the background
	myBG->render();

	// Render the combat header
	renderHeader(getResourceManager()->getString("COMBAT_HEADER_TEXT"));

	// Render the combat scene
	myCombatScene->render();

	// When combat is over, return to the BattleMap state
	if (combat_fader_state == 0 && myCombatScene->getCombatState() == COMBAT_DONE) {
		myFader.fadeToBlack(FADE_OUT_TIME);
		combat_fader_state = 1;
	}
	if (myFader.isDone() && combat_fader_state == 1) {
		myCombatScene->setCombatState(SELECTING_COMBAT_TYPE);
		StateMachine::getStateMachine()->changeState("MAP_BATTLE_STATE");
	}

	// Rendeer the screen fader
	myFader.render();



}