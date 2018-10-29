#ifndef INVADERS_ENTITY
#define INVADERS_ENTITY


class Game;

#include "SFML/Graphics.hpp"
#include "Game.h"

enum class EntityType{PROJECTILE, SHIP, EFFECT};
enum class EntityFaction{FRIEND, ENEMY, NEUTRAL};

class Entity
{
public:
	Entity(Game *game);
	// "Virtual" functions, need to be set in each entity.
	virtual ~Entity();
	virtual void update(float deltaTime) = 0;
	virtual EntityType getType() const = 0;
	virtual EntityFaction getFaction() const = 0;
	virtual void collide(Entity *otherEntity) = 0;
	
	// These functions are the same for each entity
	void draw();
	sf::Vector2f getPosition() const;
	float getRadius() const;

protected:
	// Variables each entity has
	Game *mGame;
	sf::Sprite mSprite;

	float mVelocity;
	float mRadius;
};


#endif