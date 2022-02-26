#include "CombatScene.h"
#include "allegro5/allegro_primitives.h"
#include "Resources.h"
#include "Text.h"
#include "Mouse.h"
#include <iostream>
#include "CombatSkill.h"
#include "AI_Soldier.h"
#include "AI_Magician.h"

using namespace std;

ALLEGRO_BITMAP *battle_background;
Unit *combatUnitLeft;
Unit *combatUnitRight;

// Variables used to make the icons "clang" together
int icon_clang_dir = 1;
float icon_clang_ticks = 0;
float icon_clang_max_ticks = 180;

// Constructor
CombatScene::CombatScene() {
	combat_state = SELECTING_COMBAT_TYPE;
	myLog = new CombatLog(COMBAT_LOG_POS_X, COMBAT_LOG_POS_Y, COMBAT_LOG_WIDTH, COMBAT_LOG_HEIGHT);

	// Create the four combat type buttons
	combatButton1 = new DialogButton(COMBAT_SCENE_POS_X + COMBAT_SCENE_WIDTH + COMBAT_SCENE_SPACING + 5, COMBAT_SCENE_POS_Y,
		MEDIUM_BUTTON, getResourceManager()->getString("COMBAT_TYPE_1"));
	combatButton2 = new DialogButton(COMBAT_SCENE_POS_X + COMBAT_SCENE_WIDTH + COMBAT_SCENE_SPACING + 5, COMBAT_SCENE_POS_Y + 23,
		MEDIUM_BUTTON, getResourceManager()->getString("COMBAT_TYPE_2"));
	combatButton3 = new DialogButton(COMBAT_SCENE_POS_X + COMBAT_SCENE_WIDTH + COMBAT_SCENE_SPACING + 86, COMBAT_SCENE_POS_Y,
		MEDIUM_BUTTON, getResourceManager()->getString("COMBAT_TYPE_3"));
	combatButton4 = new DialogButton(COMBAT_SCENE_POS_X + COMBAT_SCENE_WIDTH + COMBAT_SCENE_SPACING + 86, COMBAT_SCENE_POS_Y + 23,
		MEDIUM_BUTTON, getResourceManager()->getString("COMBAT_TYPE_4"));

	doneButton = new DialogButton(COMBAT_LOG_POS_X, COMBAT_LOG_POS_Y + COMBAT_LOG_HEIGHT + 5,
		MEDIUM_BUTTON, getResourceManager()->getString("AFTER_BATTLE_BUTTON"));
}

// Update loop
void CombatScene::update() {

	// Update all of the buttons if they are available
	if (combat_state == SELECTING_COMBAT_TYPE) {

		// If it's the player's attack, they can choose the combat type
		if (combatUnitLeft->enemy_unit == false) {
			combatButton1->update();
			combatButton2->update();
			combatButton3->update();
			combatButton4->update();

			// User clicked button 1
			if (combatButton1->isClicked()) {
				combatButton1->reset();
				combat_state = SHOWING_ATTACK;
				engageCombatTypeOne();
			}

			// User clicked button 2
			if (combatButton2->isClicked()) {
				combatButton2->reset();
				combat_state = SHOWING_ATTACK;
				engageCombatTypeTwo();
			}

			// User clicked button 3
			if (combatButton3->isClicked()) {
				combatButton3->reset();
				combat_state = SHOWING_ATTACK;
				engageCombatTypeThree();
			}

			// User clicked button 4
			if (combatButton4->isClicked()) {
				combatButton4->reset();
				combat_state = SHOWING_ATTACK;
				engageCombatTypeFour();
			}
		}

		// Otherwise the enemy will choose the combat type
		else {
			combat_state = SHOWING_ATTACK;
			int r = rand() % 101;
			if (r < 67) { engageCombatTypeOne(); }
			else { engageCombatTypeTwo(); }
		}

	}

	// The aftermath of the combat is shown, and the user can click the button to go back to the map
	if (combat_state == SHOWING_ATTACK) {
		doneButton->update();
		if (doneButton->isClicked()) {
			doneButton->reset();
			combat_state = COMBAT_DONE;
		}
	}
}

