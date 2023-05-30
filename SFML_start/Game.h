#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>

class Game
{
	//class that act as game engine


	//objects
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;







	sf::Sprite hero;
	sf::Texture hero_texture;
	sf::Texture background_texture;
	sf::Sprite background;

	// Flags for key pressed
	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;

	sf::Vector2f vec_move;

	std::vector<sf::RectangleShape> walls;
	sf::Texture wall_texture;

	void set_movment();
	void initializeViriables();
	void initializeWindow();
	int initializeHero();
	int initBackground();

	auto pressed();
	auto relesed();


	//all for collisions
	auto initializeWalls();

	auto wall_collision();


public:
	//constructors
	Game();
	virtual ~Game();

	const bool running() const;

	void updateEvents();
	void render();
	void update();

};

