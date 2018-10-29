#ifndef INVADERS_INVADER
#define INVADERS_INVADER

#include "SFML/Graphics.hpp"
#include "Entity.h"

class InvaderEntity : public Entity
{
public:
	InvaderEntity(Game *game, sf::Vector2f position, sf::Vector2f direction);
	~InvaderEntity();
	void update(float deltaTime);
	void collide(Entity *otherEntity) override;
	EntityFaction getFaction() const override;
	EntityType getType() const override;

private:
	void updatePosition(float deltaTime);
	void handleFire();

	sf::Vector2f mDirection;
};

#endif