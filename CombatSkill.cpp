#include "CombatSkill.h"
#include <algorithm>
#include "Inventory.h"

using namespace std;

// Constants used in damage formulas
const double ATK_STAT_WEIGHT = 1.35;
const double DEF_STAT_WEIGHT = 0.25;
const double CRITICAL_HIT_MULTIPLIER = 1.25;

// Basic attack
void useSkillAttack(Unit *attacker, Unit *defender, CombatLog *log) {

	// First show the original attack
	string line = "";
	line = attacker->NAME + " attacks.";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "It's a direct hit!";
		log->addText(line);
		critical_multiplier = CRITICAL_HIT_MULTIPLIER;
	}

	// If speed is more than double the defender's speed, attack a second time
	int double_attack_multiplier = 1;
	if (attacker->SPD >= defender->SPD * 2) {
		line = attacker->NAME + " attacks again!";
		log->addText(line);
		double_attack_multiplier = 2;
	}

	// Calculate the final damage, show it, and apply it to the defender
	for (int i = 0; i < double_attack_multiplier; i++) {
		double randmultiplier = (rand() % 50 + 1000) / 1000.0;
		int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (defender->DEF * DEF_STAT_WEIGHT))));
		line = defender->NAME + " takes " + to_string(dmg) + " damage.";
		log->addText(line);
		defender->takeDamage(dmg);
	}

}

// Power Slash
// Deals twice the damage of a regular attack, but cannot attack twice or crit
void usePowerSlash(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_POWER_SLASH);

	// First show the original attack
	string line = "";
	line = attacker->NAME + " uses Power Slash!";
	log->addText(line);

	// Calculate the final damage, show it, and apply it to the defender
	double randmultiplier = (rand() % 50 + 1000) / 1000.0;
	int dmg = (int)(randmultiplier + 2.0 * max(1,(int)(attacker->STR*ATK_STAT_WEIGHT) - (int)(defender->DEF * DEF_STAT_WEIGHT)));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

}

// Wind Blade
// Deals damage using target's MND instead of DEF if MND < DEF
void useWindBlade(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_POWER_SLASH);

	// First show the original attack
	string line = "";
	line = attacker->NAME + " uses Wind Blade!";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "It's a direct hit!";
		log->addText(line);
		critical_multiplier = 1.25;
	}

	// If speed is more than double the defender's speed, attack a second time
	int double_attack_multiplier = 1;
	if (attacker->SPD >= defender->SPD * 2) {
		line = attacker->NAME + " attacks again!";
		log->addText(line);
		double_attack_multiplier = 2;
	}

	// Calculate the final damage, show it, and apply it to the defender
	for (int i = 0; i < double_attack_multiplier; i++) {
		double randmultiplier = (rand() % 50 + 1000) / 1000.0;
		int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (min(defender->MND, defender->DEF) * DEF_STAT_WEIGHT))));
		line = defender->NAME + " takes " + to_string(dmg) + " damage.";
		log->addText(line);
		defender->takeDamage(dmg);
	}

}

