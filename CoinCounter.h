#pragma once
#ifndef COIN_COUNTER_H
#define COIN_COUNTER_H

#include "AnimatedSprite.h"

// Class is just the box that shows how many coins the player has

class CoinCounter {
public:
	CoinCounter(int xx, int yy);
	~CoinCounter();
	void render();
private:
	AnimatedSprite *myAnimation;
	int x;
	int y;
};

#endif