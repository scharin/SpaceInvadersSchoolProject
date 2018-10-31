#ifndef INVADERS_EXPLOSION
#define INVADERS_EXPLOSION

#include "SFML/Graphics.hpp"
#include "Entity.h"

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity(Game *game, sf::Vector2f position);
	~ExplosionEntity();
	void update(float deltaTime);
	void collide(Entity *otherEntity) override;
	EntityFaction getFaction() const override;
	EntityType getType() const override;

private:
	float mDurationDelta;
};

#endif