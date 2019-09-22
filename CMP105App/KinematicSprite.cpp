#include "KinematicSprite.h"



KinematicSprite::KinematicSprite()
{
	speed = 50.f;
	acceleration = 50.f;
	target = sf::Vector2f(1100, 300);
	moving = true;
}


KinematicSprite::~KinematicSprite()
{
}


void KinematicSprite::update(float dt)
{

	//IN CLASS WE ARE DEALING WITH KINEMATIC MOTION ON A STRAIGHT LINE BUT
	//That line may be any line in the game window  we are creating a line between
	//where the sprite is (getPosition) and the target
	//then we are normalizing it (aka getting the unit vector or the line if it had a distance of 1 unit)
	//and moving along that line
	//if you want to make the 

	// calculate direction and move
	direction = target - getPosition();
	direction = Vector::normalise(direction);
	
	////if you want to make the line just straight across the screen uncomment the next 1 lines
	//direction = sf::Vector2f(1,0);
	////////////////////////////MATHS 101 CODE HERE WEEK 1 & 2 Kinematics ////////////////////////////////////////////////

	////0. First way to try to move 0 acceleration / constant velocity 
	//sf::Vector2f u = velocity;
	//velocity = (direction * speed); // fixed speed
	//move(velocity*dt);

	////1. Second way to move calc new v based on acceleration, apply that velocity assuming lim dt -> 0
	////v = u + at   //here before we set velocity it is the u that it was last frame  accel is const and our t is the difference in time between frames aka deltaTime aka dt
	sf::Vector2f u = velocity;
	velocity = velocity + (direction * acceleration) * dt;	// accelerated towards the point
	setPosition(getPosition() + velocity * dt);  //s = (u +v)/2  * t -> //our previous pos is incorportated with the getPosition and as lim dt -> 0 u -> v  v+v/2*dt 

	////2. same as 1 but cannot assume dt is small (although in practice in video games dt usually == 0.0166667s and is considered small
	//sf::Vector2f u = velocity;
	//velocity = velocity + (direction * acceleration) * dt;	// accelerated towards the point
	//setPosition(getPosition() + (u + velocity)*0.5f*dt); //if we assume dt is of a significant value we take the average of last velocity and current

	////3. try solving the position without v
	////s = ut + 1/2 at^2
	////here we have yet to update the variable velocity so it is the vel of last frame aka u
	//setPosition(getPosition() + velocity*dt + 0.5f*direction*acceleration*dt*dt);
	//velocity = velocity + (direction * acceleration) * dt; ////we need to update velocity to store the change between frames

	

	///////////////////////////////////////END OF KINEMATIC CODE HERE /////////////////////////////////////////////////////////////////


	//THIS IS SOME GAMEPLAY CODE FEEL FREE TO CHANGE IT AND SEE WHAT HAPPENS 
	// if object is close enough to taget
	if (Vector::magnitude(target - getPosition()) < 10.f)
	{
		moving = false;
		setPosition(target);
	}

	// reset object (position and velocity)
	if (input->isKeyDown(sf::Keyboard::Num1))
	{
		setPosition(0, 0);
		setVelocity(0, 0);
		moving = true;
	}
	if (input->isKeyDown(sf::Keyboard::Num2))
	{
		setPosition(0, 250);
		setVelocity(0, 0);
		moving = true;
	}
	if (input->isKeyDown(sf::Keyboard::Num3))
	{
		setPosition(0, 500);
		setVelocity(0, 0);
		moving = true;
	}
}
