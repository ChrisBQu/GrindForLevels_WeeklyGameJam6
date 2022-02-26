#include "StateMachine.h"

StateMachine *instanceOfStateMachine = NULL;

// Constructor for state machine
StateMachine::StateMachine() {
	class DefaultState : public State {
		void render() {};
		void update() {};
		void enter() {};
		void exit() {};
	};
	DefaultState *D = new DefaultState();
	registerState("__DEF_STATE__", D);
	activeState = stringToState["__DEF_STATE__"];
}

// Register a new state by pairing an ID to an update/render function pair
void StateMachine::registerState(std::string id, State *s) {
	stringToState[id] = s;
}

// Change the current state
void StateMachine::changeState(std::string id) {
	if (stringToState.find(id) != stringToState.end()) {
		activeState->exit();
		activeState = stringToState[id];
		activeState->enter();
	}
}

// Call the appropriate render function for the current state
void StateMachine::render() {
	activeState->render();
}

// Call the appropriate update function for the current state
void StateMachine::update() {
	activeState->update();
}


StateMachine* StateMachine::getStateMachine() {
	if (!instanceOfStateMachine) { instanceOfStateMachine = new StateMachine(); }
	return instanceOfStateMachine;
}