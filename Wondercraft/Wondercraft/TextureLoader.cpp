#include "TextureLoader.hpp"

TextureLoader::TextureLoader(std::string dir) {
	this->dir = dir;
}

TextureLoader::~TextureLoader() {
	map.clear();
}

sf::Texture* TextureLoader::get(std::string key) {
	sf::Texture* texture = nullptr;

	if (isLoaded(key)) {
		texture = map[key];
	}

	else {
		sf::Image img;
		if (img.loadFromFile(dir + key)) {
			texture = new sf::Texture();
			texture->loadFromImage(img);
			texture->setSmooth(true);
			map[key] = texture;
			texture = map[key];
		}
	}

	return texture;
}

bool TextureLoader::isLoaded(std::string key) {
	return map.count(key) > 0;
}

bool TextureLoader::unload(std::string key) {
	return map.erase(key) > 0;
}