#ifndef INVADERS_SHIP
#define INVADERS_SHIP

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Game.h"

class ShipEntity : public Entity
{
public:
	ShipEntity(Game *game);
	~ShipEntity();
	void update(float deltaTime);

private:
	void updatePosition(float deltaTime);
	void constrainPosition();
	void handleFire();
};

#endif