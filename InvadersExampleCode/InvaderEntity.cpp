namespace {
	const string textureFilename = "Invader.psd";
	const float RADIUS = 32.0f;
	const float FIRE_RATE = 2.0f;
	const float VELOCITY = 200.0f;
}

InvaderEntity::InvaderEntity(Game *game, Vector2f position, Vector2f direction) : 
	Entity(game),
	mSprite(game->createSprite(textureFilename, position)),
	mRadius(RADIUS),
	mFireDelta(1.0f / FIRE_RATE),
	mFireTime(0.0f),
	mDirection(direction),
	mVelocity(VELOCITY){
}

float InvaderEntity::getRadius() const {
	return mSprite.getRadius();
}

Vector2f InvaderEntity::getPosition() const {
	return mSprite.getPosition();
}

EntityType InvaderEntity::getType() const {
	return EntityType::SHIP;
}

EntityFaction InvaderEntity::getFaction() const {
	return EntityFaction::ENEMY;
}

void InvaderEntity::update(float deltaTime) {
	handleMovement(deltaTime);
	handleFire(deltaTime);
}

void InvaderEntity::collide(Entity *otherEntity) {
	if(otherEntity->getFaction() == EntityFaction::FRIEND){
		mGame->add(new ExplosionEntity(mGame, mSprite.getPosition()));
		mGame->remove(this);
	}
}

void InvaderEntity::draw() {
	mGame->draw(mSprite);
}

void InvaderEntity::handleMovement(float deltaTime) {
	float minX = mRadius;
	float maxX = mGame->getRenderWindow().getSize().x - mRadius;
	Vector2f position = mSprite.getPosition();
	position += deltaTime * mVelocity * mDirection;
	if(position.x < minX) {
		position.x = minX;
		mDirection.x = -mDirection.x;
	}
	else if (maxX < position.x) {
		position.x = maxX;
		mDirection.x = -mDirection.x;
	}
	mSprite.setPosition(position);
}

void InvaderEntity::handleFire(float deltaTime) {
	mFireTime += deltaTime;
	if(mFireDelta < mFireTime && mGame->isVisible(this)) {
		EntityFaction category = EntityFaction::ENEMY;
		Vector2f position = mSprite.getPosition();
		Vector2f direction = Vector2f(0.0f, 1.0f);
		mGame->add(new BulletEntity(mGame, category, position, direction));
		mFireTime = 0.0f;
	}
}