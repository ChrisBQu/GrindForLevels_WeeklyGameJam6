#pragma once
#ifndef STAGE_SELECTOR_H
#define STAGE_SELECTOR_H

#include <vector>
#include <string>
#include "LargeMenu.h"

// Constants for where and how to render stage preview and menu
const int MAP_PREVIEW_X = 5;
const int MAP_PREVIEW_Y = 37;
const int MAP_PREVIEW_WIDTH = 80;
const int MAP_PREVIEW_HEIGHT = 80;
const int STAGE_SELECT_MENU_SPACING_X = 5;

// Class lets the player select a stage, and renders a preview and menu of choices

class StageSelector {
public:
	StageSelector();
	void update();
	void render();
	LargeMenu *getMenu();
private:
	LargeMenu *myMenu;
};

#endif