#pragma once
#ifndef DIALOGS_H
#define DIALOGS_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// Class is simply a box with a gradient background that can be drawn on top of
class DialogBox {
public:
	DialogBox(int xx, int yy, int ww, int hh);
	void makeGradient();
	virtual void render();
	int getX();
	int getY();
private:
	int x;
	int y;
	int width;
	int height;
	ALLEGRO_BITMAP *myGradient;
};

// Progress bar can be drawn onto the dialog box
void drawLoadBar(int x, int y, int width, float val, float maxval);

#endif