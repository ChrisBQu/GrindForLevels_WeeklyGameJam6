#pragma once
#ifndef SCROLLING_BG_H
#define SCROLLING_BG_H

#include <string>

// Class is a scrolling tiled background. Can be stationary if desired
// Backgrounds must have equal width and height

class ScrollingBG {
public:
	ScrollingBG(std::string name, int image_size, bool scroll);
	void render();
private:
	int size;
	int scrollval;
	std::string image_name;
	bool scrolling;

};

#endif