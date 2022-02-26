#include "Unit.h"
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Default average stats for all classes
const int DEFAULT_AVERAGE_STATS[9 * NUMBER_OF_CLASSES] = {
	//HP, MP, STR, DEF, INT, MND, SPD, MOV, ATKDIS
	20, 6, 7, 6, 3, 5, 6, 2, 1, // Soldier
	16, 8, 3, 3, 8, 4, 6, 2, 2 // Magician
};

// Constructor takes int based on unit type
Unit::Unit(int unit_type, int enemy) {

	NAME = "NoName";
	CLASSTYPE = unit_type;
	LEVEL = 1;
	EXP = 0;

	// Set up generators for standard deviation based rng
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);

	// Generate HP
	normal_distribution<double> HP_Distribution(DEFAULT_AVERAGE_STATS[unit_type * 9], DEFAULT_AVERAGE_STATS[unit_type * 9] * 0.1);
	HP = max(1, (int)HP_Distribution(generator));
	MAXHP = HP;

	// Generate MP
	normal_distribution<double> MP_Distribution(DEFAULT_AVERAGE_STATS[unit_type * 9 + 1], DEFAULT_AVERAGE_STATS[unit_type * 9 + 1] * 0.1);
	MP = max(0, (int)MP_Distribution(generator));
	MAXMP = MP;

	// Generate stats
	normal_distribution<double> Stat_Distribution(0, 2);
	STR = max(1, DEFAULT_AVERAGE_STATS[unit_type * 9 + 2] + (int)Stat_Distribution(generator));
	DEF = max(1, DEFAULT_AVERAGE_STATS[unit_type * 9 + 3] + (int)Stat_Distribution(generator));
	INT = max(1, DEFAULT_AVERAGE_STATS[unit_type * 9 + 4] + (int)Stat_Distribution(generator));
	MND = max(1, DEFAULT_AVERAGE_STATS[unit_type * 9 + 5] + (int)Stat_Distribution(generator));
	SPD = max(1, DEFAULT_AVERAGE_STATS[unit_type * 9 + 6] + (int)Stat_Distribution(generator));
	MOV = DEFAULT_AVERAGE_STATS[unit_type * 9 + 7];
	ATKDIS = DEFAULT_AVERAGE_STATS[unit_type * 9 + 8];

	selected = false;
	enemy_unit = enemy;

	// If the unit has a parent link, it means this unit is a copy used in battle.
	// When it levels up in battle, the parent (the original unit) should then level up outside of battle.
	parentLink = NULL;

}

// Level the unit up, and increase its stats accordingly
void Unit::levelUp() {

	if (LEVEL < MAXIMUM_LEVEL) {

		LEVEL++;

		HP += (int) (DEFAULT_AVERAGE_STATS[CLASSTYPE * 9] * (((rand() % 20) + 30) / 100.0));
		MP += (int) (DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 1] * (((rand() % 20) + 30) / 100.0));
		MAXHP = HP;
		MAXMP = MP;

		STR = STR + max(1, DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 2] / 2) + (rand() % 2);
		DEF = DEF + max(1, DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 3] / 2) + (rand() % 2);
		INT = INT + max(1, DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 4] / 2) + (rand() % 2);
		MND = MND + max(1, DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 5] / 2) + (rand() % 2);
		SPD = SPD + max(1, DEFAULT_AVERAGE_STATS[CLASSTYPE * 9 + 6] / 2) + (rand() % 2);
	}

}

// Function levels unit up to a specified level
void Unit::levelTo(int lvlto) {
	while (LEVEL < lvlto) { levelUp(); } 
}

// Functions for taking damage and MP from a unit
void Unit::takeDamage(int dmg) {
	HP -= dmg;
	if (HP < 0) { HP = 0; }
}

void Unit::takeMP(int amount) {
	MP -= amount;
	if (MP < 0) { MP = 0; }
}

// Copy stats from one unit to another
void copyUnitStats(Unit *from, Unit *to) {
	to->HP = from->HP;
	to->MAXHP = from->MAXHP;
	to->MP = from->MP;
	to->MAXMP = from->MAXMP;
	to->STR = from->STR;
	to->DEF = from->DEF;
	to->INT = from->INT;
	to->MND = from->MND;
	to->SPD = from->SPD;
	to->ATKDIS = from->ATKDIS;
	to->MOV = from->MOV;
	to->LEVEL = from->LEVEL;
	to->CLASSTYPE = from->CLASSTYPE;
	to->NAME = from->NAME;
};

// Helper function: get amount of exp needed at a given level, to level up
int getNeededEXP(int lvl) { return (int)(2.8 * pow(2.3, 0.45*lvl)); }

// Helper function: get the amount of EXP killing a unit of a certain level is worth
int getValuedEXP(int lvl) { return (int)(pow(lvl, 1.85) + lvl*2.5 - 1.5); }

// Grant EXP to the unit, potentially causing it to level up
void Unit::awardEXP(int val) {
	EXP += val;
	while (EXP >= getNeededEXP(LEVEL)) {
		EXP -= getNeededEXP(LEVEL);
		levelUp();
	}
	if (parentLink != NULL) { parentLink->awardEXP(val); }
}