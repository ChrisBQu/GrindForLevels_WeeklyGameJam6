#include "GameClass.h"
#include "StateMachine.h"
#include "MapBattleState.h"
#include "StudioLogoSplash.h"
#include "GameJamSplash.h"
#include "CombatState.h"
#include "PartyGeneratorState.h"
#include "SelectStageState.h"
#include "PartyOrderState.h"
#include "ShopState.h"
#include "MainMenuState.h"
#include "Resources.h"
#include "TitleState.h"
#include "InventoryState.h"
#include <time.h>
#include <iostream>

int main() {

	// Seed the random number generator
	srand(time(NULL));

	// Create the game object (must be before initializing resource manager)
	GameClass *GAME = new GameClass();

	// Initialize resource manager
	initResourceManager();

	// Set up FSM to control game state
	StateMachine *FSM = StateMachine::getStateMachine();
	FSM->registerState("MAP_BATTLE_STATE", new MapBattleState());
	FSM->registerState("STUDIO_LOGO_STATE", new StudioLogoState());
	FSM->registerState("GAME_JAM_LOGO_STATE", new GameJamLogoState());
	FSM->registerState("COMBAT_STATE", new CombatState());
	FSM->registerState("PARTY_GEN_STATE", new PartyGeneratorState());
	FSM->registerState("STAGE_SELECT_STATE", new StageSelectState());
	FSM->registerState("MAIN_MENU_STATE", new MainMenuState());
	FSM->registerState("PARTY_ORDER_STATE", new PartyOrderState());
	FSM->registerState("SHOP_STATE", new ShopState());
	FSM->registerState("TITLE_STATE", new TitleState());
	FSM->registerState("INVENTORY_STATE", new InventoryState());
	FSM->changeState("STUDIO_LOGO_STATE");

	// Run the game
	GAME->run();

	return 0;
}