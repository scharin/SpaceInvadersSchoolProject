#ifndef INVADERS_TEXTRES
#define INVADERS_TEXTRES

#include "SFML/Graphics.hpp"
#include <string>
#include <map>

class TextRes
{
public:
	TextRes();
	~TextRes();
	void loadTextures();
	void loadTexture(const std::string& name, const std::string& filename);
	sf::Texture& getRef(const std::string& texture);

	void printLoadedTextures();
private:
	std::map<std::string, sf::Texture> mTextures;
};

#endif