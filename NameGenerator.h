#pragma once
#ifndef NAME_GENERATOR_H
#define NAME_GENERATOR_H

#include <vector>
#include <string>

// Class is used to generate names for characters in the player's party

class NameGenerator {
public:
	NameGenerator(std::string filename);
	std::string getName();
private:
	std::vector<std::string> loadedNames;
};

#endif