#include "Pathfinder.h"
#include <iostream>

using namespace std;

// Constructor
Path::Path() {
	valid = false;
}


// Given a unit's MOV attribute, sets all tiles that can be reached in that number of moves or less
void getValidMoves(int startx, int starty, int mov, BattleMap *BM, int validity[5][5]) {

	// Start by initializing all valid moves as 0 except for the starting space
	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++) {
			validity[j][k] = 0;
		}
	}
	int newvalidity[5][5] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	validity[startx][starty] = 1;

	// Iterate: For all moves I can currently make, see where I can go from there
	// Mark these as a new set of moves reachable in the newvalidity matrix
	for (int step = 0; step < mov; step++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (validity[j][k] == 1) {
					if (j > 0 && !BM->getSolidity(j-1, k) && !BM->isUnitAt(j-1, k)) { newvalidity[j - 1][k] = 1; }
					if (j < 4 && !BM->getSolidity(j + 1, k) && !BM->isUnitAt(j + 1, k)) { newvalidity[j + 1][k] = 1; }
					if (k > 0 && !BM->getSolidity(j, k-1) && !BM->isUnitAt(j, k-1)) { newvalidity[j][k - 1] = 1; }
					if (k < 4 && !BM->getSolidity(j, k+1) && !BM->isUnitAt(j, k+1)) { newvalidity[j][k + 1] = 1; }
				}
			}
		}

		// After iterating through one step ahead, copy all of the new moves I can
		// reach to the original matrix
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (newvalidity[j][k] == 1) {validity[j][k] = newvalidity[j][k]; }
			}
		}

	}

	// And remember, the unit can't move to the square we started on
	validity[startx][starty] = 0;
}

// Modification of getValidMoves, which takes a unit's ATKDIS. Tiles with units on them will be valid
// And the attack can potentially go over solid tiles
void getValidAttacks(int startx, int starty, int atkdis, BattleMap *BM, int validity[5][5]) {

	// Start by initializing all valid moves as 0 except for the starting space
	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++) {
			validity[j][k] = 0;
		}
	}
	int newvalidity[5][5] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	validity[startx][starty] = 1;

	// Iterate: For all moves I can currently make, see where I can go from there
	// Mark these as a new set of moves reachable in the newvalidity matrix
	for (int step = 0; step < atkdis; step++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (validity[j][k] == 1) {
					if (j > 0 ) { newvalidity[j - 1][k] = 1; }
					if (j < 4 ) { newvalidity[j + 1][k] = 1; }
					if (k > 0 ) { newvalidity[j][k - 1] = 1; }
					if (k < 4 ) { newvalidity[j][k + 1] = 1; }
				}
			}
		}

		// After iterating through one step ahead, copy all of the new moves I can
		// reach to the original matrix. Remove the moves that fall on solid tiles
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (newvalidity[j][k] == 1 && !BM->getSolidity(j,k)) { validity[j][k] = newvalidity[j][k]; }
			}
		}

	}

	// And remember, the unit can't move to the square we started on
	validity[startx][starty] = 0;
}

// To be implemented later, time allowing
Path solvePath(int startx, int starty, int endx, int endy, BattleMap *BM) {
	Path P;
	int steps = 0;
	return P;
}