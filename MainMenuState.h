#pragma once
#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "CoinCounter.h"
#include "ScrollingBackground.h"
#include "LargeMenu.h"

// State where the player is at the main menu

class MainMenuState : public State {
public:
	friend class StateMachine;
	MainMenuState();
	void render();
	void update();
	void enter();
	void exit();
private:
	LargeMenu *myMenu;
	ScrollingBG *myBG;
	CoinCounter *myCoinCount;
	ScreenFader myFader;
};

#endif