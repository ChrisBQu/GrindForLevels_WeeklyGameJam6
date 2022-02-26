#pragma once
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <string>

// Class represents a path that a unit will walk, and can be built with the solvePath function
class Path {
public:
	Path();
	bool valid;
	std::vector<int> xvals;
	std::vector<int> yvals;
};

#include "BattleMap.h"

void getValidMoves(int startx, int starty, int mov, BattleMap *BM, int storeAt[5][5]);
void getValidAttacks(int startx, int starty, int atkdis, BattleMap *BM, int storeAt[5][5]);

// The returned path will have its "valid" value equal to false if no path was found
Path solvePath(int startx, int starty, int endx, int endy, BattleMap *BM);


#endif