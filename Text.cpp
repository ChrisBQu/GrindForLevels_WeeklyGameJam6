#include "Text.h"
#include "Resources.h"
#include <allegro5/allegro_font.h>

using namespace std;

// Draw text without shadow
void drawText(ALLEGRO_COLOR c, string fontname, float dx, float dy, string msg) {
	ALLEGRO_FONT *useFont = getResourceManager()->getFont(fontname);
	al_draw_textf(useFont, c, dx - 1, dy - 1, 0, msg.c_str());
}

// Draw text with shadow
void drawShadowedText(ALLEGRO_COLOR c, ALLEGRO_COLOR outline, string fontname, float dx, float dy, string msg) {
	ALLEGRO_FONT *useFont = getResourceManager()->getFont(fontname);
	int x; int y;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			al_draw_textf(useFont, outline, dx - 1 + x, dy - 1 + y, 0, msg.c_str());
		}
	}
	al_draw_textf(useFont, c, dx, dy, 0, msg.c_str());
}