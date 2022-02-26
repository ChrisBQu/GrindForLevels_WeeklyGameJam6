#pragma once
#ifndef MAP_MENU
#define MAP_MENU

#include <vector>
#include <string>
#include "BattleMap.h"

class MapMenu {
public:
	MapMenu(BattleMap *parent);
	void open();
	void close();
	void update();
	void render();
	void setPos(int xx, int yy);
	void addOption(std::string s);
	void clearOptions();
	bool isOpen();
private:
	BattleMap *mapParent;
	int chosenval;
	bool visible;
	int cursor;
	int x;
	int y;
	int width;
	int height;
	std::vector<std::string> myOptions;
};

#endif