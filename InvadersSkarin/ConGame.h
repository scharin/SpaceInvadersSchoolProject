#ifndef INVADERS_CONGAME
#define INVADERS_CONGAME

#include "Game.h"
#include "ShipEntity.h"
#include "InvaderEntity.h"
#include "Bullet.h"
#include "TextRes.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <random>

class ConGame : public Game
{
public:
	ConGame();
	~ConGame() override;
	sf::Sprite createSprite(std::string filename, sf::Vector2f position) override;
	void run() override;
	void draw(sf::Sprite &sprite) override;
	sf::Vector2f getWindowSize() const override;
	void remove(Entity *entity) override;

private:
	TextRes mTextureManager;
	sf::RenderWindow mRenderWindow;
	float mTime;
	float mSpawnTime;
	
	void handleWindowEvents();
	void spawnInvaders(float deltaTime);
	void spawnInvader();
	sf::Vector2f getSpawnDirection();
	sf::Vector2f getSpawnPosition();
	void updateEntities(float deltaTime);
	void integrateNewEntities();
	void collideEntities();
	void destroyOldEntites();
	bool overlap(Entity *entity0, Entity *entity1);
	bool overlap(sf::Vector2f pos0, float rad0, sf::Vector2f pos1, float rad1);
	void drawEntities();
	bool isVisible(Entity *entity) override;

	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntities;
	EntityVector mNewEntities;
	EntityVector mOldEntities;

	// Random stuff
	static std::mt19937 createGenerator();
	std::mt19937 mGenerator;
	bool getRandomBoolean(float probability);
	float getRandomFloat(float min, float max);
};

#endif