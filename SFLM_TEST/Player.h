#pragma once
#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Collider.h"
#include "Projectile.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	
	void Update(float deltaTime, std::vector<Projectile> &projectiles, sf::Texture *bulletTexture);
	void Draw(sf::RenderWindow &window);
	void onCollision(sf::Vector2f direction);
	int getX();
	int getY();
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider getCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	Animation animation;
	unsigned row;
	float speed = 0.0;
	bool faceRight;

	bool wasKeyPressed = false;
	bool attackBool = false;
	float attackDelay = 0.0f;
	sf::Clock jumpDelay;
	bool canJump;
	float jumpHeight;
	bool isMoving = false;
};

