#include "Inventory.h"
#include <random>

using namespace std;

// Constructor
Inventory::Inventory() {
	total = 0;
	for (int i = 0; i < SIZE_OF_ITEM_ENUM; i++) { counts[i] = 0; }
}

// Get the count of a specific item in the inventory
int Inventory::getItemCount(int item) { return counts[item]; }

// Get the total item count
int Inventory::getTotalItemCount() { return total; }

// Remove an item from the inventory
void Inventory::removeItem(int item) {
	if (counts[item] > 0) { 
		counts[item]--;
		total--;
	}
}

// Add an item to the inventory
void Inventory::addItem(int item) { 
	counts[item]++; 
	total++;
}

// Get a random item from the inventory
int Inventory::getRandomItem() {
	if (total == 0) { return -1; }
	else {
		int r = rand() % SIZE_OF_ITEM_ENUM;
		while (counts[r] == 0) {
			r++;
			if (r == SIZE_OF_ITEM_ENUM) { r = 0; }
		}
		return r;
	}
}