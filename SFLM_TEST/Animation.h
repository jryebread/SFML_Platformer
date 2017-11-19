#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	
public:
	sf::IntRect uvRect;
	enum xImage //Amount of images on the x axis (width)
	{ //was walk 9, shoot 13, idle 1
		Walk = 7,
		Shoot = 3,
		Run = 7,
		Idle = 1,
		Jump = 7
	};
	
	void Update(int row, xImage rowImages, float deltaTime, bool faceRight);
	bool UpdateAttack(int row, xImage rowImages, float deltaTime, bool faceRight, bool attackBool);
	void UpdateJump(int row, xImage rowImages, float deltaTime, bool faceRight, bool canJump, sf::Vector2f velocity);
	void updateImageStart(int currentImagex);
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

