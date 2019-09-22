#include "MySprite.h"

MySprite::~MySprite()
{}

MySprite::MySprite() : RectangleShape()
{}

// override this function to provide functionality
void MySprite::update(float dt)
{
}

// Sets the velocity of the sprite
void MySprite::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}
void MySprite::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

// get sprite velocity
sf::Vector2f MySprite::getVelocity()
{
	return velocity;
}

// default function for collision update
void MySprite::updateCollisionBox()
{
	// Axis Aligned Bounding Box, based on sprite size and position.
	// Shape could be smaller/larger and offset if required.
	// Can be overwritten by child classes
	collisionBox.left += getPosition().x;
	collisionBox.top += getPosition().y;
}

// Reponse function, what the sprite does based on collision
// Colliding object is passed in for information
// e.g. compare sprite positions to determine new velocity direction.
// e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
void MySprite::collisionResponse(MySprite * sp)
{
}
