#pragma once
#ifndef COMBAT_SKILL_H
#define COMBAT_SKILL_H

#include "Unit.h"
#include "CombatLog.h"

// Soldier skill costs (and basic attack is free)
const int COST_OF_POWER_SLASH = 8;
const int COST_OF_WIND_BLADE = 3;
const int COST_OF_TORNADO_SLASH = 16;

// Magician skill costs
const int COST_OF_FIRE = 2;
const int COST_OF_ICE = 4;
const int COST_OF_STORM = 8;
const int COST_OF_TSUNAMI = 20;

void useSkillAttack(Unit *attacker, Unit *defender, CombatLog *log);
void useItemSkill(Unit *attacker, Unit *defender, CombatLog *log, int item);

// Soldier Skills
void usePowerSlash(Unit *attacker, Unit *defender, CombatLog *log);
void useTornadoSlash(Unit *attacker, Unit *defender, CombatLog *log);
void useWindBlade(Unit *attacker, Unit *defender, CombatLog *log);
void useGuardBreak(Unit *attacker, Unit *defender, CombatLog *log);

// Magician Skills
void useFire(Unit *attacker, Unit *defender, CombatLog *log);
void useIce(Unit *attacker, Unit *defender, CombatLog *log);
void useStorm(Unit *attacker, Unit *defender, CombatLog *log);
void useTsunami(Unit *attacker, Unit *defender, CombatLog *log);
void useRestore(Unit *attacker, Unit *defender, CombatLog *log);

#endif