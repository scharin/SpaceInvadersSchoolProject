#ifndef ASTEROID_GAME
#define ASTEROID_GAME

#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Coin.h"
#include "Asteroid.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>

class Game {
public:
	Game();
	void run();

private:
	sf::RenderWindow mRenderWindow;
	void handleWindowEvents();
	
	sf::Texture mShipTexture;
	sf::Texture mCoinTexture;
	sf::Texture mAsteroidTexture;
	Ship *mShip;
	Coin *mCoin;
	typedef std::vector<Asteroid*> AsteroidVector;
	AsteroidVector mAsteroids;
	
	void createShip();
	void updateShip(float deltaTime);
	void drawShip();
	
	void createCoin();
	void destroyCoin();
	void updateCoin(float deltaTime);
	void handleLostCoin();
	void handleCoinPickup();
	void drawCoin();

	sf::Clock mAsteroidSpawnClock;
	void createAsteroids();
	void updateAsteroid(float deltaTime);
	void drawAsteroid();
	void pruneAsteroids();
	void handleAsteroidCollisions();

	int mLevel;
	bool mGameOver;

	bool overlap(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1);
	bool overlap(Ship *ship, Coin *coin);
	bool overlap(Ship *ship, Asteroid *asteroid);

	// RandomStuff
	static std::mt19937 createGenerator();
	std::mt19937 mGenerator;
	sf::Vector2f getRandomVector(int rMin, int rMax, int rValue);
};

#endif