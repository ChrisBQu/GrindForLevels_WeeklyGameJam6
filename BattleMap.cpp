#include "BattleMap.h"
#include <allegro5/allegro_primitives.h>
#include "Resources.h"
#include "Mouse.h"
#include "Pathfinder.h"
#include "MapMenu.h"
#include <iostream>
#include "Sound.h"
#include "CombatScene.h"
#include "SaveData.h"
#include "GameClass.h"
#include "Sound.h"

using namespace std;

// Time for the AI to be delayed (in seconds) so the user can see their moves
const double AI_TIME_DELAY = 0.4;

// Cannot be a member variable because MapMenu.h includes BattleMap.h
MapMenu *myMenu;

// Variables for tracking mouse as it passes over the map
int cx = -1;
int cy = -1;

// Variables for tracking movement of the units on the map, and the flow of battle
int validmoves[5][5];
bool unitClicked = false;
int AI_Timer;
bool player_moved = false;
bool player_attacked = false;
Unit *last_attacker;
int coins_earned;

// A state machine controls how the BattleMap behaves at a given moment and is tracked with this variable
int control_mode = UNLOADED_BATTLE;

// Constructor
BattleMap::BattleMap() {

	// Initialize default values for map and game
	cursor_x = 0;
	cursor_y = 0;
	AI_Timer = 0;
	coins_earned = 0;
	turn = PLAYER_TURN;
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) { mapSolidity[i] = 0; }
	myBG = NULL;
	selectedUnit = NULL;
	secondSelectedUnit = NULL;
	myPoof = NULL;
	headerText = "";

	// Create the right click menu
	myMenu = new MapMenu(this);
	myMenu->addOption("Move");
	myMenu->addOption("Attack");

	endTurnButton = new DialogButton(END_TURN_BUTTON_X, END_TURN_BUTTON_Y, SMALL_BUTTON, getResourceManager()->getString("END_TURN"));
}

// Add a unit to the map (used during construction of a stage)
void BattleMap::addUnit(Unit *u) { myUnits.push_back(u); }

// Sets the background image of the map (used during construction of a stage)
void BattleMap::setBG(ALLEGRO_BITMAP *bg) { myBG = bg; }
void BattleMap::setImage(ALLEGRO_BITMAP *img) { myMap = img; }
void BattleMap::setHeaderText(string s) { headerText = s; }

// Set the solidity of the stage
// We compress a 2D array of 0s and 1s into a string to build the stage solidity
// Example: 0 0 1 0 0
//          0 0 1 0 0
//          0 0 0 0 0    Becomes:     0010000100000000010000000
//          0 0 1 0 0
//          0 0 0 0 0
void BattleMap::setSolidity(string s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == '0') { mapSolidity[i] = 0; }
		else { mapSolidity[i] = 1; }
	}
}

// Receive a signal from the menu
void BattleMap::processMenuClick(string signal) {

	// User exited menu with right click
	if (signal.compare("RIGHTCLICK") == 0) {
		selectedUnit = NULL;
		secondSelectedUnit = NULL;
		unitClicked = false;
	}

	// User wants to move (can do this once per turn)
	if (signal.compare("Move") == 0) {
		if (player_moved == false) { control_mode = MOVING; }
		else { 
			getSoundPlayer()->playEffect("Resources/Sound/Error.ogg"); 
			selectedUnit = NULL;
			secondSelectedUnit = NULL;
			unitClicked = false;
		}
	}

	// User wants to attack (can do this once per turn)
	if (signal.compare("Attack") == 0) {
		if (player_attacked == false) { control_mode = ATTACKING; }
		else { 
			getSoundPlayer()->playEffect("Resources/Sound/Error.ogg"); 
			selectedUnit = NULL;
			secondSelectedUnit = NULL;
			unitClicked = false;
		}
	}

}