// Tornado Slash
// Deals four hits, each which ranges in power from 0.25 to 1.25 a regular attack
void useTornadoSlash(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_TORNADO_SLASH);

	// First show the original attack
	string line = "";
	line = attacker->NAME + " uses Tornado Slash!";
	log->addText(line);

	// First hit
	double multiplier = (rand()%100 + 25) / 100.0;
	int dmg = (int)(multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (defender->DEF * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

	// Second hit
	multiplier = (rand() % 100 + 25) / 100.0;
	dmg = (int)(multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (defender->DEF * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

	// Third hit
	multiplier = (rand() % 100 + 25) / 100.0;
	dmg = (int)(multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (defender->DEF * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

	// Fourth hit
	multiplier = (rand() % 100 + 25) / 100.0;
	dmg = (int)(multiplier * max(1, (int)((attacker->STR*ATK_STAT_WEIGHT) - (defender->DEF * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);
}

// Fire
// Magic attack using INT and MND instead of STR and DEF
void useFire(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_FIRE);

	string line = attacker->NAME + " casts Fire!";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "The spell flares!";
		log->addText(line);
		critical_multiplier = CRITICAL_HIT_MULTIPLIER;
	}

	// Calculate the final damage, show it, and apply it to the defender
	double randmultiplier = (rand() % 50 + 1000) / 1000.0;
	int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->INT*ATK_STAT_WEIGHT) - (defender->MND * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

}

// Restore
// Unit restores all MP
void useRestore(Unit *attacker, Unit *defender, CombatLog *log) {
	string line = attacker->NAME + " casts Restore!";
	log->addText(line);
	int difmp = attacker->MAXMP - attacker->MP;
	line = attacker->NAME + " gains " + to_string(difmp) + " MP!";
	log->addText(line);
}

//  Ice
// Same as fire, but also lowers SPD stat of defender
void useIce(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_ICE);

	string line = attacker->NAME + " casts Ice!";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "The spell crystalizes!";
		log->addText(line);
		critical_multiplier = CRITICAL_HIT_MULTIPLIER;
	}

	// Calculate the final damage, show it, and apply it to the defender
	double randmultiplier = (rand() % 50 + 1000) / 1000.0;
	int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->INT*ATK_STAT_WEIGHT) - (defender->MND * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

	// Calculate the speed loss
	int r = rand() % 6;
	line = defender->NAME + " loses " + to_string(r) + " SPD!";
	defender->SPD -= r;
	log->addText(line);
	if (defender->SPD < 1) { defender->SPD = 1; }

}

//  Storm
// A stronger magic attack. If it crits, the target loses MND
void useStorm(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_STORM);
	string line = attacker->NAME + " casts Storm!";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "The sky darkens!";
		log->addText(line);
		critical_multiplier = CRITICAL_HIT_MULTIPLIER;
	}

	// Calculate the final damage, show it, and apply it to the defender
	double randmultiplier = (rand() % 50 + 1000) / 1000.0;
	int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->INT*ATK_STAT_WEIGHT*2) - (defender->MND * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

	// Calculate MND loss
	if (critical_multiplier == CRITICAL_HIT_MULTIPLIER) {
		int r = rand() % 6;
		line = defender->NAME + " loses " + to_string(r) + " MND!";
		log->addText(line);
		defender->MND -= r;
		if (defender->MND < 1) { defender->MND = 1; }
	}

}

//  Tsunami
// A much stronger magic attack
void useTsunami(Unit *attacker, Unit *defender, CombatLog *log) {

	attacker->takeMP(COST_OF_TSUNAMI);
	string line = attacker->NAME + " casts Tsunami!";
	log->addText(line);

	// A critical hit is based on pure chance. 10%.
	double critical_multiplier = 1.0;
	if (rand() % 100 >= 90) {
		line = "Everything is washed away!";
		log->addText(line);
		critical_multiplier = CRITICAL_HIT_MULTIPLIER;
	}

	// Calculate the final damage, show it, and apply it to the defender
	double randmultiplier = (rand() % 50 + 1000) / 1000.0;
	int dmg = (int)(randmultiplier * critical_multiplier * max(1, (int)((attacker->INT*ATK_STAT_WEIGHT * 3.5) - (defender->MND * DEF_STAT_WEIGHT))));
	line = defender->NAME + " takes " + to_string(dmg) + " damage.";
	log->addText(line);
	defender->takeDamage(dmg);

}

// Guard Break
// Lowers target's defense by half
void useGuardBreak(Unit *attacker, Unit *defender, CombatLog *log) {

	// First show the original attack
	string line = attacker->NAME + " uses Shield Break!";
	log->addText(line);

	// Calculate the final damage, show it, and apply it to the defender
	int defloss = (int)((defender->DEF) / 2);
	line = defender->NAME + " loses " + to_string(defloss) + " DEF!";
	defender->DEF /= 2;
	log->addText(line);

}

// Item Skills
// Effects are different for each item
void useItemSkill(Unit *attacker, Unit *defender, CombatLog *log, int item) {

	// Kunai
	if (item == KUNAI) {
		string line = attacker->NAME + " throws a Kunai!";
		log->addText(line);
		int dmg = (int)(max(1, (int)(20*ATK_STAT_WEIGHT) - (int)(defender->DEF * DEF_STAT_WEIGHT)));
		line = defender->NAME + " takes " + to_string(dmg) + " damage.";
		log->addText(line);
		defender->takeDamage(dmg);
	}

	// Shuriken
	if (item == SHURIKEN) {
		string line = attacker->NAME + " throws a Shuriken!";
		log->addText(line);
		int dmg = (int)(max(1, (int)(40 * ATK_STAT_WEIGHT) - (int)(defender->DEF * DEF_STAT_WEIGHT)));
		line = defender->NAME + " takes " + to_string(dmg) + " damage.";
		log->addText(line);
		defender->takeDamage(dmg);
	}

	if (item == FIREBOMB) {
		string line = attacker->NAME + " throws a Fire Bomb!";
		log->addText(line);
		int dmg = (int)(max(1, (int)(30 * ATK_STAT_WEIGHT) - (int)(defender->MND * DEF_STAT_WEIGHT)));
		line = defender->NAME + " takes " + to_string(dmg) + " fire damage.";
		log->addText(line);
		defender->takeDamage(dmg);
	}

	if (item == ICE_RAY) {
		string line = attacker->NAME + " fires an Ice Ray!";
		log->addText(line);
		int dmg = (int)(max(1, (int)(25 * ATK_STAT_WEIGHT) - (int)(defender->MND * DEF_STAT_WEIGHT)));
		line = defender->NAME + " takes " + to_string(dmg) + " ice damage.";
		log->addText(line);
		int spd_drop = rand() % 6;
		line = defender->NAME + " loses " + to_string(spd_drop) + " SPD!";
		log->addText(line);
		defender->takeDamage(dmg);
		defender->SPD -= spd_drop;
		if (defender->SPD < 1) { defender->SPD = 1; }
	}

	if (item == SPEED_DRINK) {
		string line = attacker->NAME + " drinks a Speed Drink!";
		log->addText(line);
		line = attacker->NAME + " gains " + to_string(attacker->SPD) + " SPD!";
		log->addText(line);
		attacker->SPD *= 2;
	}



}