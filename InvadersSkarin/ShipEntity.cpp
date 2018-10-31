#include "ShipEntity.h"
#include <iostream>

namespace {
	const float RADIUS = 30.0f;
	const float VELOCITY = 400.0f;
	const float FIRE_DELTA = .3f;
}

using namespace sf;
using namespace std;

ShipEntity::ShipEntity(Game *game, Vector2f position) :
	Entity(game),
	mFireTime(0)
{
	mSprite = mGame->createSprite("ship", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
}
ShipEntity::~ShipEntity()
{
}

void ShipEntity::update(float deltaTime) {
	updatePosition(deltaTime);
	constrainPosition();
	handleFire(deltaTime);
}

void ShipEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() == EntityFaction::ENEMY) {
		mGame->remove(this);
		mGame->gameOver(true);
	}
}

EntityFaction ShipEntity::getFaction() const {
	return EntityFaction::FRIEND;
}

EntityType ShipEntity::getType() const {
	return EntityType::SHIP;
}

void ShipEntity::updatePosition(float deltaTime) {
	float directionX = 0.0f;
	float directionY = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		directionX -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		directionX += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		directionY -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		directionY += 1.0f;
	}
	Vector2f direction(directionX, directionY);
	mSprite.move(deltaTime * mVelocity * direction);
}
void ShipEntity::constrainPosition() {
	Vector2f windowSizeFloat;
	windowSizeFloat = Vector2f(mGame->getWindowSize());
	float minX = mRadius;
	float minY = mRadius;
	float maxX = windowSizeFloat.x - mRadius;
	float maxY = windowSizeFloat.y - mRadius;
	float shipX = mSprite.getPosition().x;
	float shipY = mSprite.getPosition().y;

	if (shipX < minX) {
		shipX = minX;
	}
	else if (maxX < shipX) {
		shipX = maxX;
	}
	if (shipY < minY) {
		shipY = minY;
	}
	else if (maxY < shipY) {
		shipY = maxY;
	}

	Vector2f shipPosition(shipX, shipY);
	mSprite.setPosition(shipPosition);
}
void ShipEntity::handleFire(float deltaTime) {
	mFireTime += deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::Space) && FIRE_DELTA < mFireTime) {
		EntityFaction faction = EntityFaction::FRIEND;
		Vector2f position = mSprite.getPosition();
		Vector2f direction1 = Vector2f(0.0f, -1.0f);
		Vector2f direction2 = Vector2f(.5f, -1.0f);
		Vector2f direction3 = Vector2f(-.5f, -1.0f);

		mGame->add(new BulletEntity(mGame, faction, position, direction1));
		mGame->add(new BulletEntity(mGame, faction, position, direction2));
		mGame->add(new BulletEntity(mGame, faction, position, direction3));

		mFireTime = 0.0f;
	}
}