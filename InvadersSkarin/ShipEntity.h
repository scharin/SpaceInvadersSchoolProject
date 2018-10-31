#ifndef INVADERS_SHIP
#define INVADERS_SHIP

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"

class ShipEntity : public Entity
{
public:
	ShipEntity(Game *game, sf::Vector2f position);
	~ShipEntity();
	void update(float deltaTime);
	void collide(Entity *otherEntity) override;
	EntityFaction getFaction() const override;
	EntityType getType() const override;

private:
	float mFireTime;

	void updatePosition(float deltaTime);
	void constrainPosition();
	void handleFire(float deltaTime);
};

#endif