ConcreteGame::ConcreteGame() :
	mGenerator(createGenerator()),
	mRenderWindow(windowSize, windowTitle, Style::Titlebar | Style::Close),
	mTextureResources(),
	mEntities(),
	mNewEntities(),
	mOldEntities(),
	mTime(0.0f),
	mSpawnTime(0.0f),
	mGameOver(false) {
		mEntities.push_back(new ShipEntity(this));
}
void ConcreteGame::run() {
	Clock clock;
	while (mRenderWindow.isOpen() && !mGameOver) {
		float deltaTime = clock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		updateTime(deltaTime);
		updateEntities(deltaTime);
		spawnInvaders(deltaTime);
		collideEntitites();
		destroyOldEntities();
		destroyDistantEntities();
		integrateNewEntities();
		drawEntities();
		displayWindow();
	}
}

void ConcreteGame::updateTime(float deltaTime) {
	mTime += deltaTime;
}

void ConcreteGame::updateEntities(float deltaTime) {
	for(EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		mEntities[i]->update(deltaTime);
	}
}

void ConcreteGame::spawnInvader() {
	Vector2f position = getSpawnPosition();
	Vector2f direction = getSpawnDirection();
	InvaderEntity *invader = new InvaderEntity(this, position, direction);
	mNewEntities.push_back(invader);
}

void ConcreteGame::spawnInvaders(float deltaTime) {
	mSpawnTime += deltaTime;
	if (SPAWN_DELTA < mSpawnTime) {
		int spawnCount = int(SPAWN_BASE + mTime * SPAWN_INCREMENT);
		for (int i = 0; i < spawnCount; i++) {
			spawnInvader();
		}
		mSpawnTime = 0.0f;
	}
}

void ConcreteGame::integrateNewEntities() {
	for (EntityVector::size_type i = 0; i < mNewEntities.size(); i++) {
		mEntities.push_back(mNewEntities[i]);
	}
	mNewEntities.clear();
}

void ConcreteGame::destroyOldEntities() {
	EntityVector remainingEntities;
	for(EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if (isOld(entity)) {
			delete entity;
		}
		else {
			remainingEntities.push_back(entity);
		}
	}
	mOldEntities.clear();
	mEntities = remainingEntities;
}

void ConcreteGame::collideEntitites() {
	EntityVector visibleEntities = getVisibleEntities();
	for (EntityVector::size_type i = 0; i < visibleEntities.size(); i++) {
		Entity *entity0 = visibleEntities[i];
		for (EntityVector::size_type j = i+1; j < visibleEntities.size(); j++){
			Entity *entity1 = visibleEntities[j];
			if (overlap(entity0, entity1)){
				entity0->collide(entity1);
				entity1->collide(entity0);
			}
		}
	}
}

void ConcreteGame::drawEntities(EntityType type) {
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if(entity->getType() == type) {
			entity->draw();
		}
	}
}

void ConcreteGame::drawEntities() {
	drawEntities(EntityType::PROJECTILE);
	drawEntities(EntityType::SHIP);
	drawEntities(EntityType::EFFECT);
}

Sprite ConcreteGame::CreateSprite(string filename, Vector2f position){
	Sprite sprite(getTexture(filename));
	float originX = 0.5f * sprite.getLocalBounds().width;
	float originY = 0.5f * sprite.getLocalBounds().height;
	Vector2f origin(originX, originY);
	sprite.setOrigin(origin);
	sprite.setPosition(position);
	return sprite;
}

Texture& ConcreteGame::getTexture(string filename) {
	for(TextureResources::size_type i = 0; i < mTextureResources.size(); i++) {
		if(filename == mTextureResources[i]->getFilename()){
			return mTextureResources[i]->getTexture();
		}
	}
	Texture texture;
	texture.loadFromFile(filename);
	TextureResource *textureResource = new TextureResource(filename, texture);
	mTextureResources.push_back(textureResource);
	return textureResource->getTexture();
}

// Random stuff
float ConcreteGame::getRandomFloat(float min, float max) {
	uniform_real_distribution<float> distribution(min, max);
	return distribution(mGenerator);
}
bool ConcreteGame::getRandomBoolean(float probability) {
	float value = getRandomFloat(0.0f, 1.0f);
	if (value < probability) {
		return true;
	}
	else {
		return false;
	}
}
mt19937 ConcreteGame::createGenerator() {
	random_device randomDevice;
	mt19937 generator(randomDevice());
	return generator;
}