#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

// Functions for drawing text to the screen

void drawText(ALLEGRO_COLOR c, std::string fontname, float dx, float dy, std::string msg);
void drawShadowedText(ALLEGRO_COLOR c, ALLEGRO_COLOR outline, std::string fontname, float dx, float dy, std::string msg);

#endif