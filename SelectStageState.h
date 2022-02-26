#pragma once
#ifndef SELECT_STAGE_STATE_H
#define SELECT_STAGE_STATE_H

#include "StateMachine.h"
#include "BattleMap.h"
#include "Dialogs.h"
#include "Unit.h"
#include "ScreenFader.h"
#include "StageSelector.h"
#include "CoinCounter.h"
#include "ScrollingBackground.h"
#include "DialogButton.h"

// State where the player is selecting a stage

class StageSelectState : public State {
public:
	friend class StateMachine;
	StageSelectState();
	void render();
	void update();
	void enter();
	void exit();
private:
	DialogButton *myBackButton;
	ScrollingBG *myBG;
	CoinCounter *myCoinCount;
	ScreenFader myFader;
	StageSelector *mySelector;
};

#endif