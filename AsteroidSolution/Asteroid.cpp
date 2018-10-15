#include "Asteroid.h"

using namespace sf;

Asteroid::Asteroid(sf::RenderWindow &renderWindow, sf::Texture &texture, 
	sf::Vector2f position, Vector2f velocity, float radius) :
	mRenderWindow(renderWindow),
	mAsteroidTexture(texture),
	mPosition(position),
	mVelocity(velocity),
	mRadius(radius){
	textureToSprite();
	draw();
}

void Asteroid::textureToSprite() {
	mSprite.setTexture(mAsteroidTexture);
	mSprite.setOrigin(
		Vector2f(
			mSprite.getGlobalBounds().height / 2,
			mSprite.getGlobalBounds().width / 2
		)
	);

	mSprite.setPosition(mPosition);
}

void Asteroid::update(float deltaTime) {
	mSprite.move(deltaTime * mVelocity);
}

void Asteroid::draw() {
	mRenderWindow.draw(mSprite);
}

Vector2f Asteroid::getPosition() const {
	return mSprite.getPosition();
}