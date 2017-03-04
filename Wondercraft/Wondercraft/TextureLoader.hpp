#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureLoader {
public:
	TextureLoader(std::string dir="");
	~TextureLoader();

	sf::Texture* get(std::string key);
	bool isLoaded(std::string key);
	bool unload(std::string key);
	
private:
	std::string dir;
	std::map<std::string, sf::Texture*> map;
};