#include "ConGame.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace {
	const string windowTitle = "Invaders - a16miksk";
	const VideoMode videoMode = VideoMode(768, 950);
	const Color bgColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;
}

ConGame::ConGame() : 
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close){
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
	mTextureManager.loadTextures();
	createShip();
}

void ConGame::run() {
	Clock frameClock;
	while (mRenderWindow.isOpen()) {
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		mRenderWindow.clear(bgColor);

		updateEntities(deltaTime);

		drawEntities();
		mRenderWindow.display();
	}
}

void ConGame::createShip() {
	Entity *ship = new ShipEntity(this);
	mEntities.push_back(ship);
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