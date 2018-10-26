ConGame::ConGame() : 
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close){
	mTextureManager.loadTextures();
	createShip();
}

void ConGame::run() {
	while (mRenderWindow.isOpen()) {
		handleWindowEvents();
		mRenderWindow.clear(bgColor);


		drawEntities();
		mRenderWindow.display();
	}
}

void ConGame::createShip() {
	ShipEntity *ship = new ShipEntity(this);
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

void ConGame::draw(Sprite& sprite) {
	mRenderWindow.draw(sprite);
}

void ConGame::drawEntities() {
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		ShipEntity *ship = mEntities[i];
		ship->draw();
	}
}