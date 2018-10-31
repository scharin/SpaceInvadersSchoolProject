#ifndef INVADERS_BULLET
#define INVADERS_BULLET

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <string>

class BulletEntity : public Entity
{
public:
	BulletEntity(Game *game, EntityFaction faction, sf::Vector2f position, sf::Vector2f direction);
	~BulletEntity();
	void update(float deltaTime) override;
	EntityType getType() const override;
	EntityFaction getFaction() const override;
	void collide(Entity *otherEntity) override;

private:
	EntityFaction mFaction;
	sf::Vector2f mDirection;
};


#endif