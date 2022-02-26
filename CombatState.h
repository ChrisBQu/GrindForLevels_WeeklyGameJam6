#pragma once
#ifndef COMBAT_STATE_H
#define COMBAT_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "CombatScene.h"
#include "ScrollingBackground.h"

// State where two units are in combat with one another


class CombatState : public State {
public:
	friend class StateMachine;
	CombatState();
	void render();
	void update();
	void enter();
	void exit();
private:
	ScrollingBG *myBG;
	CombatScene *myCombatScene;
	ScreenFader myFader;
};

#endif