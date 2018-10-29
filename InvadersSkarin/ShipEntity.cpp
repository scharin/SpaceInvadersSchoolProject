#include "ShipEntity.h"
#include <iostream>

namespace {
	const float RADIUS = 30.0f;
	const float VELOCITY = 400.0f;
}

using namespace sf;
using namespace std;

ShipEntity::ShipEntity(Game *game, Vector2f position) :
	Entity(game)
{
	mSprite = mGame->createSprite("ship", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
}
ShipEntity::~ShipEntity()
{
}

EntityFaction ShipEntity::getFaction() const {
	return EntityFaction::FRIEND;
}
EntityType ShipEntity::getType() const {
	return EntityType::SHIP;
}
void ShipEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() == EntityFaction::ENEMY) {
		mGame->remove(this);
	}
}

void ShipEntity::update(float deltaTime) {
	updatePosition(deltaTime);
	constrainPosition();
	handleFire();
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
void ShipEntity::handleFire() {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		cout << "Do pew pew stuff \n";
	}
}