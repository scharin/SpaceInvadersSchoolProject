#ifndef INVADERS_SHIP
#define INVADERS_SHIP

class ConGame;
#include "SFML/Graphics.hpp"
#include "ConGame.h"

class ShipEntity
{
public:
	ShipEntity(ConGame *game);
	~ShipEntity();
	void draw();

private:
	ConGame *mGame;
	sf::Sprite mSprite;
};

#endif