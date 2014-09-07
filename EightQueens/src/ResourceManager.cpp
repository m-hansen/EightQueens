#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

sf::Texture* ResourceManager::GetTexture(const std::string& filename)
{
	// Check if the texture already exists
	for (std::map<std::string, sf::Texture>::const_iterator it = textureMap.begin(); 
		it != textureMap.end(); ++it)
	{
		if (filename == it->first)
		{
			fprintf(stdout, "Using existing image: %s\n", filename.c_str());
			return &textureMap[filename];//(it->second));
		}
	}

	// Create and save the texture
	sf::Texture texture;
	if (texture.loadFromFile(filename))
	{
		textureMap[filename] = texture;
		fprintf(stdout, "Loading image: %s\n", filename.c_str());
		return &textureMap[filename];
	}

	// The texture file was not found
	fprintf(stdout, "Error: Texture \"%s\" not found!\n", filename.c_str());
	textureMap[filename] = texture;
	return &textureMap[filename];
}