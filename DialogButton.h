#pragma once
#ifndef DIALOG_BUTTON_H
#define DIALOG_BUTTON_H

#include <string>

enum BUTTON_SIZE {SMALL_BUTTON, MEDIUM_BUTTON, LARGE_BUTTON};

// Class is a button that can be clicked on

class DialogButton {
public:
	DialogButton(int xx, int yy, int size, std::string text);
	void update();
	void render();
	void reset();
	bool isClicked();
private:
	std::string myText;
	int x;
	int y;
	int width;
	int mySize;
	bool highlighted;
	bool clicked;
};

#endif