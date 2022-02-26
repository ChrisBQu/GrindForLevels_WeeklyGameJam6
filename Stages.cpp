#include "Stages.h"
#include "Unit.h"
#include "Resources.h"
#include "SaveData.h"
#include <iostream>

using namespace std;

void unbuildStage(BattleMap *BM) {
	BM->reset();
	getResourceManager()->unloadImage("MAP_IMAGE");
	getResourceManager()->unloadImage("MAP_BACKGROUND");
}

void buildStageOne(BattleMap *BM) {

	// Set background image of the stage
	getResourceManager()->loadImage("Resources/Maps/Map01.png", "MAP_IMAGE");
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "MAP_BACKGROUND");
	BM->setBG(getResourceManager()->getImage("MAP_BACKGROUND"));
	BM->setImage(getResourceManager()->getImage("MAP_IMAGE"));

	// Set the solidity of the tiles
	BM->setSolidity("1111110001100011000111011");

	// Set the header text of the stage
	BM->setHeaderText("Train in the forest!");

	// Place units on the stage
	Unit *newunit = new Unit(0, 0);
	copyUnitStats(getLoadedSave()->unitOne, newunit);
	newunit->parentLink = getLoadedSave()->unitOne;
	newunit->xpos = 2;
	newunit->ypos = 4;
	BM->addUnit(newunit);

	Unit *newunit2 = new Unit(0, 1);
	newunit2->xpos = 2;
	newunit2->ypos = 1;
	newunit2->NAME = "Effi";
	BM->addUnit(newunit2);

}

void buildStageTwo(BattleMap *BM) {

	// Set background image of the stage
	getResourceManager()->loadImage("Resources/Maps/Map02.png", "MAP_IMAGE");
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "MAP_BACKGROUND");
	BM->setBG(getResourceManager()->getImage("MAP_BACKGROUND"));
	BM->setImage(getResourceManager()->getImage("MAP_IMAGE"));

	// Set the solidity of the tiles
	BM->setSolidity("0010000100000000010011111");

	// Set the header text of the stage
	BM->setHeaderText("Cross the bridge!");

	// Place units on the stage
	Unit *newunit = new Unit(0, 0);
	copyUnitStats(getLoadedSave()->unitOne, newunit);
	newunit->xpos = 0;
	newunit->ypos = 1;

	BM->addUnit(newunit);

	Unit *newunit2 = new Unit(0, 1);
	newunit2->xpos = 2;
	newunit2->ypos = 2;
	newunit2->NAME = "Burza";
	newunit2->awardEXP(50);
	BM->addUnit(newunit2);

}

void buildStageThree(BattleMap *BM) {
	// Set background image of the stage
	getResourceManager()->loadImage("Resources/Maps/Map03.png", "MAP_IMAGE");
	getResourceManager()->loadImage("Resources/BGs/BG01.png", "MAP_BACKGROUND");
	BM->setBG(getResourceManager()->getImage("MAP_BACKGROUND"));
	BM->setImage(getResourceManager()->getImage("MAP_IMAGE"));

	// Set the solidity of the tiles
	BM->setSolidity("1000110001010100000010101");

	// Set the header text of the stage
	BM->setHeaderText("Climb the mountain!");

	// Place units on the stage
	Unit *newunit = new Unit(0, 0);
	copyUnitStats(getLoadedSave()->unitOne, newunit);
	newunit->xpos = 1;
	newunit->ypos = 4;
	BM->addUnit(newunit);

	Unit *newunit0 = new Unit(0, 0);
	copyUnitStats(getLoadedSave()->unitTwo, newunit0);
	newunit0->xpos = 3;
	newunit0->ypos = 4;
	BM->addUnit(newunit0);

	Unit *newunit2 = new Unit(0, 1);
	newunit2->xpos = 1;
	newunit2->ypos = 1;
	newunit2->NAME = "Adrix";
	newunit2->levelTo(9);
	BM->addUnit(newunit2);

	Unit *newunit3 = new Unit(0, 1);
	newunit3->xpos = 3;
	newunit3->ypos = 1;
	newunit3->NAME = "Zedrix";
	newunit3->levelTo(9);
	BM->addUnit(newunit3);

}