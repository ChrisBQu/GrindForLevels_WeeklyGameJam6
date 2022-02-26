#include "AI_Soldier.h"
#include "CombatSkill.h"
#include "Inventory.h"
#include "SaveData.h"

using namespace std;

// Description
// Unit will perform a basic attack 67% of the time
// Otherwise it will try to use a skill: 30% of the time, Power Slash, 70% of the tim Wind Blade
// Unit will attack if all else fails.
void AI_Soldier_Conservative(Unit *attacker, Unit *defender, CombatLog *log) {

	int choice = rand() % 101;
	
	// Use skill
	if (choice < 33) {
		choice = rand() % 101;
		string line = attacker->NAME + " is restless...";
		log->addText(line);
		if (attacker->MP > COST_OF_POWER_SLASH && choice < 30) { usePowerSlash(attacker, defender, log); }
		else if (attacker->MP > COST_OF_WIND_BLADE ) { useWindBlade(attacker, defender, log); }
		else {
			string line = attacker->NAME + " lacks MP...";
			log->addText(line);
			useSkillAttack(attacker, defender, log);
		}
	}

	// Use a basic attack
	else {
		useSkillAttack(attacker, defender, log);
	}

};

// Description:
// Uses an item at random if there is one
// Unit will attack otherwise
void AI_Soldier_Items(Unit *attacker, Unit *defender, CombatLog *log) {

	if (getLoadedSave()->inventory.getTotalItemCount() == 0) {
		string line = attacker->NAME + " has no items...";
		log->addText(line);
		useSkillAttack(attacker, defender, log);
	}

	else {
		int item = getLoadedSave()->inventory.getRandomItem();
		getLoadedSave()->inventory.removeItem(item);
		useItemSkill(attacker, defender, log, item);
	}


};

// Description:
// Uses soldier's special ability: Guard Break
void AI_Soldier_Free(Unit *attacker, Unit *defender, CombatLog *log) {
	useGuardBreak(attacker, defender, log);
};

// Description:
// Unit will perform the most expensive skill it can 40% of the time
// Unit will perform the second most expensive skill it can 40% of time
// Unit will perform the third most expensive skill it can 20% of the time
// Unit will attack if all else fails
void AI_Soldier_Aggressive(Unit *attacker, Unit *defender, CombatLog *log) {

	int choice = rand() % 101;

	// Most expensive
	if (choice < 40) {
		if (attacker->MP > COST_OF_TORNADO_SLASH) { useTornadoSlash(attacker, defender, log); }
		else if (attacker->MP > COST_OF_POWER_SLASH) { usePowerSlash(attacker, defender, log); }
		else if (attacker->MP > COST_OF_WIND_BLADE) { useWindBlade(attacker, defender, log); }
		else {
			string line = attacker->NAME + " lacks MP...";
			log->addText(line);
			useSkillAttack(attacker, defender, log);
		}
	}

	// Next most expensive
	else if (choice > 40 && choice < 80) {
		if (attacker->MP > COST_OF_POWER_SLASH && attacker->MP > COST_OF_TORNADO_SLASH) { usePowerSlash(attacker, defender, log); }
		else if (attacker->MP > COST_OF_WIND_BLADE && attacker->MP > COST_OF_POWER_SLASH) { useWindBlade(attacker, defender, log); }
		else {
			string line = attacker->NAME + " lacks MP...";
			log->addText(line);
			useSkillAttack(attacker, defender, log);
		}
	}

	else {
		string line = attacker->NAME + " is acting wildly!";
		log->addText(line);
		useSkillAttack(attacker, defender, log);
	}


};
