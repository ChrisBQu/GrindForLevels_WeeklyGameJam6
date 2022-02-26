#pragma once
#ifndef INVENTORY_STATE_H
#define INVENTORY_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "CoinCounter.h"
#include "ScrollingBackground.h"
#include "DialogButton.h"
#include "CombatLog.h"

// State where the player looks at their item list

class InventoryState : public State {
public:
	friend class StateMachine;
	InventoryState();
	void render();
	void update();
	void enter();
	void exit();
private:
	CombatLog *myLog;
	DialogButton *myBackButton;
	ScrollingBG *myBG;
	CoinCounter *myCoinCount;
	ScreenFader myFader;
};

#endif