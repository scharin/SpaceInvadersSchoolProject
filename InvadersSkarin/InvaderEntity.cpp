#include "InvaderEntity.h"
#include <iostream>
#include <string>

namespace {
	const float RADIUS = 32.0f;
	const float VELOCITY = 150.0f;
	const float FIRE_DELTA = 1.0f;
}

using namespace std;
using namespace sf;

InvaderEntity::InvaderEntity(Game *game, Vector2f position, Vector2f direction) :
	Entity(game),
	mDirection(direction),
	mFireTime(0)
{
	mSprite = mGame->createSprite("invader", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
}
InvaderEntity::~InvaderEntity()
{
}

void InvaderEntity::update(float deltaTime) {
	updatePosition(deltaTime);
	handleFire(deltaTime);
}

void InvaderEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() == EntityFaction::FRIEND) {
		mGame->add(new ExplosionEntity(mGame, this->getPosition()));
		mGame->remove(this);
		mGame->updateKills();
	}
}

EntityFaction InvaderEntity::getFaction() const {
	return EntityFaction::ENEMY;
}
EntityType InvaderEntity::getType() const {
	return EntityType::SHIP;
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
void InvaderEntity::handleFire(float deltaTime) {
	mFireTime += deltaTime;
	if (FIRE_DELTA < mFireTime) {
		EntityFaction faction = EntityFaction::ENEMY;
		Vector2f position = mSprite.getPosition();
		Vector2f direction = Vector2f(.0f, 1.0f);
		mGame->add(new BulletEntity(mGame, faction, position, direction));
		mFireTime = .0f;
	}
}