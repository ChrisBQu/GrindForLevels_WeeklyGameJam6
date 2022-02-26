#pragma once
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <string>
#include <map>

class State {
	friend class StateMachine;
private:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
};


class StateMachine {
private:
	StateMachine();
	std::map<std::string, State*> stringToState;
	State *activeState;
public:
	static StateMachine *getStateMachine();
	void changeState(std::string id);
	void registerState(std::string id, State *s);
	void update();
	void render();
};


#endif