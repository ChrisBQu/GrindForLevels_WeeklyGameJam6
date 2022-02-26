#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>

enum CLASS_NAMES { SOLDIER, MAGICIAN, NUMBER_OF_CLASSES };

const std::string UNIT_CLASS_NAMES[] = { "Soldier", "Magician" };

// Class represents units on the battlefield

const int MAXIMUM_LEVEL = 99;

class Unit {
public:
	Unit(int unit_type, int enemy);

	// Unit stats
	std::string NAME;
	int CLASSTYPE;
	int LEVEL;
	int MOV;
	int HP; int MAXHP;
	int MP; int MAXMP;
	int STR;
	int DEF; 
	int INT; 
	int MND;
	int SPD;
	int ATKDIS;
	int EXP;
	void awardEXP(int val);
	void levelUp();
	void levelTo(int lvlto);

	void takeDamage(int dmg);
	void takeMP(int amount);

	Unit *parentLink;

	// Unit placement on map
	bool selected;
	int enemy_unit;
	int xpos;
	int ypos;
};

void copyUnitStats(Unit *from, Unit *to);
int getNeededEXP(int lvl);
int getValuedEXP(int lvl);

#endif