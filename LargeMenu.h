#pragma once
#ifndef LARGE_MENU_H
#define LARGE_MENU_H

#include <vector>
#include <string>

// Constant controls how menu looks
const int LARGE_MENU_SPACING_Y = 3;

// Class is a menu utilizing large boxes for each option

class LargeMenu {
public:
	LargeMenu(int xx, int yy);
	void update();
	void render();
	void reset();
	void addChoice(std::string s);
	bool isDone();
	int getLastSelected();
	int getChosen();
private:
	int x;
	int y;
	bool done;
	int cursor;
	int chosen;
	int last_selected;
	std::vector<std::string> myChoices;
};

#endif