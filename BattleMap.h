#pragma once
#ifndef BATTLE_MAP
#define BATTLE_MAP

#include <vector>
#include "Unit.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "DialogButton.h"
#include "AnimatedSprite.h"

enum CONTROL_MODE { UNLOADED_BATTLE, SELECTION, MOVING, ATTACKING, FADE_TO_BATTLE, FADE_TO_LOSS, FADE_TO_WIN};
enum TURN_MODE { PLAYER_TURN, ENEMY_TURN };

// Constants describing the size and position of the map, and layout of the screen
const int MAP_POS_X = 5;
const int MAP_POS_Y = 37;
const int MAP_TILE_SIZE = 16;
const int MAP_WIDTH = 5;
const int MAP_HEIGHT = 5;
const int END_TURN_BUTTON_X = 150;
const int END_TURN_BUTTON_Y = 200;

// Class representing the battlefield

class BattleMap {
public:
	BattleMap();
	void addUnit(Unit *u);
	void setBG(ALLEGRO_BITMAP *bg);
	void setImage(ALLEGRO_BITMAP *img);
	void setHeaderText(std::string s);
	void render();
	void update();
	void reset();
	void setSolidity(std::string s);
	bool getSolidity(int x, int y);
	bool isUnitAt(int x, int y);
	int getControlState();
	void setControlState(int s);
	void clearUnits();
	std::string getHeaderText();
	Unit *getSelectedUnit();
	Unit *getSecondSelectedUnit();
	ALLEGRO_BITMAP *getBG();
	void processMenuClick(std::string signal);

private:
	std::string headerText;
	int turn;
	int cursor_x;
	int cursor_y;
	DialogButton *endTurnButton;
	ALLEGRO_BITMAP *myBG;
	ALLEGRO_BITMAP *myMap;
	AnimatedSprite *myPoof;
	Unit *selectedUnit;
	Unit *secondSelectedUnit;
	std::vector<Unit*> myUnits;
	int mapSolidity[25];
};

#endif