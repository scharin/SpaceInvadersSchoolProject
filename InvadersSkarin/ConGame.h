#ifndef INVADERS_CONGAME
#define INVADERS_CONGAME

#include "Game.h"
#include "ShipEntity.h"
#include "TextRes.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class ConGame : public Game
{
public:
	ConGame();
	sf::Sprite createSprite(std::string filename, sf::Vector2f position) override;
	void run() override;
	void draw(sf::Sprite &sprite) override;
	sf::Vector2f getWindowSize() const override;

private:
	TextRes mTextureManager;
	sf::RenderWindow mRenderWindow;
	
	void handleWindowEvents();
	void createShip();
	void updateEntities(float deltaTime);
	void drawEntities();

	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntities;
};

#endif