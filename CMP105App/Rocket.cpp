#include "Rocket.h"
#include "framework/Vector.h"



Rocket::Rocket() :
	cForceGravity(0, -9.8f),
	cResitanceForceMagnitude(0.0f)
{
	speed = 50.f;
	acceleration = 50.f;
	mass = 2; //mass must be positive
	mass = fabs(mass);
	
	
}


void Rocket::update(float dt)
{



	////if you want to make the line just straight across the screen uncomment the next 1 lines
	//direction = sf::Vector2f(1,0);
	////////////////////////////MATHS 101 CODE HERE WEEK 3 Forces ////////////////////////////////////////////////
	//F = ma  we need to sum all forces including input, gravity, and resistance 
	sf::Vector2f totalForce = forceFromInput + cForceGravity;
	float forceMag = Vector::magnitude(totalForce);
	sf::Vector2f forceDirection = Vector::normalise(totalForce);

	//Resistance like air resist/ friction etc always opposes the direction of the force, so we can subtract on it's magnitude

	forceMag -= fabs(cResitanceForceMagnitude); //fabs is a function float absolute value, as resistance is always an absolute value
	if (forceMag < 0)
	{
		forceMag = 0;  //if we have some force to move the rocket but that is less than the resistance we do not have enough force to overcome resistance hence resetting forcemag to 0
	}


	//if F = ma then a = F/m
	//sanity check, rocket must have some mass
	if (mass < 0.01)
	{
		mass = 0.01;
	}

	acceleration = forceMag / mass;
	direction = forceDirection; //the direction of the acceleration is the direction of the force as acceleration can occur in R3 and so may Force, while mass is always a scalar




	////1. Second way to move calc new v based on acceleration, apply that velocity assuming lim dt -> 0
	////v = u + at   //here before we set velocity it is the u that it was last frame  accel is const and our t is the difference in time between frames aka deltaTime aka dt
	sf::Vector2f u = velocity;
	velocity = velocity + (direction * acceleration) * dt;	// accelerated towards the point
	setPosition(getPosition() + velocity * dt);  //s = (u +v)/2  * t -> //our previous pos is incorportated with the getPosition and as lim dt -> 0 u -> v  v+v/2*dt 

	////2. same as 1 but cannot assume dt is small (although in practice in video games dt usually == 0.0166667s and is considered small
	//sf::Vector2f u = velocity;
	//velocity = velocity + (direction * acceleration) * dt;	// accelerated towards the point
	//setPosition(getPosition() + (u + velocity)*0.5f*dt); //if we assume dt is of a significant value we take the average of last velocity and current
}

Rocket::~Rocket()
{
}
