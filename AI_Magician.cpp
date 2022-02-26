#include "AI_Magician.h"
#include "CombatSkill.h"
#include "Inventory.h"
#include "SaveData.h"
#include <iostream>

using namespace std;

// Description
// Unit will perform Fire 75% of the time
// Unit will try to perform Ice 25% of the time
// If it can't perform Ice, it will try to perform Fire, failing that, it attacks
void AI_Magician_Conservative(Unit *attacker, Unit *defender, CombatLog *log) {

	if (attacker->MP >= COST_OF_FIRE) {
		int r = rand() % 101;
		if (r < 75) {
			useFire(attacker, defender, log);
		}

		else {
			string line = attacker->NAME + " can't hold back!";
			log->addText(line);
			if (attacker->MP >= COST_OF_ICE) { useIce(attacker, defender, log); }
			else { useFire(attacker, defender, log); }
		}
	}

	else {
		string line = attacker->NAME + " lacks MP...";
		log->addText(line);
		useSkillAttack(attacker, defender, log);
	}



};

// Use an item at random if there is one
// Otherwise try to cast fire
void AI_Magician_Items(Unit *attacker, Unit *defender, CombatLog *log) {

	if (getLoadedSave()->inventory.getTotalItemCount() == 0) {
		string line = attacker->NAME + " has no items...";
		log->addText(line);
		if (attacker->MP >= COST_OF_FIRE) { useFire(attacker, defender, log); }
		else {
			string line = attacker->NAME + " has no MP...";
			log->addText(line);
			useSkillAttack(attacker, defender, log);
		}
	}

	else {
		int item = getLoadedSave()->inventory.getRandomItem();
		getLoadedSave()->inventory.removeItem(item);
		useItemSkill(attacker, defender, log, item);
	}

};

// Unit will use restore
void AI_Magician_Free(Unit *attacker, Unit *defender, CombatLog *log) {
	useRestore(attacker, defender, log);
};

// Unit will try to use top tier spell 50% of time
// Unit will try to use second tier spell 40% of time
// Unit will try to use third tier spell 10% of time
void AI_Magician_Aggressive(Unit *attacker, Unit *defender, CombatLog *log) {
	int r = rand() % 101;
	
	if (r < 50) {
		if (attacker->MP >= COST_OF_TSUNAMI) { useTsunami(attacker, defender, log); }
		else if (attacker->MP >= COST_OF_STORM) { useStorm(attacker, defender, log); }
		else if (attacker->MP >= COST_OF_ICE) { useIce(attacker, defender, log); }
		else if (attacker->MP >= COST_OF_FIRE) { useFire(attacker, defender, log); }
		else {
			string line = attacker->NAME + " lacks MP...";
			log->addText(line);
			useSkillAttack(attacker, defender, log);
		}
	}

	else if (r >= 50 && r < 90) {
			if (attacker->MP >= COST_OF_STORM) { useStorm(attacker, defender, log); }
			else if (attacker->MP >= COST_OF_ICE) { useIce(attacker, defender, log); }
			else if (attacker->MP >= COST_OF_FIRE) { useFire(attacker, defender, log); }
			else {
				string line = attacker->NAME + " lacks MP...";
				log->addText(line);
				useSkillAttack(attacker, defender, log);
			}
	}

	else {
			if (attacker->MP >= COST_OF_ICE) { useIce(attacker, defender, log); }
			else if (attacker->MP >= COST_OF_FIRE) { useFire(attacker, defender, log); }
			else {
				string line = attacker->NAME + " lacks MP...";
				log->addText(line);
				useSkillAttack(attacker, defender, log);
			}
	}

};
