#pragma once
#include "MySprite.h"
#include "Line.h"
#include "Force.h"

class Rocket :
	public MySprite
{
public:
	Rocket();
	~Rocket(); 
	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	void setAcceleration(float acc) { acceleration = acc; }; //setter to allow the main game to change the acceleration of sprite
	float getAcceleration() { return acceleration; }; // getter so main game can see what the current value of the acceleration is
	void addForce(sf::Vector2f f, sf::Vector2i s, sf::Vector2i e); //Adds a force to the total forces acting on the rocket
	void setRenderWindow(sf::RenderWindow* w) { pWindow = w; }
	void setText(sf::Text* t) { pText = t; }

	void Draw();
protected:
	void handleInput(float dt);
	void updateForces(float dt);
	float acceleration;

	//here we are separating out speed and direction aka velocity

	sf::Vector2f direction;
	//desired destination
	sf::Vector2f forceFromInput;

	const sf::Vector2f cGravity;
	const float cResitanceForceMagnitude;
	float mass;
	//flag to see if the sprite is currently moving
	bool moving;
	bool drag;

	sf::RenderWindow* pWindow;
	sf::Vector2i startPos, endPos;
	sf::Text* pText;
	static const int MAX_FORCES = 5;
	TransientForce forces[MAX_FORCES];

	Line line;

};

