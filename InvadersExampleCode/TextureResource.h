#ifndef INVADERS_TEXTURE_RESOURCE
#define INVADERS_TEXTURE_RESOURCE

#include "SFML/Graphics.hpp"
#include <string>

class TextureResource{
public:
	TextureResource(std::string filename, sf::Texture texture);
	std::string getFilename() const;
	sf::Texture& getTexture() const;
private:
	std::string mFilename;
	sf::Texture mTexture;
}

#endif