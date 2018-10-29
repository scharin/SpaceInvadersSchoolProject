#ifndef INVADERS_GAME
#define INVADERS_GAME

class Entity;

#include "SFML/Graphics.hpp"
#include <string>

class Game
{
public:
	Game();
	virtual ~Game();
	virtual sf::Vector2f getWindowSize() const = 0;
	virtual sf::Sprite createSprite(std::string filename, sf::Vector2f position) = 0;
	virtual void run() = 0;
	virtual void remove(Entity *entity) = 0;
	virtual void draw(sf::Sprite &sprite) = 0;
	virtual bool isVisible(Entity *entity) = 0;
};

#endif