#ifndef ASTEROID_ASTEROID
#define ASTEROID_ASTEROID

#include "SFML/Graphics.hpp"

class Asteroid
{
public:
	Asteroid(sf::RenderWindow &renderWindow, sf::Texture &texture,
		sf::Vector2f position, sf::Vector2f velocity, float radius);
	void update(float deltaTime);
	void draw();
	sf::Vector2f getPosition() const;

private:
	sf::RenderWindow &mRenderWindow;
	sf::Texture mAsteroidTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	float mRadius;

	void textureToSprite();
};

#endif