#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Collider.h"
#include "Platform.h"
#include <vector>
using namespace std;
static const float VIEW_HEIGHT = 500.0f;
void ResizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
	view.zoom(0.7f);
}
//*********************TODO************************\\
//Add Enemy Class
//
int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML");
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(500, 500));
	view.zoom(0.5f);
	//view.setViewport(sf::FloatRect();
	//Mountain backdrop
	sf::FloatRect fBounds(0.f, 0.f, 10000.0f, 400.0f);
	sf::Texture backGroundText;
	sf::IntRect iBounds(fBounds);
	backGroundText.loadFromFile("Media/Assets/outside.png");
	sf::Sprite back(backGroundText, iBounds);
	backGroundText.setRepeated(true);

	//Moon sprite
	sf::Texture moonT;	moonT.loadFromFile("Media/dirttiles.png");
	sf::Sprite moon(moonT);
	moon.setTextureRect(sf::IntRect(96, 0, 32.5, 35));
	moon.setPosition(600.0f, -90.0f);
	moon.scale(3.0f, 3.0f);

	//Underground rock background
	sf::Texture rockBackT = moonT; rockBackT.setRepeated(true);
	sf::Sprite rockBack(rockBackT);
	rockBack.setTextureRect(sf::IntRect(96, 72, 32.5, 35));
	rockBack.setPosition(200.0f, 100.0f);

	//Platforms
	sf::Texture groundTexture;
	groundTexture.loadFromFile("Media/dirttiles.png");
	groundTexture.setRepeated(true);
	//Platform Vector
	std::vector<Platform> platforms;	//Scale, Position 
	//platforms.push_back(Platform(&groundTexture, sf::Vector2f(500.0f, 900.0f), sf::Vector2f(00.0f, 300.0f)));
	platforms.push_back(Platform(&groundTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(220.0f, 400.0f)));
	platforms.push_back(Platform(&groundTexture, sf::Vector2f(300.0f, 300.0f), sf::Vector2f(500.0f, 380.0f)));
	
	//Grass ( should create vector for grasses )
	sf::Texture grasst; grasst.loadFromFile("Media/dirttiles.png");
	//std::vector<sf::Sprite> grasses(sf::Sprite(grasst));
	sf::Sprite grass(grasst); grass.setTextureRect(sf::IntRect(165, 70, 32.5, 27));
	grass.setPosition(200.0f, 220.0f);
	grass.scale(3.0f, 3.0f);
	sf::Sprite grass2 = grass;
	grass2.setTextureRect(sf::IntRect(190, 70, 32.5, 27));
	grass2.setPosition(350.0f, 150.0f);

	//Projectiles Vector Declaration
	std::vector<Projectile> projectiles;
	//Projectile texture
	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("Media/ninjaStar.png");
	//Player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Media/template_Player1.png");
	Player player(&playerTexture, sf::Vector2u(8, 9), 0.1f, 70.0f, 75); //was 13, 21


	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
				ResizeView(window, view);
		}
		//Platform collisions
		sf::Vector2f direction;
		for (Platform &platform : platforms)
			if (platform.GetCollider().CheckCollision(player.getCollider(), direction, 1.0f));
				player.onCollision(direction);

		//Projectiles

		player.Update(deltaTime, projectiles, &bulletTexture);//set center only after update
		//Window
		view.setCenter(player.GetPosition()); //set center only after collision detection (or jittery)
		sf::Color color(44, 65, 92);
		window.clear(color);
		window.setView(view);
		window.draw(back);
		window.draw(moon);
		player.Draw(window);
		//draw platforms
		for (Platform &platform : platforms)
			platform.Draw(window);
		//draw and delete projectiles
		std::vector<Projectile>::iterator it;
		for (Projectile &projectile : projectiles) 
			projectile.Draw(window);






		window.draw(grass);
		window.draw(grass2);
		window.display();
	}

	return 0;
}