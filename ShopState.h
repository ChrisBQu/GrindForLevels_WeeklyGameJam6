#pragma once
#ifndef SHOP_STATE_H
#define SHOP_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "CoinCounter.h"
#include "ScrollingBackground.h"
#include "Shop.h"
#include "DialogButton.h"

// State where the player is purchasing items

class ShopState : public State {
public:
	friend class StateMachine;
	ShopState();
	void render();
	void update();
	void enter();
	void exit();
private:
	DialogButton *myBackButton;
	Shop *myShop;
	ScrollingBG *myBG;
	CoinCounter *myCoinCount;
	ScreenFader myFader;
};

#endif