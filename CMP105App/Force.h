#pragma once

#include "framework/Vector.h"


class TransientForce
{

public:

	sf::Vector2f force;
	float age;
	float maxAge = 10.0f;
	
	//for visual
	sf::Vector2i startPos, endPos;

	void Set(sf::Vector2f _force, float _age, sf::Vector2i start, sf::Vector2i end, float _maxAge = 10)
	{
		force = _force;
		age = _age;
		startPos = start;
		endPos = end;
		maxAge = _maxAge;
	}
	bool ReachedMaxAge() const { return age >= maxAge; }
};

