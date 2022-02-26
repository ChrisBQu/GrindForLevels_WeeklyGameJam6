#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include <allegro5/allegro.h>

// Functions for reading mouse input

void resetMouseClicks();
void handleMouseControls(ALLEGRO_EVENT *ev);
bool getMouseClicked();
bool getMouseRightClicked();
int getMouseY();
int getMouseX();


#endif