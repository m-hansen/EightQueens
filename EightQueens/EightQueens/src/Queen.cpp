#include "Queen.hpp"

Queen::Queen()
{
	LoadResources();
}

Queen::~Queen()
{
}	  
	  
void Queen::LoadResources()
{
	sf::Texture texture;

	if (!texture.loadFromFile("resources/crown.jpg"))
	{
		// error
	}
}