void BattleMap::update() {

	myMenu->update();

	// Check for dead units on the map, and if they exist, remove them
	for (unsigned int i = 0; i < myUnits.size(); i++) {
		if (myUnits.at(i)->HP <= 0) { 
			myPoof = new AnimatedSprite("POOF", MAP_POS_X + myUnits.at(i)->xpos*MAP_TILE_SIZE-4, MAP_POS_Y+myUnits.at(i)->ypos*MAP_TILE_SIZE-4, 25, 25, 5, 9);
			getSoundPlayer()->playEffect("Resources/Sound/Pop.ogg");
			coins_earned = 0;
			if (myUnits.at(i)->enemy_unit) {
				last_attacker->awardEXP(getValuedEXP(myUnits.at(i)->LEVEL));
				coins_earned = rand() % (myUnits.at(i)->LEVEL) + 1;
				delete myUnits.at(i); 
			}
			myUnits.erase(myUnits.begin() + i); 
		}
	}

	// Check for the player clicking "End turn" if it's their turn
	if (turn == PLAYER_TURN) { endTurnButton->update(); }
	if (endTurnButton->isClicked() && control_mode!=FADE_TO_BATTLE) {
		endTurnButton->reset();
		control_mode = SELECTION;
		turn = ENEMY_TURN;
		AI_Timer = AI_TIME_DELAY * getGameClass()->getFPS();
	}
	
	if (myMenu->isOpen() == false) {
		// Update mouse position
		int mx = getMouseX();
		int my = getMouseY();

		// Update cursor position if the mouse is over the map
		if (mx > MAP_POS_X && mx < MAP_POS_X + MAP_TILE_SIZE*MAP_WIDTH && my > MAP_POS_Y && my < MAP_POS_Y + MAP_TILE_SIZE*MAP_HEIGHT) {
			cx = (mx - MAP_POS_X) / 16;
			cy = (my - MAP_POS_Y) / 16;
		}
		else {
			cx = -1;
			cy = -1;
		}

		//-------------------------------------------------------------------------
		// Player is selecting a unit
		//-------------------------------------------------------------------------
		if (control_mode == SELECTION && turn == PLAYER_TURN) {

			// Update the selected unit if there is one
			if (!unitClicked) { selectedUnit = NULL; }
			secondSelectedUnit = NULL;
			for (Unit *each : myUnits) {
				if (cx == each->xpos && cy == each->ypos) {
					if (!unitClicked) { selectedUnit = each; }
					else { secondSelectedUnit = each; }
				}
			}

			// If a unit is selected, update the list of valid moves it could make (so tiles can be highlighted)
			if (selectedUnit != NULL) {
				getValidMoves(selectedUnit->xpos, selectedUnit->ypos, selectedUnit->MOV, this, validmoves);
				if (getMouseClicked() && selectedUnit->enemy_unit == false && control_mode == SELECTION) {
					unitClicked = true;
					myMenu->setPos(getMouseX(), getMouseY());
					myMenu->open();
				}
			}
		}

		//-------------------------------------------------------------------------
		// Enemy is selecting a unit
		//-------------------------------------------------------------------------
		if (control_mode == SELECTION && turn == ENEMY_TURN && AI_Timer == 0) {

			// Get the list of enemy units to consider
			vector<Unit*> enemyUnits;
			for (Unit *each : myUnits) {
				if (each->enemy_unit) { enemyUnits.push_back(each); }
			}

			// Cnly consider those units that have a valid move to make
			vector<Unit*> validUnits;
			for (Unit *each : enemyUnits) {
				getValidMoves(each->xpos, each->ypos, each->MOV, this, validmoves);
				bool validUnit = false;
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (validmoves[j][k] == 1) { validUnit = true; }
					}
				}
				if (validUnit) { validUnits.push_back(each); }
			}

			// Pick one of the units that has a valid move, otherwise pick null
			selectedUnit = NULL;
			if (validUnits.size() != 0) {
				int r = rand() % validUnits.size();
				selectedUnit = validUnits.at(r);
			}

			control_mode = MOVING;
			AI_Timer = AI_TIME_DELAY * getGameClass()->getFPS();

		}

		//-------------------------------------------------------------------------
		// Player is selecting how to move a unit
		//-------------------------------------------------------------------------
		if (control_mode == MOVING && turn == PLAYER_TURN) {

			// Player cancels out of the MOVING mode
			if (getMouseRightClicked()) {
				control_mode = SELECTION;
				unitClicked = false;
				selectedUnit = NULL;
				secondSelectedUnit = NULL;
			}

			// Player chooses a square to move to
			else if (getMouseClicked()) {
				// The click willl only count if the move is valid
				if (validmoves[cx][cy]) {
					control_mode = SELECTION;
					unitClicked = false;
					selectedUnit->xpos = cx;
					selectedUnit->ypos = cy;
					player_moved = true;
					selectedUnit = NULL;
					secondSelectedUnit = NULL;
				}
				// Play a sound effect if they make an invalid move
				else { getSoundPlayer()->playEffect("Resources/Sound/Error.ogg"); }
			}

		}

		//-------------------------------------------------------------------------
		// Enemy is selecting how to move a unit
		//-------------------------------------------------------------------------
		if (control_mode == MOVING && turn == ENEMY_TURN && AI_Timer == 0) { 


			// If there's no selected unit, then there's no moving, so skip this phase
			if (selectedUnit == NULL) { 
				control_mode = ATTACKING; 
				AI_Timer = AI_TIME_DELAY * getGameClass()->getFPS();
			}

			// Otherwise, see if the unit can approach one of the player's units
			else {

				int chosenx = -1;
				int choseny = -1;

				// Get the list of player units to consider
				vector<Unit*> playerUnits;
				for (Unit * each : myUnits) {
					if (each->enemy_unit == false) { playerUnits.push_back(each); }
				}


				// Search for a move that will put the enemy near a player, if possible
				bool foundMove = false;
				getValidMoves(selectedUnit->xpos, selectedUnit->ypos, selectedUnit->MOV, this, validmoves);
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (validmoves[j][k] == 1) {
							for (Unit *each : playerUnits) {
								if (each->enemy_unit == false) {
									if ((j > 0 && j - 1 == each->xpos && k == each->ypos) ||
										(j < 4 && j + 1 == each->xpos && k == each->ypos) ||
										(j == each->xpos && k > 0 && k - 1 == each->ypos) ||
										(j == each->xpos && k < 4 && k + 1 == each->ypos)) {
										chosenx = j;
										choseny = k;
										foundMove = true;
									}
								}
							}
						}
					}
				}

				// Otherwise make a move that approaches a player
				if (foundMove == false) {
					// Start by checking the current minimum distance amongst all player units
					int curMinDistance = 9999;
					int origMinDistance = 9999;
					for (Unit *each : playerUnits) {
						int dist = pow(pow(each->xpos - selectedUnit->xpos, 2) + pow(each->ypos - selectedUnit->ypos, 2), 0.5);
						if (dist < curMinDistance) {
							curMinDistance = dist;
							origMinDistance = dist;
						}
					}

					// Then, see if the movement can decrease this. 
					for (int j = 0; j < 5; j++) {
						for (int k = 0; k < 5; k++) {
							if (validmoves[j][k] == 1) {
								for (Unit *each : playerUnits) {
									int dist = pow(pow(each->xpos - j, 2) + pow(each->ypos - k, 2), 0.5);
									if (dist < curMinDistance) {
										curMinDistance = dist;
										chosenx = j;
										choseny = k;
									}
								}
							}
						}
					}
				}

				// If it can't, then don't make a move. Otherwise, make the best move found
				if (chosenx != -1 && choseny != -1) {
					selectedUnit->xpos = chosenx;
					selectedUnit->ypos = choseny;
				}

				// Either way, continue to the attacking phase
				control_mode = ATTACKING;
				AI_Timer = AI_TIME_DELAY * getGameClass()->getFPS();
			}

		
		}

		//-------------------------------------------------------------------------
		// Player is selecting how to attack with unit
		//-------------------------------------------------------------------------
		if (control_mode == ATTACKING && turn == PLAYER_TURN) {

			getValidAttacks(selectedUnit->xpos, selectedUnit->ypos, selectedUnit->ATKDIS, this, validmoves);

			// Player is hovering over a unit to attack
			secondSelectedUnit = NULL;
			for (Unit *each : myUnits) {
				if (cx == each->xpos && cy == each->ypos && each != selectedUnit) {
					secondSelectedUnit = each;
				}
			}

			// Player cancels out of the MOVING mode
			if (getMouseRightClicked()) {
				control_mode = SELECTION;
				unitClicked = false;
				selectedUnit = NULL;
				secondSelectedUnit = NULL;
			}

			// Player chooses a square to move to
			else if (getMouseClicked()) {
				// The click willl only count if the move is valid
				if (validmoves[cx][cy] && isUnitAt(cx,cy)) {
					control_mode = SELECTION;
					unitClicked = false;
					setBattleBG(myBG);
					Unit *attacked = NULL;
					for (Unit *each : myUnits) {
						if (each->xpos == cx && each->ypos == cy) { attacked = each; }
					}
					setCombatUnits(selectedUnit, attacked);
					control_mode = FADE_TO_BATTLE;
					player_attacked = true;
					getSoundPlayer()->playEffect("Resources/Sound/Clash.ogg");
					last_attacker = selectedUnit;
					selectedUnit = NULL;
					secondSelectedUnit = NULL;
				}
				// Play a sound effect if they make an invalid move
				else { getSoundPlayer()->playEffect("Resources/Sound/Error.ogg"); }
			}

		}

		//-------------------------------------------------------------------------
		// Enemy is selecting how to attack with unit
		//-------------------------------------------------------------------------

		if (control_mode == ATTACKING && turn == ENEMY_TURN && AI_Timer == 0) {

			// Get the list of enemy units to consider
			vector<Unit*> enemyUnits;
			for (Unit *each : myUnits) {
				if (each->enemy_unit) { enemyUnits.push_back(each); }
			}

			// Cnly consider those units that have a valid attack to make
			vector<Unit*> validUnits;
			for (Unit *each : enemyUnits) {
				getValidAttacks(each->xpos, each->ypos, each->ATKDIS, this, validmoves);
				bool validUnit = false;
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (validmoves[j][k] == 1) { 
							for (Unit *each : myUnits) {
								if (each->enemy_unit == false && each->xpos == j && each->ypos == k) {
									validUnit = true;
								}
							}
						}
					}
				}
				if (validUnit) { validUnits.push_back(each); }
			}

			// Pick one of the units that has a valid move, otherwise pick null
			selectedUnit = NULL;
			if (validUnits.size() != 0) {
				int r = rand() % validUnits.size();
				selectedUnit = validUnits.at(r);
			}

			// Get the list of possible attacks
			secondSelectedUnit = NULL;
			if (selectedUnit != NULL) {

				getValidAttacks(selectedUnit->xpos, selectedUnit->ypos, selectedUnit->ATKDIS, this, validmoves);

				// Search for the attack
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (validmoves[j][k] == 1) {
							for (Unit *each : myUnits) {
								if (each->enemy_unit == false) {
									if (j == each->xpos && k == each->ypos) {
										secondSelectedUnit = each;
									}
								}
							}
						}
					}
				}
			}

			// Make the attack if one was found
			if (secondSelectedUnit != NULL) {
				setCombatUnits(selectedUnit, secondSelectedUnit);
				control_mode = FADE_TO_BATTLE;
				getSoundPlayer()->playEffect("Resources/Sound/Clash.ogg");
				last_attacker = selectedUnit;
			}

			// If no attack was found, then skip combat
			else { control_mode = SELECTION; }

			// Either way, it will then go back to the player's turn
			turn = PLAYER_TURN;
			player_moved = false;
			player_attacked = false;
			selectedUnit = NULL;
			secondSelectedUnit = NULL;
		
		}

		//-----------------------------------

	}

}

