#pragma once
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>

// Class is a animated sprite that can loop or not loop

class AnimatedSprite {
public:
	AnimatedSprite(std::string name, int xx, int yy, int width, int height, int maxframes, int ticksperframe);
	void render();
	bool isDone();
private:
	int x;
	int y;
	int w;
	int h;
	bool done;
	std::string bmpName;
	int tick;
	int frame;
	int ticks_per_frame;
	int max_frame;
};

#endif