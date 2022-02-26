#pragma once
#ifndef PARTY_ORDER_STATE_H
#define PARTY_ORDER_STATE_H

#include "StateMachine.h"
#include "ScreenFader.h"
#include "PartyGenerator.h"
#include "ScrollingBackground.h"
#include "Dialogs.h"
#include "DialogButton.h"

// State where player changes the order of their party

class PartyOrderState : public State {
public:
	friend class StateMachine;
	PartyOrderState();
	void render();
	void update();
	void enter();
	void exit();
private:
	DialogBox *dialog1;
	DialogBox *dialog2;
	DialogBox *dialog3;
	DialogButton *switch1and2;
	DialogButton *switch1and3;
	DialogButton *switch2and3;
	DialogButton *backButton;
	ScrollingBG *myBG;
	ScreenFader myFader;
};

#endif