#pragma once
#ifndef PARTY_GENERATOR_STATE_H
#define PARTY_GENERATOR_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "PartyGenerator.h"
#include "ScrollingBackground.h"

// State where three units are created randomly for the player's party

class PartyGeneratorState : public State {
public:
	friend class StateMachine;
	PartyGeneratorState();
	void render();
	void update();
	void enter();
	void exit();
private:
	ScrollingBG *myBG;
	PartyGenerator myGenerator;
	ScreenFader myFader;
};

#endif