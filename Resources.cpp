#include "Resources.h"
#include <iostream>
#include <fstream>
#include <allegro5/allegro_ttf.h>

#define DEFAULT_EMPTY_STRING ""

using namespace std;

ResourceManagerClass* ResourceManager;

// Constructor creates default resources to return in case of errors
ResourceManagerClass::ResourceManagerClass() {

	// Create dummy font and image to return if actual images are not found or cannot be loaded
	blankImage = al_create_bitmap(1, 1);
	blankFont = al_create_builtin_font();

	// For simplicity, the most commonly accessed graphics remain stored in memory
	loadImage("Resources/Interface/Interface.png", "UI");
	loadImage("Resources/Interface/Icons.png", "UNIT_ICONS");
	loadImage("Resources/Interface/Header.png", "HEADER");
	loadImage("Resources/Interface/ButtonSmall.png", "SMALL_BUTTON");
	loadImage("Resources/Interface/Button.png", "MEDIUM_BUTTON");
	loadImage("Resources/Interface/ButtonLarge.png", "LARGE_BUTTON");

}

// Parses a text file for strings, and adds them to myStrings map
// Lines of file are, for example:
//
// @ STRING_ONE Hello
// @ STRING_TWO Goodbye
// @ STRING_THREE How are you?
// ...
void ResourceManagerClass::loadStrings(string filename) {

	// Open file, with error checking
	ifstream fp(filename);
	if (fp.fail()) {
		cout << "Error: File <" << filename << "> does not exist." << endl;
		return;
	}

	// Tokenize file, and load map of key strings and value strings.
	string valString = "";
	string keyString = "";
	string token;
	while (fp >> token) {
		// @ as a token indicates a new pair has been reached.
		if (!token.compare("@")) {
			if (valString.compare(" ")) { myStrings[keyString] = valString; }
			fp >> keyString;
			valString = "";
		}
		else { valString += token + " "; }
	}

	fp.close();
}

// Return a string if it exists, and a default string otherwise
string ResourceManagerClass::getString(std::string string_key) {
	if (myStrings.find(string_key) == myStrings.end()) {
		cout << "Error: String <" << string_key << "> does not exist." << endl;
		return DEFAULT_EMPTY_STRING;
	}
	else { return myStrings[string_key]; }
}


// Load an image and store it as a spritesheet
void ResourceManagerClass::loadImage(string filename, string name) {
	ALLEGRO_BITMAP *loadedImg = al_load_bitmap(filename.c_str());
	// If the image could not be loaded, print an error
	if (loadedImg) {
		// Make sprite transparent by removing "magic pink"
		al_convert_mask_to_alpha(loadedImg, al_map_rgb(255, 0, 255));
		if (mySpritesheets.find(name) != mySpritesheets.end()) { mySpritesheets.erase(name); }
		mySpritesheets[name] = loadedImg;
	}

	// If the image could not be loaded, print an error, and use a blank bitmap
	else {
		cout << "Error: Unable to load sprite: " << filename << endl;
		mySpritesheets[name] = blankImage;
	}
}

// Unload an image from memory
void ResourceManagerClass::unloadImage(string name) {
	if (mySpritesheets.find(name) != mySpritesheets.end()) { mySpritesheets.erase(name); }
}

// Load a font and store it
void ResourceManagerClass::loadFont(string filename, string name, int fsize) {
	ALLEGRO_FONT *loadedFont = al_load_ttf_font(filename.c_str(), fsize, ALLEGRO_TTF_MONOCHROME);
	myFonts[name] = loadedFont;
}

// Return the image if it exists, otherwise return a blank one
ALLEGRO_BITMAP* ResourceManagerClass::getImage(std::string name) {
	if (mySpritesheets.find(name) != mySpritesheets.end()) { return mySpritesheets[name]; }
	else {
		cout << "Error: Image <" << name << "> does not exist." << endl;
		return blankImage;
	}
}

// Return the image if it exists, otherwise return a blank one
ALLEGRO_FONT* ResourceManagerClass::getFont(std::string name) {
	if (myFonts.find(name) != myFonts.end()) { return myFonts[name]; }
	else {
		cout << "Error: Font <" << name << "> does not exist." << endl;
		return blankFont;
	}
}

// ResourceManager is a singleton that can be requested and used by other classes
void initResourceManager() {

	ResourceManager = new ResourceManagerClass();

	// Load Strings
	ResourceManager->loadStrings("Resources/Data/Strings.txt");

	// Load fonts
	ResourceManager->loadFont("Resources/Fonts/ArcadepixPlus.ttf", "FONT1", 12);
	ResourceManager->loadFont("Resources/Fonts/Munro.ttf", "FONT2", 11);
	ResourceManager->loadFont("Resources/Fonts/Behindthesurprise.ttf", "FONT3", 12);
	ResourceManager->loadFont("Resources/Fonts/SEA_GARDENS.ttf", "FONT4", 20);

}
ResourceManagerClass* getResourceManager() {
	return ResourceManager;
}