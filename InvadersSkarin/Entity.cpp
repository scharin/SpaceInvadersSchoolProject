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

float Entity::getRadius() const {
	return this->mRadius;
}

bool Entity::isVisible() const {
	Vector2f pos = this->mSprite.getPosition();
	/* Checks if the entity is visible (Inside the gameWindow)
		* First checks if it's outside the y-axis, then checks the x-axis.
		* If any of these conditions is true, that an entity is outside the window
		* and returns false
		*/
	if ((pos.y < this->getRadius() || pos.y > (mGame->getWindowSize().y - this->getRadius()))
		|| (pos.x < 0 || pos.x > (mGame->getWindowSize().x - this->getRadius())))
		return false;
	else 
		return true;
}