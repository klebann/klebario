//  __________________________________________
// | CGame.cpp	 - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "Game.h"

Game::Game() 
: 
	window		(sf::VideoMode(WIDTH, HEIGHT), "Klebar.io SFML-GAME", sf::Style::Default, sf::ContextSettings(0, 0, 4)),
	view		(sf::FloatRect(1425, 1425, 150, 150)),
	foodnumber	(1000)
{
	srand(unsigned int(time(NULL)));

	window.setFramerateLimit(120);

	//£adowanie t³a//
	if (!texture.loadFromFile("tlo.png"))
	{
		std::cout << "B³¹d podczas wczytywania t³a" << std::endl;
	}
	background.setTexture(texture);

	//OBIEKTY//
	for (int i = 0; i < foodnumber; i++)
	{
		foods.push_back(new CFood());
	}

	//ZEGAR//
	sf::Event event;
	sf::Clock timer;
	sf::Time fps, accumulator;
	float TPF = 0.03f; /*TimePerFrame*/
	float czasdosek = 0.f;
}

void Game::run()
{
	timer.restart();
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	//OBS£UGA ZDARZEÑ//
	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed && sf::Keyboard::Escape) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			window.close();
		}
	}
}

void Game::update()
{
	//ZLICZANIE CZASU//
	fps = timer.restart();
	accumulator += fps;

	//MECHANIKA GRY//								
	if (accumulator.asSeconds() >= TPF)
	{
		addFood();
		player->upDate(TPF, &foods, &view);
		accumulator -= sf::seconds(TPF);
	}
}

void Game::render()
{
	window.clear(sf::Color::Magenta); //czysc ekran przed renderingiem


	window.setView(view); //ustaw kamere
	window.draw(background);
	for (std::list<CFood*>::iterator i = foods.begin(); i != foods.end(); i++)
	{
		(*i)->draw(window, sf::RenderStates::Default);
	}
	player->draw(window, sf::RenderStates::Default);
	window.setView(window.getDefaultView()); //zdjemij kamere

	window.draw(player->getTekst());


	window.display(); //zakoncz aktualna klatke i wyswietl zawartosc na ekranie
}

//Dodaje nowe jedzenia zale¿ne od czasu
void Game::addFood()
{
	timeOnFood += TPF;
	if ( (timeOnFood >= 0.1f) && (foods.size() <= foodlimit) )
	{
			timeOnFood -= 0.1f;
			foods.push_back(new CFood());
	}
}