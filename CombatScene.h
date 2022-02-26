#pragma once
#ifndef COMBAT_SCENE_H
#define COMBAT_SCENE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Unit.h"
#include "CombatLog.h"
#include "DialogButton.h"

// Constants describing the size and position of the map
const int COMBAT_SCENE_POS_X = 5;
const int COMBAT_SCENE_POS_Y = 37;
const int COMBAT_SCENE_WIDTH = 80;
const int COMBAT_SCENE_HEIGHT = 80;
const int COMBAT_SCENE_SPACING = 3;

// Constants describing the size and position of the combat log
const int COMBAT_LOG_POS_X = 90;
const int COMBAT_LOG_POS_Y = 37;
const int COMBAT_LOG_WIDTH = 140;
const int COMBAT_LOG_HEIGHT = 96;

enum STATE_OF_COMBAT { SELECTING_COMBAT_TYPE, SHOWING_ATTACK, COMBAT_DONE};

// Class represents a battle taking place between two units

class CombatScene {
public:
	CombatScene();
	int getCombatState();
	void setCombatState(int s);
	void engageCombatTypeOne();
	void engageCombatTypeTwo();
	void engageCombatTypeThree();
	void engageCombatTypeFour();
	void update();
	void render();
private:
	DialogButton *combatButton1;
	DialogButton *combatButton2;
	DialogButton *combatButton3;
	DialogButton *combatButton4;
	DialogButton *doneButton;
	CombatLog *myLog;
	int combat_state;
};

void setCombatUnits(Unit *u1, Unit *u2);
ALLEGRO_BITMAP *getBattleBG();
void setBattleBG(ALLEGRO_BITMAP *bg);

#endif