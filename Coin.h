#ifndef ASTEROID_COIN
#define ASTEROID_COIN

#include "SFML/Graphics.hpp"

class Coin {
public:
	Coin(sf::RenderWindow &renderWindow, sf::Texture &texture,
		sf::Vector2f position, sf::Vector2f velocity, float radius);
	void update(float deltaTime);
	void draw();
	sf::Vector2f getPosition() const;
	// float getRadius() const;

private:
	sf::RenderWindow &mRenderWindow;
	sf::Texture mCoinTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	float mRadius;

	void textureToSprite();
	// void updatePosition(float deltaTime);
};

#endif