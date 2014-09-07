#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	sf::Texture* GetTexture(const std::string& filename);
private:
	// key = filename, value = texture;
	std::map<std::string, sf::Texture> textureMap;
};