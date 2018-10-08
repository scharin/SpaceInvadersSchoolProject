#include "Ship.h"

using namespace sf;

Ship::Ship(sf::RenderWindow &renderWindow, sf::Texture &texture,
	sf::Vector2f position, float velocity, float radius) :
	mRenderWindow(renderWindow),
	mShipTexture(texture),
	mPosition(position),
	mVelocity(velocity),
	mRadius(radius){
	textureToSprite();
	draw();
}

void Ship::textureToSprite() {
	mSprite.setTexture(mShipTexture);
	mSprite.setOrigin(
		Vector2f(
			mSprite.getGlobalBounds().height / 2, 
			mSprite.getGlobalBounds().width / 2
		)
	);
	
	mSprite.setPosition(mPosition);
}

void Ship::update(float deltaTime) {
	updatePosition(deltaTime);
	constrainPosition();
}
void Ship::updatePosition(float deltaTime) {
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
void Ship::constrainPosition() {
	Vector2f windowSizeFloat;
	windowSizeFloat = Vector2f(mRenderWindow.getSize());
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

void Ship::draw() {
	mRenderWindow.draw(mSprite);
}

Vector2f Ship::getPosition() const {
	return mSprite.getPosition();
}

