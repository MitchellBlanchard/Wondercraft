#include "FontLoader.hpp"

FontLoader::FontLoader(std::string dir) {
	this->dir = dir;
}

FontLoader::~FontLoader() {
	map.clear();
}

sf::Font* FontLoader::get(std::string key) {
	if (isLoaded(key)) {
		return map[key];
	}
	else {
		sf::Font* font = new sf::Font();
		if (font->loadFromFile(dir + key)) {
			map[key] = font;
			return map[key];
		}
	}

	return nullptr;
}

bool FontLoader::isLoaded(std::string key) {
	return map.count(key) > 0;
}

bool FontLoader::unload(std::string key) {
	return map.erase(key) > 0;
}