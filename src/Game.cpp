//  __________________________________________
// | CGame.cpp	 - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "Game.h"

Game::Game() 
: 
	window		(sf::VideoMode(WIDTH, HEIGHT), "Klebar.io v0.33 SFML-GAME", sf::Style::Default, sf::ContextSettings(0, 0, 4)),
	view		(sf::FloatRect(1425.f, 1425.f, 150.f, 150.f)), //150
	m_size		(150,150),
	scale		(1,1),
	foodnumber	(1000),
	enemynumber (20),
	sterowanie	(5.f,100.f),
	SkinNumber	(30),
	isSkin		(true),
	width		(WIDTH),
	height		(HEIGHT)
{
	srand(unsigned int(time(NULL)));

	//Ustawienie skina//
	if (isSkin)
	{
		player->circle.setFillColor(sf::Color::White);
		player->circle.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255)); //losuj kolor

		int nr = rand() % SkinNumber + 1;
		std::stringstream ss;
		ss << nr;
		std::string nrString = ss.str();

		std::string skinName = "Skins/" + nrString + ".png";
		if (!playerTexture.loadFromFile(skinName))
		{
			std::cout << "Blad podczas wczytania skina" << std::endl;
		}	
		playerTexture.setSmooth(true);
		player->circle.setTexture(&playerTexture); std::cout << "Loaded skin: " << skinName;
	}
	
	//USTAWIENIE OKNA GRY//
	window.setFramerateLimit(120);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	//£adowanie t³a//
	if (!textureBg.loadFromFile("tlo.png"))
	{
		std::cout << "Blad podczas wczytywania tla gry" << std::endl;
	}	background.setTexture(textureBg);

	if (!textureOver.loadFromFile("gameover.png"))
	{
		std::cout << "Blad podczas wczytywania tla \" Game OVER \" " << std::endl;
	}	gameOver.setTexture(textureOver);

	//OBIEKTY//
	for (int i = 0; i < foodnumber; i++)
	{
		foods.push_back(new CFood());
	}

	for (int i = 0; i < enemynumber; i++)
	{
		enemies.push_back(new Enemy());
	}

	//ZEGAR//
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
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Home))
		{
			sterowanie.godMode(player);
		}
		if (event.type == sf::Event::Resized)
		{
			resize();
		}
	}
}

void Game::update()
{
	//ZLICZANIE CZASU//
	fps = timer.restart();
	accumulator += fps;

	//MECHANIKA GRY//								
	if (accumulator.asSeconds() >= TPF && !isDead)
	{
		addFood();
		addEnemy(); 
		sterowanie.upDate(&window, player, &view);
		for (std::list<Enemy*>::iterator j = enemies.begin(); j != enemies.end(); j++)
		{
			int licznik = (*j)->upDate(TPF, player, &foods, &enemies); //Ile enemy dokonalo kanibalizmu, musze wyrownac ilosc powtorzen w petli
			while (licznik>0)
			{
					j--;
					licznik--;
			}

		}
		if (player->upDate(TPF, &foods, &enemies, &view, &m_size, scale))
			isDead = true;

		map->UpDate(player);

		//accumulator -= sf::seconds(TPF);
		accumulator = sf::Time::Zero;
	}
}

void Game::render()
{
	window.clear(sf::Color::White); //czysc ekran przed renderingiem

	//GRA//
	window.setView(view); //ustaw kamere
	window.draw(background);
	for (std::list<CFood*>::iterator i = foods.begin(); i != foods.end(); i++)
	{
		(*i)->draw(window, sf::RenderStates::Default);
	}
	for (std::list<Enemy*>::iterator j = enemies.begin(); j != enemies.end(); j++)
	{
		(*j)->draw(window, sf::RenderStates::Default);
	}
	player->draw(window, sf::RenderStates::Default);
	
	//nakladka na gre//
	window.setView(window.getDefaultView()); //zdjemij kamere
	window.draw((*player->getTekst()));

	map->print(window, sf::RenderStates::Default, &foods, &enemies, player);

	if (isDead)
	{
		window.setView(window.getDefaultView());
		window.draw(gameOver);
	}

	window.display(); //zakoncz aktualna klatke i wyswietl zawartosc na ekranie
}

//Dodaje nowe jedzenia zale¿ne od czasu
void Game::addFood()
{
	timeOnFood += TPF;
	if ( (timeOnFood >= 0.03f) && (foods.size() <= foodlimit) )
	{
			timeOnFood -= 0.03f;
			foods.push_back(new CFood());
	}
}

void Game::addEnemy()
{
	timeOnEnemy += TPF;
	if ((timeOnEnemy >= 10.f) && (enemies.size() <= enemylimit))
	{
		timeOnEnemy -= 10.f;
		enemies.push_back(new Enemy());
	}
}

//Skaluje mape do zmienionych rozmiarów
void Game::resize()
{
	//ustaw skale ze standardowych wymiarow
	scale.x = float (window.getSize().x) / width;
	scale.y = float (window.getSize().y) / height;

	float mniejszy; float mniejsza_skala;
	if (event.size.width < event.size.height)
	{
		mniejszy = float(event.size.width);
		mniejsza_skala = mniejszy / height;
	}
	else
	{
		mniejszy = float(event.size.height);
		mniejsza_skala = mniejszy / height;
	}

	//Ustaw nowe parametry
	width = float (event.size.width);
	height = float (event.size.height);

	//ustaw rozmiar view
	view.setSize( (view.getSize().x * scale.x) , (view.getSize().y * scale.y) );
	m_size = view.getSize();

	//ustaw rozmiar tekstu
	player->getTekst()->scale(1 / scale.x, 1 / scale.y);
	/*float sizze = Size;
	float average = (scale.x + scale.y) / 2;
	sizze *= average;
	Size = sizze;
	player->getTekst()->setCharacterSize(int(sizze));*/

	//Ustaw rozmiar MiniMapy
	map->reSize(scale, width, height, mniejszy, mniejsza_skala);

	//Ustaw sterowanie myszki
	sterowanie.setPlayerPosition(width, height);
}