// Render loop
void CombatScene::render() {

	// Make the unit icons sway back and forth, clanging into each other
	icon_clang_ticks += 6; // 6 is an arbitrary speed. Higher is faster
	if (icon_clang_ticks >= icon_clang_max_ticks) { 
		icon_clang_dir *= -1; 
		icon_clang_ticks = 0;
	}

	// Draw combat scene
	al_draw_bitmap(getResourceManager()->getImage("COMBAT_BG_LEFT"), COMBAT_SCENE_POS_X, COMBAT_SCENE_POS_Y, 0);
	al_draw_rectangle(COMBAT_SCENE_POS_X, COMBAT_SCENE_POS_Y, COMBAT_SCENE_POS_X + COMBAT_SCENE_WIDTH, 
		COMBAT_SCENE_POS_Y + COMBAT_SCENE_HEIGHT, al_map_rgb(0, 0, 0), 1);

	// Draw unit icons in the scene
	al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 0, 16 * combatUnitLeft->enemy_unit, 16, 16,
		COMBAT_SCENE_POS_X + 36 + (icon_clang_ticks/icon_clang_max_ticks)*icon_clang_dir, COMBAT_SCENE_POS_Y + 30, 0);

	al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 0, 16 * combatUnitRight->enemy_unit, 16, 16,
		COMBAT_SCENE_POS_X + 50 - (icon_clang_ticks / icon_clang_max_ticks)*icon_clang_dir, COMBAT_SCENE_POS_Y + 30, 0);

	// Draw attack option buttons if the user is still selecting the attack type
	if (combat_state == SELECTING_COMBAT_TYPE) {
		combatButton1->render();
		combatButton2->render();
		combatButton3->render();
		combatButton4->render();
	}

	// Show the results of combat
	if (combat_state == SHOWING_ATTACK) { 
		myLog->render(); 
		doneButton->render();
	}

}

// Get and set the scrolling background associated with the combat scene
ALLEGRO_BITMAP *getBattleBG() { return battle_background; }
void setBattleBG(ALLEGRO_BITMAP *bg) { battle_background = bg; }

// Set the units taking part in the combat
void setCombatUnits(Unit *u1, Unit *u2) {
	combatUnitLeft = u1;
	combatUnitRight = u2;
}

// There are four types of combat, depending on what the user selected. Each has an associated function

// Aggressive combat mode
void CombatScene::engageCombatTypeOne() {
	myLog->clearText();
	if (combatUnitLeft->CLASSTYPE == SOLDIER) { AI_Soldier_Aggressive(combatUnitLeft, combatUnitRight, myLog); }
	else { AI_Magician_Aggressive(combatUnitLeft, combatUnitRight, myLog); }
}
void CombatScene::engageCombatTypeTwo() {
	myLog->clearText();
	if (combatUnitLeft->CLASSTYPE == SOLDIER) { AI_Soldier_Conservative(combatUnitLeft, combatUnitRight, myLog); }
	else { AI_Magician_Conservative(combatUnitLeft, combatUnitRight, myLog); }
}
void CombatScene::engageCombatTypeThree() {
	myLog->clearText();
	if (combatUnitLeft->CLASSTYPE == SOLDIER) { AI_Soldier_Items(combatUnitLeft, combatUnitRight, myLog); }
	else { AI_Magician_Items(combatUnitLeft, combatUnitRight, myLog); }
}

void CombatScene::engageCombatTypeFour() {
	myLog->clearText();
	if (combatUnitLeft->CLASSTYPE == SOLDIER) { AI_Soldier_Free(combatUnitLeft, combatUnitRight, myLog); }
	else { AI_Magician_Free(combatUnitLeft, combatUnitRight, myLog); }
}

// Get and set the state that the combat is in
int CombatScene::getCombatState() { return combat_state; }
void CombatScene::setCombatState(int s) { combat_state = s; }