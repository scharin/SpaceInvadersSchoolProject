#include "Coin.h"

using namespace sf;

Coin::Coin(sf::RenderWindow &renderWindow, sf::Texture &texture,
	sf::Vector2f position, Vector2f velocity, float radius) :
	mRenderWindow(renderWindow),
	mCoinTexture(texture),
	mPosition(position),
	mVelocity(velocity),
	mRadius(radius) {
	textureToSprite();
	draw();
}

void Coin::textureToSprite() {
	mSprite.setTexture(mCoinTexture);
	mSprite.setOrigin(
		Vector2f(
			mSprite.getGlobalBounds().height / 2,
			mSprite.getGlobalBounds().width / 2
		)
	);

	mSprite.setPosition(mPosition);
}

void Coin::update(float deltaTime) {
	mSprite.move(deltaTime * mVelocity);
}

void Coin::draw() {
	mRenderWindow.draw(mSprite);
}

Vector2f Coin::getPosition() const {
	return mSprite.getPosition();
}