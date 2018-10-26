#include "ShipEntity.h"

ShipEntity::ShipEntity(ConGame *game) : 
	mGame(game),
	mSprite(mGame->createSprite("ship", sf::Vector2f(200,200)))
{
}

ShipEntity::~ShipEntity()
{
}

void ShipEntity::draw() {
	mGame->draw(mSprite);
}
