#pragma once
#ifndef COMBAT_LOG_H
#define COMBAT_LOG_H

#include <string>
#include <vector>

// Class is a dialog window showing text that describes the aftermath of combat

class CombatLog {
public:
	CombatLog(int xx, int yy, int ww, int hh);
	void addText(std::string text);
	void clearText();
	void render();
private:
	int x;
	int y;
	int height;
	int width;
	int open_ticker;
	std::vector<std::string> myText;
};

#endif