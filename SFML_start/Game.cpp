#include "Game.h"

//private



void Game::initializeViriables()
{
	this->window = nullptr;
}
void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "lab_9_psio");
	this->window->setFramerateLimit(90);
}

auto Game::relesed()
{
	switch (this->ev.key.code)
	{
	case sf::Keyboard::Up:      upFlag = false;	break;
	case sf::Keyboard::Down:    downFlag = false; break;
	case sf::Keyboard::Left:    leftFlag = false; break;
	case sf::Keyboard::Right:   rightFlag = false; break;
	default: break;
	}
}
void Game::set_movment()
{
	this->vec_move.x = 0;
	this->vec_move.y = 0;
	if (hero.getGlobalBounds().left < 0)	leftFlag = false;
	if (hero.getGlobalBounds().top < 0)		upFlag = false;
	if (hero.getGlobalBounds().left + hero.getGlobalBounds().width > this->videoMode.width)  rightFlag = false;
	if (hero.getGlobalBounds().top + hero.getGlobalBounds().height > this->videoMode.height) downFlag = false;
	for (const auto& s : walls) {
		if (hero.getGlobalBounds().intersects(s.getGlobalBounds()) && (downFlag))
		{
			downFlag = false;
			this->vec_move.y = -2;

		}
		if (hero.getGlobalBounds().intersects(s.getGlobalBounds()) && (upFlag))
		{
			upFlag = false;
			this->vec_move.y = 2;


		}
		if (hero.getGlobalBounds().intersects(s.getGlobalBounds()) && (leftFlag))
		{
			leftFlag = false;
			this->vec_move.x = 2;


		}
		if (hero.getGlobalBounds().intersects(s.getGlobalBounds()) && (rightFlag))
		{
			rightFlag = false;
			this->vec_move.x = -2;


		}
	}
	if (downFlag && !upFlag) {
		this->vec_move.y = 1;
	}
	if (upFlag && !downFlag) {
		this->vec_move.y = -1;
	}
	if (leftFlag && !rightFlag) {
		this->vec_move.x = -1;
	}
	if (rightFlag && !leftFlag) {
		this->vec_move.x = 1;

	}
	this->hero.move(vec_move);
}



int Game::initializeHero()
{
	//textur pack for hero

	if (!this->hero_texture.loadFromFile("Character.png")) {
		std::cerr << "Could not load texture" << std::endl;
		return 1;
	}

	this->hero.setTexture(hero_texture);
	this->hero.setTextureRect(sf::IntRect(16, 11, 33, 40));
	this->hero.scale(sf::Vector2f(2, 2));
	this->hero.setPosition(sf::Vector2f(0, 0));

}
int Game::initBackground()
{

	if (!this->background_texture.loadFromFile("dungeon.png")) {
		std::cerr << "Could not load texture" << std::endl;
		return 1;
	}


	this->background.setTexture(background_texture);
	this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
	this->background.setScale(1, 1);
	this->background.setPosition(0, 0);


}


auto Game::pressed()
{
	//hero movment method

	switch (this->ev.key.code)
	{
	case sf::Keyboard::Up:      upFlag = true;	break;
	case sf::Keyboard::Down:    downFlag = true; break;
	case sf::Keyboard::Left:    leftFlag = true; break;
	case sf::Keyboard::Right:   rightFlag = true; break;
	default: break;
	}




}
//const

auto Game::initializeWalls()
{
	if (!this->wall_texture.loadFromFile("wall.png")) {
		std::cerr << "Could not load texture" << std::endl;
		return 1;
	}
	wall_texture.setRepeated(true);
	sf::RectangleShape wall1;
	wall1.setTextureRect(sf::IntRect(0, 0, 50, 300));
	wall1.setSize(sf::Vector2f(50, 300));
	wall1.setTexture(&wall_texture);
	wall1.setPosition(201, 201);

	sf::RectangleShape wall2;
	wall2.setTextureRect(sf::IntRect(0, 0, 300, 50));
	wall2.setSize(sf::Vector2f(300, 50));
	wall2.setTexture(&wall_texture);
	wall2.setPosition(501, 201);

	sf::RectangleShape wall3;
	wall3.setTextureRect(sf::IntRect(0, 0, 50, 400));
	wall3.setSize(sf::Vector2f(50, 400));
	wall3.setTexture(&wall_texture);
	wall3.setPosition(501, 301);


	this->walls.emplace_back(wall1);
	this->walls.emplace_back(wall2);
	this->walls.emplace_back(wall3);

}

Game::Game()
{
	this->vec_move.x = 0; this->vec_move.y = 0;
	this->initializeViriables();
	this->initializeWindow();
	this->initBackground();
	this->initializeHero();
	this->initializeWalls();
}



Game::~Game()
{
	delete this->window;
	
}


auto Game::wall_collision()
{



}


const bool Game::running() const
{
	return this->window->isOpen();
}
//public



void Game::updateEvents()
{
	while (this->window->pollEvent(this->ev))
	{

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			pressed();
			break;
		case sf::Event::KeyReleased:
			relesed();
			break;
		}
	}
}


void Game::render()
{
	//visualasions renders the game obj
	this->window->clear();
	//-----------------------------

	this->window->draw(this->background);
	this->window->draw(this->hero);
	for (const auto& s : walls) {
		window->draw(s);
	}



	this->window->display();
}

void Game::update()
{
	//there is game

	this->updateEvents();
	this->set_movment();

}
