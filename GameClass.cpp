#include "GameClass.h"
#include "Mouse.h"
#include "StateMachine.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

GameClass *GameClassObj;

// Constructor for GameClass object
GameClass::GameClass() {

	// Set framerate
	FPS = DEFAULT_FPS;
	GameClassObj = this;

	// Create the window and display buffer
	if (!al_init()) { std::cout << "Error: Could not initialize Allegro." << std::endl; return; }
	changeDisplay(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_SCALE_X, DEFAULT_SCALE_Y, DEFAULT_FULLSCREEN);

	// Register allegro modules and create event queue
	registerModules();
	createEventQueue();

}

GameClass::~GameClass() {
	if (display != NULL) { al_destroy_display(display); }
	if (displayBuffer != NULL) { al_destroy_bitmap(displayBuffer); }
	if (EQ != NULL) { al_destroy_event_queue(EQ); }
}

void GameClass::changeDisplay(int width, int height, int sx, int sy, bool fullscrn) {

	// Destroy the display if it exists
	if (display != NULL) { al_destroy_display(display); }

	// Create a display object, with error checking
	if (fullscrn) { al_set_new_display_flags(ALLEGRO_FULLSCREEN); }
	display  = al_create_display(width*sx, height*sy);
	if (!display) { std::cout << "Error: Could not create display." << std::endl; return; }

	// Destroy the display buffer if it exists
	if (displayBuffer != NULL) { al_destroy_bitmap(displayBuffer); }

	// Create a new display, with error checking
	displayBuffer = al_create_bitmap(width, height);
	if (!displayBuffer) { std::cout << "Error: Could not create display buffer." << std::endl; return; }

	// Update member variables
	screen_width = width;
	screen_height = height;
	scale_x = sx;
	scale_y = sy;
	window_width = width * sx;
	window_height = height * sy;
}

// Method instantiates all of the modules to be used by Allegro
void GameClass::registerModules() {
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_install_joystick();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_acodec_addon();
}

// Function creates an Allegro event queue, and registers appropriate event sources to it
// Must be called after registerModules() is called
void GameClass::createEventQueue() {

	// Create game clock which will be added to the event queue
	ALLEGRO_TIMER *gameClock = al_create_timer(1.0 / FPS);
	al_start_timer(gameClock);

	EQ = al_create_event_queue();
	al_register_event_source(EQ, al_get_timer_event_source(gameClock));
	al_register_event_source(EQ, al_get_display_event_source(display));
	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_joystick_event_source());
	al_register_event_source(EQ, al_get_mouse_event_source());
}

// Main loop for the game
void GameClass::run() {

	StateMachine *FSM = StateMachine::getStateMachine();

	while (!done) {

		// Wait for an event from the queue
		ALLEGRO_EVENT ev;
		al_wait_for_event(EQ, &ev);
		handleMouseControls(&ev);

		// If the window is closed, end the loop
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { end(); }

		// Limit draw calls in accordance to the FPS timer
		if (ev.type == ALLEGRO_EVENT_TIMER) { redraw = true; }

		// Update function of current state
		FSM->update();

		// Rendering loop
		if (redraw) {

			// Clear the display
			al_set_target_bitmap(displayBuffer);
			al_clear_to_color(al_map_rgb(0,0,0));
			
			// Render function of current state
			FSM->render();

			// Upscale the resolution
			al_set_target_backbuffer(display);
			al_draw_scaled_bitmap(displayBuffer, 0, 0, screen_width, screen_height, 0, 0, screen_width * scale_x, screen_height * scale_y, 0);

			// Draw scanlins if option is turned on
			if (scanlines_on) {
				for (int i = 0; i < window_height + 4; i += 4) { al_draw_line(0, i, window_width, i, al_map_rgb(22, 22, 22), 1); }
			}

			// Blit everything
			al_flip_display();
			redraw = false;
		}

	}

}

// End the game
void GameClass::end() { done = true; }

// Public getter methods
int GameClass::getFPS() { return FPS; }
int GameClass::getScreenHeight() { return screen_height; }
int GameClass::getScreenWidth() { return screen_width; }
float GameClass::getXScale() { return scale_x; }
float GameClass::getYScale() { return scale_y; }

// Return a pointer to the game class
GameClass *getGameClass() { return GameClassObj; }
