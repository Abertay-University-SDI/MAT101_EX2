#include "Rocket.h"
#include "framework/Vector.h"
#include "Force.h"

#define RAD2DEG (180.0/3.14159)

Rocket::Rocket() :
	cForceGravity(0, -9.8f),
	cResitanceForceMagnitude(0.0f),
	pWindow(nullptr)
{
	speed = 50.f;
	acceleration = 50.f;
	mass = 2; //mass must be positive
	mass = fabs(mass);

	drag = false;

	for (int i = 0; i < MAX_FORCES; ++i)
	{
		forces[i] = nullptr;
	}
	
	line.pts[0].color = sf::Color::Green;
	line.pts[0].position = sf::Vector2f(0, 0);
	line.pts[1].color = sf::Color::Green;
	line.pts[1].position = sf::Vector2f(0, 0);
}


void Rocket::update(float dt)
{
	handleInput(dt);

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
	if (mass < 0.01f)
	{
		mass = 0.01f;
	}

	acceleration = forceMag / mass;
	direction = forceDirection; //the direction of the acceleration is the direction of the force as acceleration can occur in R3 and so may Force, while mass is always a scalar
	direction.y *= -1; //handle invert y of 2D plane 
	
	setRotation (acosf(Vector::dot(direction, sf::Vector2f( 0, -1 )))*RAD2DEG);


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


void Rocket::handleInput(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !drag)
	{
		if (!drag)
		{
			// Left mouse button pressed
			//MessageBox(NULL, L"Right click", L"Mouse press", MB_OK);
			startPos = sf::Mouse::getPosition(*pWindow);
			drag = true;
			line.pts[0].position.x = startPos.x;
			line.pts[0].position.y = startPos.y;
			line.pts[1].position.x = startPos.x;
			line.pts[1].position.y = startPos.y;
		}
		
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && drag)
	{
		// Left mouse button pressed
		//MessageBox(NULL, L"Right click", L"Mouse press", MB_OK);
		endPos = sf::Mouse::getPosition(*pWindow);
		drag = false;
		std::string diffx = std::to_string(endPos.x - startPos.x);
		std::string diffy = std::to_string(endPos.y - startPos.y);
		std::string distance = "diffx = " + diffx + ", diffy = " + diffy;
		line.pts[1].position.x = sf::Mouse::getPosition(*pWindow).x;
		line.pts[1].position.y = sf::Mouse::getPosition(*pWindow).y;
		pText->setString(distance);
	}
	else if (drag)

	{
		line.pts[1].position.x = sf::Mouse::getPosition(*pWindow).x;
		line.pts[1].position.y = sf::Mouse::getPosition(*pWindow).y;
	}
}


void Rocket::updateForces(float dt)
{
	for (int i = 0; i < MAX_FORCES; ++i)
	{
		if (forces[i] != nullptr)
		{
			forces[i]->age += dt;
			if (forces[i]->ReachedMaxAge())
			{
				delete forces[i];
				forces[i] = nullptr;
			}
		}
	}
}
void Rocket::addForce(sf::Vector2f f, sf::Vector2i s, sf::Vector2i e)
{
	//find an empty slot or remove oldest
	int i = 0;
	TransientForce* tempOldestForce = nullptr;
	int tempForceIndex = 0;;
	for (i = 0; i < MAX_FORCES; ++i)
	{
		if (forces[i] == nullptr)
		{
			//put new one here!
			tempForceIndex = i;
			break; //if we found an empty one use that one first
		}
		if (tempOldestForce == nullptr)
		{
			tempOldestForce = forces[i];
			tempForceIndex = i;
		}
		else if (tempOldestForce->age < forces[i]->age)
		{
			tempOldestForce = forces[i];
			tempForceIndex = i;
		}
	}

	if (tempOldestForce != nullptr)
	{
		delete tempOldestForce;
	}
	//create a new force
	forces[tempForceIndex] = new TransientForce();
	forces[tempForceIndex]->Set(f, 0, s, e);

	
}


void Rocket::Draw()
{
	pWindow->draw(*this);
	line.Draw(pWindow);
}


Rocket::~Rocket()
{
	for (int i = 0; i < MAX_FORCES; ++i)
	{
		if (forces[i] != nullptr)
		{
			delete forces[i];
			forces[i] = nullptr;
		}
	}
}
