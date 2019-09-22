#pragma once
#include "MySprite.h"
class Rocket :
	public MySprite
{
public:
	Rocket();
	~Rocket(); 
	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	void setAcceleration(float acc) { acceleration = acc; }; //setter to allow the main game to change the acceleration of sprite
	float getAcceleration() { return acceleration; }; // getter so main game can see what the current value of the acceleration is
	void addForce(sf::Vector2f tar); //Adds a force to the total forces acting on the rocket

protected:
	float acceleration;

	//here we are separating out speed and direction aka velocity
	float speed;
	sf::Vector2f direction;
	//desired destination
	sf::Vector2f forceFromInput;

	const sf::Vector2f cForceGravity;
	const float cResitanceForceMagnitude;
	float mass;
	//flag to see if the sprite is currently moving
	bool moving;
};

