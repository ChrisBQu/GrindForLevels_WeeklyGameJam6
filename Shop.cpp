#include "Shop.h"
#include "allegro5/allegro_primitives.h"
#include "Resources.h"
#include "Mouse.h"
#include "SaveData.h"
#include "Sound.h"
#include "Inventory.h"

// Constructor
Shop::Shop() {
	myMenu = new LargeMenu(SHOP_SCENE_POS_X + SHOP_SCENE_WIDTH + SHOP_SCENE_SPACING, SHOP_SCENE_POS_Y);
	myMenu->addChoice("Kunai (10 coins)");
	myMenu->addChoice("Firebomb (20 coins)");
	myMenu->addChoice("Ice Ray (20 coins)");
	myMenu->addChoice("Shuriken (30 coins)");
	myMenu->addChoice("Speed Drink (30 coins)");
}


// Destructor
Shop::~Shop() {
	if (myMenu) { delete myMenu; }
}

// Update Loop
void Shop::update() {
	myMenu->update();

	// User tries to make a purchase
	if (myMenu->isDone()) {
		int chosen = myMenu->getChosen();
		if (getLoadedSave()->coins >= ITEM_VALUES[chosen]) {
			getLoadedSave()->inventory.addItem(chosen);
			getLoadedSave()->coins -= ITEM_VALUES[chosen];
			getSoundPlayer()->playEffect("Resources/Sound/Purchase.ogg");
		}
		else { getSoundPlayer()->playEffect("Resources/Sound/Error.ogg"); }
		resetMouseClicks();
		myMenu->reset();
	}

}

// Render Loop
void Shop::render() {

	// Render the shop scene
	al_draw_bitmap(getResourceManager()->getImage("SHOP_SCENE"), SHOP_SCENE_POS_X, SHOP_SCENE_POS_Y, 0);
	al_draw_rectangle(SHOP_SCENE_POS_X, SHOP_SCENE_POS_Y, SHOP_SCENE_POS_X + SHOP_SCENE_WIDTH,
		SHOP_SCENE_POS_Y + SHOP_SCENE_HEIGHT, al_map_rgb(0, 0, 0), 1);

	// Render the menu
	myMenu->render();

}