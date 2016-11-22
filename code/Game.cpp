//  __________________________________________
// | CGame.cpp	 - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "Game.h"

Game::Game() 
: 
	window		(sf::VideoMode(WIDTH, HEIGHT), "Klebar.io SFML-GAME", sf::Style::Default, sf::ContextSettings(0,0,8)),
	view		(sf::FloatRect(1200, 1200, 600, 600))
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
	for (int i = 0; i < 1000; i++)
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
		player->upDate(TPF, &foods, player, &view);
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