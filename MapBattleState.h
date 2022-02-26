#pragma once
#ifndef MAP_BATTLE_H
#define MAP_BATTLE_H

#include "StateMachine.h"
#include "BattleMap.h"
#include "Dialogs.h"
#include "Unit.h"
#include "ScreenFader.h"
#include "ScrollingBackground.h"
#include "CoinCounter.h"

// State where the player is in-stage, playing the game

class MapBattleState : public State {
public:
	friend class StateMachine;
	MapBattleState();
	void render();
	void update();
	void enter();
	void exit();
private:
	CoinCounter *myCoinCounter;
	ScrollingBG *myBG;
	ScreenFader myFader;
	DialogBox *unitPreviewBox;
	DialogBox *secondUnitPreviewBox;
	BattleMap *myMap;
};

// Function to set which stage will be loaded next
void setBattleMap(int num);

#endif