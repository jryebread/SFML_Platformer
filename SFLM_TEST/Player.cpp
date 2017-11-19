#include "Player.h"


Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
: animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	
	faceRight = true;
	body.setSize(sf::Vector2f(20.0f, 44.0f));
	body.setOrigin(body.getSize()/2.0f);
	body.setPosition(200.0f, 210.0f);
	body.setTexture(texture);
	//body.setFillColor(sf::Color::Blue);
	
}

void Player::Update(float deltaTime, std::vector<Projectile> &projectiles, sf::Texture *bulletTexture)
{
	velocity.x = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	isMoving = velocity.x == 0 ? false : true;

	bool isKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	if ((isKeyPressed && !wasKeyPressed ) && canJump && jumpDelay.getElapsedTime().asSeconds() >= 0.75) //JUMP
	{
		jumpDelay.restart();
		canJump = false;
		//square root (2.0f * gravity * jumpHeight);
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	if (canJump == false && attackBool == false) //JUMP ANIM
	{
		row = 5;
		animation.UpdateJump(row, Animation::xImage::Jump, deltaTime, faceRight, canJump, velocity);
	}
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && attackDelay == 0) || attackBool == true) && !isMoving) //ATTACK ANIM && canJump at the end for no attacking while jumping
	{
		attackBool = true;
		row = 1;
		this->attackBool = animation.UpdateAttack(row, Animation::xImage::Shoot, deltaTime, faceRight, attackBool);
		if (attackBool == false)
		{
			//then the attack has ended, so start the attack delay timer
			attackDelay = 30.0f;
			//attack here since animation has ended
			projectiles.push_back(Projectile(bulletTexture, 10, faceRight, sf::Vector2f(10, 30), body.getPosition()));
		}
	}

	//Attack Delay
	if (attackDelay != 0)
		attackDelay -= 1.0f;
	//Gravity
	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f && canJump && attackBool == false) // IDLE
	{
		row = 0;
		animation.Update(row, Animation::xImage::Idle, deltaTime, faceRight);
	}
	else if(canJump && attackBool == false) //RUN
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //change
			faceRight = false;
		else
			faceRight = true;
		row = 0;
		animation.Update(row, Animation::xImage::Run, deltaTime, faceRight);
	}
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	wasKeyPressed = isKeyPressed;
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left stopping player
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		velocity.y = 0.0f;
		
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}

}

int Player::getX() {
	return body.getPosition().x;
}

int Player::getY() {
	return body.getPosition().y;
}