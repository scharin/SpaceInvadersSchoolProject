#include "ExplosionEntity.h"

using namespace std;
using namespace sf;

namespace {
	const float RADIUS = 15.0f;
	const float VELOCITY = .0f;
	const float EFFECT_SHOW = .4f;
}

ExplosionEntity::ExplosionEntity(Game *game, Vector2f position) :
	Entity(game)
{
	mSprite = mGame->createSprite("explosion", position);
	mRadius = RADIUS;
	mVelocity = VELOCITY;
	mDurationDelta = 0.0f;
}

ExplosionEntity::~ExplosionEntity()
{
}

void ExplosionEntity::update(float deltaTime) {
	mDurationDelta += deltaTime;
	if (EFFECT_SHOW < mDurationDelta)
		mGame->remove(this);
}

void ExplosionEntity::collide(Entity *otherEntity) {
}

EntityFaction ExplosionEntity::getFaction() const {
	return EntityFaction::NEUTRAL;
}
EntityType ExplosionEntity::getType() const {
	return EntityType::EFFECT;
}
