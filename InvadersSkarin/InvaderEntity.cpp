#include "InvaderEntity.h"
#include <iostream>
#include <string>

namespace {
	const float RADIUS = 32.0f;
	const float VELOCITY = 150.0f;
}

using namespace std;
using namespace sf;

InvaderEntity::InvaderEntity(Game *game, Vector2f position, Vector2f direction) :
	Entity(game),
	mDirection(direction)
{
	mSprite = mGame->createSprite("invader", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
}
InvaderEntity::~InvaderEntity()
{
}

EntityFaction InvaderEntity::getFaction() const {
	return EntityFaction::ENEMY;
}
EntityType InvaderEntity::getType() const {
	return EntityType::SHIP;
}

void InvaderEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() == EntityFaction::FRIEND) {
		mGame->remove(this);
	}
}

void InvaderEntity::update(float deltaTime) {
	updatePosition(deltaTime);
}
void InvaderEntity::updatePosition(float deltaTime) {
	float minX = mRadius;
	float maxX = mGame->getWindowSize().x - mRadius;
	Vector2f position = mSprite.getPosition();
	position += deltaTime * mVelocity * mDirection;

	if (position.x < minX) {
		position.x = minX;
		mDirection.x = -mDirection.x;
	}
	else if (maxX < position.x) {
		position.x = maxX;
		mDirection.x = -mDirection.x;
	}
	mSprite.setPosition(position);
}