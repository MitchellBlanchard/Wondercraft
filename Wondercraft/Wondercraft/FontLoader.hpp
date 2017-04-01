#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

// Loads fonts only when they are needed and
// prevents unnecessarily loading fonts multiple times
class FontLoader {
public:
	//Constructor may take a root directory for fonts
	FontLoader(std::string dir = "");
	~FontLoader();

	//returns the given font, loads the font if not already loaded
	sf::Font* get(std::string key);

	bool isLoaded(std::string key);

	//deletes the given font from memory
	bool unload(std::string key);

private:
	std::string dir;
	std::map<std::string, sf::Font*> map;
};