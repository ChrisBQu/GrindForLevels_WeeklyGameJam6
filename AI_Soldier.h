#pragma once
#ifndef AI_SOLDIER_H
#define AI_SOLDIER_H

#include "Unit.h"
#include "CombatLog.h"

// Four combat types for Soldier

void AI_Soldier_Conservative(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Soldier_Items(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Soldier_Free(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Soldier_Aggressive(Unit *attacker, Unit *defender, CombatLog *log);

#endif