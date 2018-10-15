#include "Game.h"

using namespace sf;
using namespace std;

namespace {
	const string windowTitle = "Asteroids game - a16miksk";
	const VideoMode videoMode = VideoMode(768, 950);
	const Color bgColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;
	const int START_LEVEL = 1;

	const float SHIP_RADIUS = 20.0f;
	const float SHIP_VELOCITY = 400.0f;
	const Vector2f SHIP_START_POS(500, 500);

	const float COIN_RADIUS = 16.0f;
	const Vector2f COIN_VELOCITY(0, 80);

	const float ASTEROIDS_RADIUS = 32.0f;
	const float ASTEROIDS_SPAWN_DELTA = 1.0f;
	const float ASTEROIDS_SPAWN_COUNT_BASE = 1.0f;
	const float ASTEROIDS_SPAWN_COUNT_INCREMENT = 0.5f;
	const float ASTEROIDS_MIN_VELOCITY = 80.f;
	const float ASTEROIDS_MAX_VELOCITY = 200.0f;
}

Game::Game() :
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	mShip(0),
	mCoin(0),
	mAsteroids(),
	mLevel(START_LEVEL),
	mGenerator(createGenerator()),
	mGameOver(false),
	mAsteroidSpawnClock(){
	createText();
	mShipTexture.loadFromFile("ShipSprite.psd");
	createShip();
	mCoinTexture.loadFromFile("CoinSprite.psd");
	createCoin();
	mAsteroidTexture.loadFromFile("AsteroidSprite.psd");
	createAsteroids();
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
}

void Game::run() {
	Clock frameClock;
	Clock scoreClock;
	while(mRenderWindow.isOpen() && !mGameOver) {
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		mRenderWindow.clear(bgColor);

		updateShip(deltaTime);
		drawShip();
		
		updateCoin(deltaTime);
		handleLostCoin();
		handleCoinPickup();
		drawCoin();

		createAsteroids();
		updateAsteroid(deltaTime);
		drawAsteroid();
		pruneAsteroids();
		handleAsteroidCollisions();

		mRenderWindow.display();
	}

}

void Game::handleWindowEvents() {
	Event event;
	while (mRenderWindow.pollEvent(event)) {
		if (event.type == Event::Closed) {
			mRenderWindow.close();
		}
	}
}

void Game::createShip() {
	mShip = new Ship(
		mRenderWindow,
		mShipTexture,
		SHIP_START_POS,
		SHIP_VELOCITY,
		SHIP_RADIUS
	);
}

void Game::updateShip(float deltaTime) {
	mShip->update(deltaTime);
}

void Game::drawShip() {
	mShip->draw();
}

void Game::createCoin() {
	mCoin = new Coin(
		mRenderWindow,
		mCoinTexture,
		getRandomVector(20, (mRenderWindow.getSize().x-20), 1),
		COIN_VELOCITY,
		COIN_RADIUS
	);
}

void Game::destroyCoin() {
	delete mCoin;
}

void Game::updateCoin(float deltaTime) {
	mCoin->update(deltaTime);
}

void Game::handleLostCoin() {
	if (COIN_RADIUS + mRenderWindow.getSize().y < mCoin->getPosition().y) {
		mGameOver = true;
	}
}

void Game::handleCoinPickup() {
	if (overlap(mShip, mCoin)) {
		mLevel++;
		destroyCoin();
		createCoin();
		cout << "Level up, Currently level: " << mLevel << endl;
	}
}

void Game::drawCoin() {
	mCoin->draw();
}

void Game::createAsteroids() {
	if (ASTEROIDS_SPAWN_DELTA < mAsteroidSpawnClock.getElapsedTime().asSeconds()) {
		int spawnCount = int(ASTEROIDS_SPAWN_COUNT_BASE + mLevel * ASTEROIDS_SPAWN_COUNT_INCREMENT);
		for (int i = 0; i < spawnCount; i++) {
			Asteroid *asteroidEntity = new Asteroid(
				mRenderWindow,
				mAsteroidTexture,
				getRandomVector(20, (mRenderWindow.getSize().x - 20), 1),
				getRandomVector(ASTEROIDS_MIN_VELOCITY, ASTEROIDS_MAX_VELOCITY, 2),
				ASTEROIDS_RADIUS
			);
			mAsteroids.push_back(asteroidEntity);
		}
		mAsteroidSpawnClock.restart();
	}
}

void Game::updateAsteroid(float deltaTime) {
	for (AsteroidVector::size_type i = 0; i < mAsteroids.size(); i++) {
		mAsteroids[i]->update(deltaTime);
	}
}

void Game::drawAsteroid() {
	for (AsteroidVector::size_type i = 0; i < mAsteroids.size(); i++) {
		mAsteroids[i]->draw();
	}
}

void Game::pruneAsteroids() {
	float maxY = mRenderWindow.getSize().y + ASTEROIDS_RADIUS;
	AsteroidVector remainingAsteroids;
	for (AsteroidVector::size_type i = 0; i < mAsteroids.size(); i++) {
		Asteroid *asteroid = mAsteroids[i];
		if (asteroid->getPosition().y < maxY) {
			remainingAsteroids.push_back(asteroid);
		}
		else {
			delete asteroid;
		}
	}
	mAsteroids = remainingAsteroids;
}

void Game::handleAsteroidCollisions() {
	for (AsteroidVector::size_type i = 0; i < mAsteroids.size(); i++) {
		if (overlap(mShip, mAsteroids[i])) {
			mGameOver = true;
		}
	}
}

bool Game::overlap(Vector2f position0, float radius0, Vector2f position1, float radius1) {
	float deltaX = position0.x - position1.x;
	float deltaY = position0.y - position1.y;
	float radiusSum = radius0 + radius1;
	return deltaX * deltaX + deltaY * deltaY < radiusSum * radiusSum;
}

bool Game::overlap(Ship *ship, Coin *coin) {
	Vector2f shipPosition = ship->getPosition();
	Vector2f coinPosition = coin->getPosition();
	return overlap(shipPosition, SHIP_RADIUS, coinPosition, COIN_RADIUS);
}

bool Game::overlap(Ship *ship, Asteroid *asteroid) {
	Vector2f shipPosition = ship->getPosition();
	Vector2f asteroidPosition = asteroid->getPosition();
	return overlap(shipPosition, SHIP_RADIUS, asteroidPosition, ASTEROIDS_RADIUS);
}

mt19937 Game::createGenerator() {
	random_device randomDevice;
	mt19937 randomGenerator(randomDevice());
	return randomGenerator;
}

Vector2f Game::getRandomVector(int rMin, int rMax, int rValue) {
	int randValue;
	Vector2f rVector;
	uniform_int_distribution<int> distribution(rMin, rMax);
	randValue = distribution(mGenerator);
	if (rValue == 1) {
		rVector = Vector2f(randValue, -100);
	}
	else if (rValue == 2) {
		rVector = Vector2f(0, randValue);
	}

	return rVector;
}