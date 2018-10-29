#include "TextRes.h"
#include <iostream>

using namespace std;
using namespace sf;

TextRes::TextRes()
{
}

TextRes::~TextRes()
{
}

void TextRes::loadTextures() {
	// Loads all textures into memory at once
	// Few textures so it's doable
	loadTexture("bullet", "gfx/Bullet.psd");
	loadTexture("explosion", "gfx/Explosion.psd");
	loadTexture("invader", "gfx/Invader.psd");
	loadTexture("ship", "gfx/Ship.psd");
}

void TextRes::loadTexture(const string& name, const std::string& filename) {
	// Loads the texture
	sf::Texture tex;
	tex.loadFromFile(filename);

	// Adds it to the map of textures
	mTextures[name] = tex;
}

// To load textures use: mTextureManager.getRef("name")
sf::Texture& TextRes::getRef(const string& texture) {
	return mTextures.at(texture);
}