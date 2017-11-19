#include "Animation.h"



Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width = (texture->getSize().x / float(imageCount.x)); //FIX /2
	uvRect.height = (texture->getSize().y / float(imageCount.y));

}

void Animation::Update(int row, xImage rowImages, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;
	
	if (totalTime >= switchTime)
	{

		totalTime -= switchTime;
		currentImage.x++;
	
		if (currentImage.x >= rowImages )
		{
			if (rowImages == xImage::Run)
				currentImage.x = 4;
			else
				currentImage.x = 0;
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}

bool Animation::UpdateAttack(int row, xImage rowImages, float deltaTime, bool faceRight, bool attackBool)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		if(attackBool)
			currentImage.x++;

		if (currentImage.x >= rowImages)
		{
			attackBool = false;
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{

		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	return attackBool;
}

void Animation::UpdateJump(int row, xImage rowImages, float deltaTime, bool faceRight, bool canJump, sf::Vector2f velocity)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime; //reset switch timer
		if (velocity.y != 0.0f && currentImage.x != 7 && !canJump )
		{
			++currentImage.x;
		}
		
	}
	//If horizontal velocity left switch jump animation
	if (velocity.x < 0)
		faceRight = false;
	else if(velocity.x > 0)
		faceRight = true;
	uvRect.top = currentImage.y * uvRect.height;
	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{

		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}

void Animation::updateImageStart(int currentImagex)
{
	currentImage.x = currentImagex;
}

Animation::~Animation()
{
}
