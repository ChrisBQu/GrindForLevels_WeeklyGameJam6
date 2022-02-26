#include "NameGenerator.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor loads names into the generator's vector
NameGenerator::NameGenerator(string filename) {
	
	ifstream fp(filename);

	// Error checking: put blank names in the list so that it technically still works
	// even if the name list could not be loaded
	if (fp.fail()) {
		cout << "Error: Unable to open data file: " << filename <<  endl;
		loadedNames.push_back("_BLANK_NAME_1");
		loadedNames.push_back("_BLANK_NAME_2");
		loadedNames.push_back("_BLANK_NAME_3");
	}

	// Othwerwise load the vector with names
	else {
		string nextToken;
		while (fp >> nextToken) { loadedNames.push_back(nextToken); }
	}

}

// Get a name from the list of loaded names at random
string NameGenerator::getName() {
	int index = rand() % loadedNames.size();
	return loadedNames.at(index);
}