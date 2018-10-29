#include "ConGame.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace {
	const string windowTitle = "Invaders - a16miksk";
	const VideoMode videoMode = VideoMode(768, 950);
	const Color bgColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;

	const float INVADERS_SPAWN_DELTA = 6.0f;
	const float INVADERS_SPAWN_BASE = 1.0f;
	const float INVADERS_SPAWN_INCREMENT = 0.1f;
}

ConGame::ConGame() : 
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	mTime(0.0f),
	mSpawnTime(3.0f),
	mEntities(),
	mNewEntities(),
	mOldEntities(),
	mGenerator(createGenerator()){
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
	mTextureManager.loadTextures();
	mEntities.push_back(new ShipEntity(this, Vector2f(360, 500)));
}
ConGame::~ConGame() {
	cout << "----------\nGame ends\nDestroying all entities\n----------\n";
	while (!mEntities.empty()) {
		delete mEntities.back();
		mEntities.pop_back();
	}
	while (!mNewEntities.empty()) {
		delete mNewEntities.back();
		mNewEntities.pop_back();
	}
}

void ConGame::run() {
	Clock frameClock;
	while (mRenderWindow.isOpen()) {
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		mRenderWindow.clear(bgColor);
		mTime += deltaTime;

		updateEntities(deltaTime);
		spawnInvaders(deltaTime);
		collideEntities();
		destroyOldEntites();
		integrateNewEntities();

		drawEntities();
		mRenderWindow.display();
	}
}

void ConGame::spawnInvaders(float deltaTime) {
	mSpawnTime += deltaTime;
	if (INVADERS_SPAWN_DELTA < mSpawnTime) {
		int spawnCount = int(INVADERS_SPAWN_BASE + mTime * INVADERS_SPAWN_INCREMENT);
		for (int i = 0; i < spawnCount; i++) {
			spawnInvader();
		}
		mSpawnTime = 0.0f;
	}
}

void ConGame::spawnInvader() {
	Vector2f position = getSpawnPosition();
	Vector2f direction = getSpawnDirection();
	cout << "Invader X: " << position.x << " Y: " << position.y << endl;
	
	InvaderEntity *invader = new InvaderEntity(this, position, direction);
	mNewEntities.push_back(invader);
}

Vector2f ConGame::getSpawnDirection() {
	if (getRandomBoolean(0.5f)) return Vector2f(1, 1);
	else return Vector2f(-1, 1);
}

Vector2f ConGame::getSpawnPosition() {
	float xAxis = getRandomFloat(32.0f, mRenderWindow.getSize().x - 32.0f);
	float yAxis = getRandomFloat(50.0f, 300.0f);
	return Vector2f(xAxis, -yAxis);
}

void ConGame::integrateNewEntities() {
	for (EntityVector::size_type i = 0; i < mNewEntities.size(); i++) {
		mEntities.push_back(mNewEntities[i]);
	}
	mNewEntities.clear();
}

void ConGame::destroyOldEntites() {
	EntityVector remainingEntities;
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if (find(mOldEntities.begin(), mOldEntities.end(), entity) != mOldEntities.end())
			delete entity;
		else
			remainingEntities.push_back(entity);
	}
	mOldEntities.clear();
	mEntities = remainingEntities;
}

void ConGame::collideEntities() {
	//EntityVector visibleEntities = getVisibleEntities();
	//for (EntityVector::size_type i = 0; i < visibleEntities.size; i++) {
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity0 = mEntities[i]; //visibleEntities[i];
		//for (EntityVector::size_type j = i + 1; j < visibleEntities.size(); j++) {
		for (EntityVector::size_type j = i + 1; j < mEntities.size(); j++) {
			Entity *entity1 = mEntities[j]; //visibleEntities[j];
			if (overlap(entity0, entity1)) {
				entity0->collide(entity1);
				entity1->collide(entity0);
			}
		}
	}
}

bool ConGame::overlap(Entity *entity0, Entity *entity1) {
	Vector2f entity0pos = entity0->getPosition();
	Vector2f entity1pos = entity1->getPosition();
	float entity0rad = entity0->getRadius();
	float entity1rad = entity1->getRadius();
	return overlap(entity0pos, entity0rad, entity1pos, entity1rad);
}
bool ConGame::overlap(Vector2f pos0, float rad0, Vector2f pos1, float rad1) {
	float deltaX = pos0.x - pos1.x;
	float deltaY = pos0.y - pos1.y;
	float radiusSum = rad0 + rad1;
	return deltaX * deltaX + deltaY * deltaY < radiusSum * radiusSum;
}

Sprite ConGame::createSprite(string filename, Vector2f position) {
	Sprite sprite;
	sprite.setTexture(mTextureManager.getRef(filename));
	sprite.setOrigin(
		Vector2f(
			sprite.getGlobalBounds().height / 2,
			sprite.getGlobalBounds().width / 2
		)
	);
	sprite.setPosition(position);
	
	return sprite;
}

void ConGame::updateEntities(float deltaTime) {
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		mEntities[i]->update(deltaTime);
	}
}

void ConGame::draw(Sprite& sprite) {
	mRenderWindow.draw(sprite);
}

void ConGame::drawEntities() {
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		entity->draw();
	}
}

void ConGame::handleWindowEvents() {
	Event event;
	while (mRenderWindow.pollEvent(event)) {
		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
			mRenderWindow.close();
		}
	}
}

Vector2f ConGame::getWindowSize() const{
	return Vector2f(mRenderWindow.getSize());
}

void ConGame::remove(Entity *entity) {
	mOldEntities.push_back(entity);
}

bool ConGame::isVisible(Entity *entity) {
	Vector2f pos = entity->getPosition();
	/* Checks if the entity is visible (Inside the gameWindow)
	 * First checks if it's outside the y-axis, then checks the x-axis.
	 * If any of these conditions is true, that an entity is outside the window
	 * it returns false
	 */
	if ((pos.y < 0 || pos.y > float(mRenderWindow.getSize().y))
		|| (pos.x < 0 || pos.x > float(mRenderWindow.getSize().x))) return false;
	else return true;
}
// Random stuff
mt19937 ConGame::createGenerator() {
	random_device randomDevice;
	mt19937 randomGenerator(randomDevice());
	return randomGenerator;
}
bool ConGame::getRandomBoolean(float probability) {
	float value = getRandomFloat(0.0f, 1.0f);
	if (value < probability) return true;
	else return false;
}
float ConGame::getRandomFloat(float min, float max) {
	uniform_real_distribution<float> distribution(min, max);
	return distribution(mGenerator);
}