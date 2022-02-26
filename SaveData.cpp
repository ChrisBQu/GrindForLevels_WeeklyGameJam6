#include "SaveData.h"

SaveData *loadedSave = NULL;

// Staring values
// These could be adjusted for game balance, and depending on the size of the game
// As the scope of this project was limited by this being a game jam, I just want
// to open up the content and make things accessible to players.
const int STARTING_COIN_COUNT = 50;
const int STARTING_UNLOCKED_STAGES = 3;

// Constructor
SaveData::SaveData() {

	// Default values
	coins = STARTING_COIN_COUNT;
	unlocked_stages = STARTING_UNLOCKED_STAGES;

	// Generate a default party
	unitOne = new Unit(0, false);
	unitTwo = new Unit(0, false);
	unitThree = new Unit(0, false);

}

// Get the instance of the currently loaded save
SaveData *getLoadedSave() { 
	if (loadedSave == NULL) { loadedSave = new SaveData(); }
	return loadedSave; 
}