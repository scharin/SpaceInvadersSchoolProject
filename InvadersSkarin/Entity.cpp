#include "Entity.h"

using namespace sf;

Entity::Entity(Game *game) :
	mGame(game)
{
}


Entity::~Entity()
{
}

void Entity::draw() {
	mGame->draw(this->mSprite);
}

Vector2f Entity::getPosition() const {
	return this->mSprite.getPosition();
}