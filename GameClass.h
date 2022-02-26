#pragma once
#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <allegro5/allegro.h>

// Class representing the game object itself

const int DEFAULT_SCREEN_WIDTH = 256;
const int DEFAULT_SCREEN_HEIGHT = 224;
const int DEFAULT_FPS = 60;
const float DEFAULT_SCALE_X = 4;
const float DEFAULT_SCALE_Y = 4;
const bool DEFAULT_FULLSCREEN = false;

class GameClass {

private:
	int window_width; 
	int window_height;
	int screen_width; 
	int screen_height;
	int scale_x; 
	int scale_y;
	int FPS;
	bool done = false;
	bool scanlines_on = false;
	bool redraw = false;
	bool fullscreen = false;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *EQ = NULL;
	ALLEGRO_BITMAP *displayBuffer = NULL;
	void createEventQueue();
	void registerModules();

public:
	int getFPS();
	int getScreenWidth();
	int getScreenHeight();
	float getXScale();
	float getYScale();
	void run();
	void end();
	void changeDisplay(int width, int height, int scale_x, int scale_y, bool fullscrn);
	GameClass();
	~GameClass();
};

GameClass *getGameClass();

#endif