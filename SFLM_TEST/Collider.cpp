#include "Collider.h"

Collider::Collider(sf::RectangleShape & body)
	:body(body)
{
}

bool Collider::CheckCollision(Collider & other,sf::Vector2f &direction, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = this->GetPosition();
	sf::Vector2f thisHalfSize = this->GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	//AAB Collision detection
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f); //clamping between 0 and 1
		
		if (intersectX > intersectY) //push x axis
		{
			if (deltaX > 0.0f)
			{
				this->Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				this->Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else //push y axis
		{
			if (deltaY > 0.0f)
			{
				this->Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				this->Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}

	return false;
}


