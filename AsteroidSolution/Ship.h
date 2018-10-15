#ifndef ASTEROID_SHIP
#define ASTEROID_SHIP

#include "SFML/Graphics.hpp"

class Ship {
public:
	Ship(sf::RenderWindow &renderWindow, sf::Texture &texture, 
		sf::Vector2f position, float velocity, float radius);
	void update(float deltaTime);
	void draw();
	sf::Vector2f getPosition() const;

private:
	sf::RenderWindow &mRenderWindow;
	sf::Texture mShipTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	float mVelocity;
	float mRadius;

	void textureToSprite();
	void updatePosition(float deltaTime);
	void constrainPosition();
};

#endif