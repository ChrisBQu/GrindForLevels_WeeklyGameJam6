#include "Mouse.h"
#include "GameClass.h"

// Values to track the mouse
int mousex = 0;
int mousey = 0;
bool mouse_click_state = false;
bool mouse_right_click_state = false;

void handleMouseControls(ALLEGRO_EVENT *ev) {

	mouse_click_state = false;
	mouse_right_click_state = false;

	// Update cursor values if the mouse moves
	if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mousex = ev->mouse.x / getGameClass()->getXScale();
		mousey = ev->mouse.y / getGameClass()->getYScale();
	}

	// Update click state if a mouse button was pressed
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (ev->mouse.button == 1) {
			if (mouse_click_state == false) { mouse_click_state = true; }
		}
		if (ev->mouse.button == 2) {
			if (mouse_right_click_state == false) { mouse_right_click_state = true; }
		}
	}

}

// Get the mouse cursor positions
int getMouseX() { return mousex; }
int getMouseY() { return mousey; }

// Check mouse clicks
bool getMouseClicked() { return mouse_click_state; }
bool getMouseRightClicked() { return mouse_right_click_state; }

// Reset mouse click status (so that the event can be "eaten" if desired
void resetMouseClicks() {
	mouse_click_state = false;
	mouse_right_click_state = false;
}