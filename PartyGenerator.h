#pragma once
#ifndef PARTY_GEN_H
#define PARTY_GEN_H

#include "Unit.h"
#include "Dialogs.h"
#include "DialogButton.h"

// Constants to control how the party generator is shown on screen
const int PARTY_GENERATOR_POS_X = 5;
const int PARTY_GENERATOR_POS_Y = 37;
const int PARTY_GENERATOR_WIDTH = 245;
const int PARTY_GENERATOR_HEIGHT = 42;
const int PARTY_GENERATOR_SPACING = 5;

// Class is used to randomly generate the player's party

class PartyGenerator {
public:
	PartyGenerator();
	~PartyGenerator();
	void randomize();
	void update();
	void render();
	bool isDone();
private:
	void save();
	bool done;
	DialogButton *acceptButton;
	DialogButton *rerollButton;
	Unit *unitOne;
	Unit *unitTwo;
	Unit *unitThree;
	DialogBox *dialog1;
	DialogBox *dialog2;
	DialogBox *dialog3;
};

#endif