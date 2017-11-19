#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Animation.h"
class Enemy
{
public:
	Enemy(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed);


	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider getCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	Animation animation;
	unsigned row;
	float speed = 0.0;
	bool faceRight;
};

