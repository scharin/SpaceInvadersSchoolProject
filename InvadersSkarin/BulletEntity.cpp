#include "BulletEntity.h"
#include <iostream>

namespace {
	const float RADIUS = 3.0f;
	const float VELOCITY = 800.0f;
}
using namespace std;
using namespace sf;


BulletEntity::BulletEntity(Game *game, EntityFaction faction, Vector2f position, Vector2f direction) :
	Entity(game),
	mFaction(faction),
	mDirection(direction)
{
	mSprite = mGame->createSprite("bullet", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
}
BulletEntity::~BulletEntity()
{
}

EntityType BulletEntity::getType() const {
	return EntityType::PROJECTILE;
}
EntityFaction BulletEntity::getFaction() const {
	return mFaction;
}

void BulletEntity::collide(Entity *otherEntity) {
	EntityFaction opositFaction;
	if (mFaction == EntityFaction::ENEMY) opositFaction = EntityFaction::FRIEND;
	else opositFaction = EntityFaction::ENEMY;
	if (otherEntity->getFaction() == opositFaction && otherEntity->getType() == EntityType::SHIP) {
		mGame->remove(this);
	}
}

void BulletEntity::update(float deltaTime) {
	Vector2f position = mSprite.getPosition();
	position += deltaTime * mVelocity * mDirection;

	mSprite.setPosition(position);
}
