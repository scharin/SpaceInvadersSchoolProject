#include "Entity.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"
#include "Game.h"

class InvaderEntity : public Entity{
public:
	InvaderEntity(Game *game, sf::Vector2f position, sf::Vector2f direction);
	virtual float getRadius() override;
	virtual sf::Vector2f getPosition() const override;
	virtual EntityType getType() const override;
	virtual EntityFaction getFaction() const override;
	virtual void update(float deltaTime) override;
	virtual void collide(Entity *otherEntity) override;
	virtual void draw() override;

private:
	void handleMovement(float deltaTime);
	void handleFire(float deltaTime);

	sf::Sprite mSprite; 		// SpriteObjekt
	float mRadius;				// Radie
	float mFireDelta;			// Tid mellan skott
	float mFireTime;			// Tid sedan senaste skott
	sf::Vector2f mDirection;	// Aktuell riktning (-1, 1) eller (1, 1)
	float mVelocity;			// Hastighet
};