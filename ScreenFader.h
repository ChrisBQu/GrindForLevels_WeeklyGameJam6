#pragma once
#ifndef SCREEN_FADER_H
#define SCREEN_FADER_H

// An effect for the screen fading in or out from black/white

enum FADER_MODE { FROM_BLACK, TO_BLACK, WAIT_BLACK, WAIT_CLEAR};

class ScreenFader {
public:
	ScreenFader();
	void render();
	void fadeFromBlack(float seconds);
	void fadeToBlack(float seconds);
	void waitClear(float seconds);
	void waitBlack(float seconds);
	bool isDone();
private:
	bool done;
	int onStep;
	int maxStep;
	int mode;
};

#endif