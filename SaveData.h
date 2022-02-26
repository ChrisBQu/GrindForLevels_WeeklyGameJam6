#pragma once
#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include "Unit.h"
#include "Inventory.h"

// Class represents the data of the current playthrough (i.e. the player's party)

class SaveData {
public:
	SaveData();
	int coins;
	int unlocked_stages;
	Unit *unitOne;
	Unit *unitTwo;
	Unit *unitThree;
	Inventory inventory;
};

SaveData *getLoadedSave();

#endif