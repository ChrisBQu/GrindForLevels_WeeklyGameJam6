#pragma once
#ifndef STAGES_H
#define STAGES_H

#include "BattleMap.h"

// Function unloads resources loaded during stage creation
void unbuildStage(BattleMap *BM);

// Functions build the given stages onto the BattleMap passed as an argument
void buildStageOne(BattleMap *BM);
void buildStageTwo(BattleMap *BM);
void buildStageThree(BattleMap *BM);

#endif