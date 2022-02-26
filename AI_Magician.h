#pragma once
#ifndef AI_MAGICIAN_H
#define AI_MAGICIAN_H

#include "Unit.h"
#include "CombatLog.h"

// Four combat types for Soldier

void AI_Magician_Conservative(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Magician_Items(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Magician_Free(Unit *attacker, Unit *defender, CombatLog *log);
void AI_Magician_Aggressive(Unit *attacker, Unit *defender, CombatLog *log);

#endif