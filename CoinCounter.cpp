#include "CoinCounter.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include "Text.h"
#include "SaveData.h"
#include <string>

using namespace std;

// Constructor
CoinCounter::CoinCounter(int xx, int yy) {
	x = xx;
	y = yy;
	myAnimation = new AnimatedSprite("COIN", x+1, y+1, 16, 16, 7, 4);
}

// Destructor
CoinCounter::~CoinCounter() {
	if (myAnimation) { delete myAnimation; }
}

// Render loop
void CoinCounter::render() {

	// Draw bounding box
	al_draw_filled_rectangle(x, y, x + 49, y + 18, al_map_rgba(200, 200, 200, 200));
	al_draw_rectangle(x, y, x + 50, y + 19, al_map_rgb(0,0,0), 1);

	// Draw the animated coin
	myAnimation->render();

	// Render the coin counter
	drawShadowedText(al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), "FONT2", x + 19, y + 6, to_string(getLoadedSave()->coins));

}