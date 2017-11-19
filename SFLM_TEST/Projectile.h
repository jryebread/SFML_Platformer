#pragma once
#include "SFML\Graphics.hpp"
#include "Collider.h"
class Projectile
{
public:
	Projectile(sf::Texture *texture, float speed, bool faceRight, sf::Vector2f size, sf::Vector2f playerPos);
	~Projectile();

	void Projectile::Draw(sf::RenderWindow &window);
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
private:
	bool alive;
	sf::Vector2f velocity;
	float mSpeed;
	sf::RectangleShape body;
};

