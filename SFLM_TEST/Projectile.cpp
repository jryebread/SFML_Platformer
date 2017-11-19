#include "Projectile.h"

Projectile::Projectile(sf::Texture *texture,float speed, bool faceRight,  sf::Vector2f size, sf::Vector2f playerPos)
{
	mSpeed = speed;
	if (faceRight)
		velocity.x = mSpeed;
	else
		velocity.x = -mSpeed;
	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(playerPos.x, playerPos.y);
	body.setTexture(texture);
	velocity.y = - (mSpeed / 2);
}

Projectile::~Projectile()
{
}

void Projectile::Draw(sf::RenderWindow &window)
{
	body.move(velocity);
	velocity.y += 0.9f;
	window.draw(body);
}



//int Projectile::getRight()
//{
//	return body.getPosition().x + body.getSize().x;
//}
//
//int Projectile::getLeft()
//{
//	return body.getPosition().x;
//}
//
//int Projectile::getTop()
//{
//	return body.getPosition().y;
//}
//
//int Projectile::getBottom()
//{
//	return body.getPosition().y + body.getSize().y;
//}
