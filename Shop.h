#pragma once
#ifndef SHOP_H
#define SHOP_H

#include "LargeMenu.h"

// Constants describing the size and position of the map
const int SHOP_SCENE_POS_X = 5;
const int SHOP_SCENE_POS_Y = 37;
const int SHOP_SCENE_WIDTH = 80;
const int SHOP_SCENE_HEIGHT = 80;
const int SHOP_SCENE_SPACING = 3;

// Class is the shop that player buys items from

class Shop {
public:
	Shop();
	~Shop();
	LargeMenu *myMenu;
	void update();
	void render();
};

#endif