#include "PartyGenerator.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include <string>
#include "Text.h"
#include "Mouse.h"
#include "SaveData.h"
#include "NameGenerator.h"

using namespace std;

int partygencursor = -1;

// Constructor
PartyGenerator::PartyGenerator() {
	
	done = false;

	// Generate a default random party
	unitOne = new Unit(rand() % NUMBER_OF_CLASSES, false);
	unitTwo = new Unit(rand() % NUMBER_OF_CLASSES, false);
	unitThree = new Unit(rand() % NUMBER_OF_CLASSES, false);

	// Generate names for the units
	NameGenerator Ngen("Resources/Data/Names.txt");
	unitOne->NAME = Ngen.getName();
	unitTwo->NAME = Ngen.getName();
	unitThree->NAME = Ngen.getName();

	// Create the dialog windows to show them in
	dialog1 = new DialogBox(PARTY_GENERATOR_POS_X, PARTY_GENERATOR_POS_Y, PARTY_GENERATOR_WIDTH, PARTY_GENERATOR_HEIGHT);
	dialog2 = new DialogBox(PARTY_GENERATOR_POS_X, PARTY_GENERATOR_POS_Y + PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING,
		PARTY_GENERATOR_WIDTH, PARTY_GENERATOR_HEIGHT);
	dialog3 = new DialogBox(PARTY_GENERATOR_POS_X, PARTY_GENERATOR_POS_Y + 2*(PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING),
		PARTY_GENERATOR_WIDTH, PARTY_GENERATOR_HEIGHT);

	// Create the Accept and Reroll buttons
	acceptButton = new DialogButton(PARTY_GENERATOR_POS_X + 5,
		PARTY_GENERATOR_POS_Y + 3 * (PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING) + 5, SMALL_BUTTON,
		getResourceManager()->getString("ACCEPT_PARTY"));
	rerollButton = new DialogButton(PARTY_GENERATOR_POS_X + 90,
		PARTY_GENERATOR_POS_Y + 3 * (PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING) + 5, SMALL_BUTTON, 
		getResourceManager()->getString("REROLL_PARTY"));
}

// Destructor
PartyGenerator::~PartyGenerator() {
	if (unitOne) { delete unitOne; }
	if (unitTwo) { delete unitTwo; }
	if (unitThree) { delete unitThree; }
	if (dialog1) { delete dialog1; }
	if (dialog2) { delete dialog2; }
	if (dialog3) { delete dialog3; }
	if (acceptButton) { delete acceptButton; }
	if (rerollButton) { delete rerollButton; }
}

// Randomize the party
void PartyGenerator::randomize() {

	done = false;

	// Delete the old party...
	delete unitOne;
	delete unitTwo;
	delete unitThree;

	// ... and create a new party
	unitOne = new Unit(rand() % NUMBER_OF_CLASSES, false);
	unitTwo = new Unit(rand() % NUMBER_OF_CLASSES, false);
	unitThree = new Unit(rand() % NUMBER_OF_CLASSES, false);

	// Generate names for the units
	NameGenerator Ngen("Resources/Data/Names.txt");
	unitOne->NAME = Ngen.getName();
	unitTwo->NAME = Ngen.getName();
	unitThree->NAME = Ngen.getName();
}

// Update loop
void PartyGenerator::update() {

	// Update the buttons
	acceptButton->update();
	rerollButton->update();

	// Check for button clicks
	if (rerollButton->isClicked()) { 
		randomize();
		rerollButton->reset();
	}
	else if (acceptButton->isClicked()) { save(); }

}

// Render loop
void PartyGenerator::render() {

	// Render the dialog windows
	dialog1->render();
	dialog2->render();
	dialog3->render();

	// Cycle through the units, and render their information
	vector<Unit*> units = { unitOne, unitTwo, unitThree };
	for (unsigned int i = 0; i < units.size(); i++) {
		int dx = PARTY_GENERATOR_POS_X;
		int dy = PARTY_GENERATOR_POS_Y + (PARTY_GENERATOR_HEIGHT + PARTY_GENERATOR_SPACING)*i;
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 16 * units.at(i)->CLASSTYPE, 16 * units.at(i)->enemy_unit, 16, 16, dx + 8, dy + 6, 0);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 10, units.at(i)->NAME);
		string linetwo = " " + UNIT_CLASS_NAMES[units.at(i)->CLASSTYPE] + " Lv " + to_string(units.at(i)->LEVEL);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 26, dy + 23, linetwo);
		string linethree = "STR " + to_string(units.at(i)->STR) + "      DEF " + to_string(units.at(i)->DEF) + 
			"      INT " + to_string(units.at(i)->INT) + "      HP " + to_string(units.at(i)->HP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 96, dy + 10, linethree);
		string linefour = "SPD " + to_string(units.at(i)->SPD) + "     MND " + to_string(units.at(i)->MND) + 
			"      MOV " + to_string(units.at(i)->MOV) + "      MP " + to_string(units.at(i)->MP);
		drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", dx + 96, dy + 23, linefour);
	}

	// Render the accept and reroll buttons
	acceptButton->render();
	rerollButton->render();
	
}

// User has accepted the party, so save it to the currently loaded file
void PartyGenerator::save() {

	// Get the loaded save
	SaveData *sav = getLoadedSave();

	// Copy over the unit stats
	copyUnitStats(this->unitOne, sav->unitOne);
	copyUnitStats(this->unitTwo, sav->unitTwo);
	copyUnitStats(this->unitThree, sav->unitThree);

	// Set flag to done
	done = true;
	
}

// Getter to determine if generation has concluded
bool PartyGenerator::isDone() { return done; }