#pragma once
#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include <string>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

// Resource manager class to handle all of the game's resources

class ResourceManagerClass {
public:
	ResourceManagerClass();
	ALLEGRO_BITMAP* getImage(std::string name);
	ALLEGRO_FONT* getFont(std::string name);
	std::string getString(std::string string_id);
	void loadFont(std::string filename, std::string name, int fsize);
	void loadImage(std::string filename, std::string name);
	void loadStrings(std::string filename);
	void unloadImage(std::string name);
private:
	ALLEGRO_BITMAP *blankImage;
	ALLEGRO_FONT *blankFont;
	std::map<std::string, ALLEGRO_BITMAP*> mySpritesheets;
	std::map<std::string, ALLEGRO_FONT*> myFonts;
	std::map<std::string, std::string> myStrings;
};

void initResourceManager();
ResourceManagerClass* getResourceManager();

#endif
