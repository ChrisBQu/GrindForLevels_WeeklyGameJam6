#include "AnimatedSprite.h"
#include "Resources.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

using namespace std;

// Constructor
AnimatedSprite::AnimatedSprite(string name, int xx, int yy, int width, int height, int maxframes, int ticksperframe) {
	x = xx;
	y = yy;
	w = width;
	h = height;
	frame = 1;
	tick = 0;
	bmpName = name;
	max_frame = maxframes;
	ticks_per_frame = ticksperframe;
	done = false;
}

// Render loop
void AnimatedSprite::render() {
	
	// Tick the animation
	if (tick < ticks_per_frame) { tick++; }
	else if (tick == ticks_per_frame) {
		tick = 0;
		if (frame != max_frame) { frame++; }
		else { frame = 0; done = true; }
	}

	// Render the current frame
	al_draw_bitmap_region(getResourceManager()->getImage(bmpName), frame*w, 0, w, h, x, y, 0);
}

// Get whether or not the animation has completed at least once
bool AnimatedSprite::isDone() { return done; }