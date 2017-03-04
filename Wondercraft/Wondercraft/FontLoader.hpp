#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class FontLoader {
public:
	FontLoader(std::string dir = "");
	~FontLoader();

	sf::Font* get(std::string key);
	bool isLoaded(std::string key);
	bool unload(std::string key);

private:
	std::string dir;
	std::map<std::string, sf::Font*> map;
};