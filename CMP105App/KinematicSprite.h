#pragma once
#include "MySprite.h"
#include "framework/Vector.h"

class KinematicSprite :
	public MySprite
{
public:
	KinematicSprite();  //constructor where initialization / setup code goes
	~KinematicSprite(); //destructor where clean up of "on end" code goes

	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	void setAcceleration(float acc) { acceleration = acc; }; //setter to allow the main game to change the acceleration of sprite
	float getAcceleration() { return acceleration; }; // getter so main game can see what the current value of the acceleration is
	void setTarget(sf::Vector2f tar) { target = tar; }; //gives a target location for the sprite to navigate toward


protected:
	float acceleration;

	//here we are separating out speed and direction aka velocity
	float speed; 
	sf::Vector2f direction;
	//desired destination
	sf::Vector2f target;
	//flag to see if the sprite is currently moving
	bool moving;
};

