#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

enum ITEM_NAMES {KUNAI, FIREBOMB, ICE_RAY, SHURIKEN, SPEED_DRINK, SIZE_OF_ITEM_ENUM };

const int ITEM_VALUES[SIZE_OF_ITEM_ENUM] = { 10, 20, 20, 30, 30 };

// Class represents an inventory of the player's items

class Inventory {
public:
	Inventory();
	int getRandomItem();
	void addItem(int item);
	void removeItem(int item);
	int getItemCount(int item);
	int getTotalItemCount();
private:
	int counts[SIZE_OF_ITEM_ENUM];
	int total;
};

#endif