// Draw the map
void BattleMap::render() {

	// Tick down the AI timer
	if (AI_Timer > 0) { AI_Timer--; }

	// Draw the map background
	if (myBG != NULL) {
		al_draw_bitmap(myMap, MAP_POS_X, MAP_POS_Y, 0);
	}

	// Draw the higlighted square if one exists
	if (cx != -1 && cy != -1) {
		al_draw_filled_rectangle(MAP_POS_X + cx*MAP_TILE_SIZE, MAP_POS_Y + cy*MAP_TILE_SIZE, MAP_POS_X + cx*MAP_TILE_SIZE + 15,
			MAP_POS_Y + cy*MAP_TILE_SIZE + 15, al_map_rgba(100, 100, 255, 40));

	}

	// If a unit is selected, highlight the squares it can move to
	if (selectedUnit != NULL && myMenu->isOpen() == false && turn == PLAYER_TURN) {
		for (int j = 0; j < MAP_WIDTH*MAP_HEIGHT; j++) {
			int row = j % MAP_WIDTH;
			int col = j / MAP_HEIGHT;
			if (validmoves[col][row] == 1) {
				al_draw_filled_rectangle(MAP_POS_X + col*MAP_TILE_SIZE, MAP_POS_Y + row*MAP_TILE_SIZE, MAP_POS_X + col*MAP_TILE_SIZE + 15,
					MAP_POS_Y + row*MAP_TILE_SIZE + 15, al_map_rgba(255, 100, 100, 40));
			}
		}
	}

	// Draw the map grid on top of the map
	for (int j = 0; j < MAP_WIDTH; j++) {
		for (int k = 0; k < MAP_HEIGHT; k++) {
			al_draw_line(MAP_POS_X + j*MAP_TILE_SIZE, MAP_POS_Y - 1, MAP_POS_X + j*MAP_TILE_SIZE, MAP_POS_Y + MAP_TILE_SIZE * MAP_HEIGHT,
				al_map_rgba(0, 0, 0, 10), 1);
			al_draw_line(MAP_POS_X, MAP_POS_Y + k*MAP_TILE_SIZE, MAP_POS_X + MAP_TILE_SIZE * MAP_HEIGHT, MAP_POS_Y + k*MAP_TILE_SIZE,
				al_map_rgba(0, 0, 0, 10), 1);
		}
	}

	// Draw the frame around the map
	al_draw_rectangle(MAP_POS_X, MAP_POS_Y, MAP_POS_X + MAP_TILE_SIZE * MAP_WIDTH, MAP_POS_Y + MAP_TILE_SIZE * MAP_HEIGHT, al_map_rgb(0, 0, 0), 1);

	// Draw units on the map
	for (Unit *each : myUnits) {
		al_draw_bitmap_region(getResourceManager()->getImage("UNIT_ICONS"), 16 * each->CLASSTYPE, 16 * each->enemy_unit, 16, 16,
			MAP_POS_X + each->xpos * MAP_TILE_SIZE, MAP_POS_Y + each->ypos * MAP_TILE_SIZE, 0);
	}

	// Render the "poof" if a unit is dead
	// Also note: because the match can only end when the last unit has died,
	// we can check for it here as well.
	if (myPoof != NULL) {
		myPoof->render();
		if (myPoof->isDone()) {
			delete myPoof;
			myPoof = NULL;
			if (coins_earned != 0) {
				getSoundPlayer()->playEffect("Resources/Sound/Coin.ogg");
				getLoadedSave()->coins += coins_earned;
			}
			// Check for the player losing (no player units left alive)
			bool livingPlayer = false;
			for (Unit *each : myUnits) {
				if (each->enemy_unit == false) { livingPlayer = true; }
			}
			if (livingPlayer == false) { control_mode = FADE_TO_LOSS; }

			// Check for the player winning (no enemy units left alive)
			bool livingEnemy = false;
			for (Unit *each : myUnits) {
				if (each->enemy_unit) { livingEnemy = true; }
			}
			if (livingEnemy == false) { control_mode = FADE_TO_WIN; }
		}

	}

	if (turn == PLAYER_TURN) { endTurnButton->render(); }

	myMenu->render();

}

// Clear all units off of map
void BattleMap::clearUnits() {
	for (Unit *each : myUnits) {
		delete each;
	}
	myUnits.clear();
}

// Getters for map attributes
Unit *BattleMap::getSelectedUnit() { return selectedUnit; }
Unit *BattleMap::getSecondSelectedUnit() { return secondSelectedUnit; }
ALLEGRO_BITMAP *BattleMap::getBG() { return myBG; }
string BattleMap::getHeaderText() { return headerText; }

// Get and set the control state of the map
int BattleMap::getControlState() { return control_mode; }
void BattleMap::setControlState(int s) { control_mode = s; }

// Get solidity of a certain tile
bool BattleMap::getSolidity(int x, int y) { return mapSolidity[y*MAP_WIDTH + x]; }

// Check if a tile has a unit on it
bool BattleMap::isUnitAt(int x, int y) {
	for (Unit *each : myUnits) {
		if (each->xpos == x && each->ypos == y) { return true; }
	}
	return false;
}

// Reset all values for the map
void BattleMap::reset() {
	clearUnits();
	control_mode = UNLOADED_BATTLE;
	selectedUnit = NULL;
	secondSelectedUnit = NULL;
	player_attacked = false;
	player_moved = false;
}