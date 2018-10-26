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
	virtual ~Entity();
	virtual void update(float deltaTime) = 0;
	
	void draw();
	sf::Vector2f getPosition() const;

protected:
	Game *mGame;
	sf::Sprite mSprite;

	float mVelocity;
	float mRadius;
	
};


#endif // !INVADERS_ENTITY