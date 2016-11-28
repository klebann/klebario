//  __________________________________________
// | CGame.h	 - class definition		      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#ifndef _H_GAME
#define _H_GAME
#define WIDTH 600
#define HEIGHT 600

#include <SFML/Graphics.hpp>
#include "CPlayer.h"
#include "CFood.h"
#include <string>
#include <iostream>
#include <sstream>

///
///Klasa reprezentuje g³ówn¹ klasê gry
///
class Game
{
public:
	///
	///Konstruktor
	///
	Game();

	///
	///Funkcja uruchamiajaca gre
	///
	void run();

private:

	///
	///Funkcja odpowiada za zdarzenia
	///
	void processEvents();
	
	///
	///funkcja updatuje grê
	///
	void update();

	///
	///Funkcja renderuj¹ca grê
	///
	void render();

	///
	///Dodoaj jedzonko zaleznie od czasu
	///
	void addFood(); //in cpp

	//ZEGAR//
	sf::Event			event;
	sf::Clock			timer;
	sf::Time			fps, accumulator;
	float				TPF = 0.03f;			//czas na sekundê
	float				czasdosek = 0.f;		//czas do sekundy

	//GRA//
	int						foodlimit = 4000;	//limit jedzenia na mapie
	int						foodnumber;			//ilosc jedzenia
	sf::RenderWindow		window;				//okno gry
	sf::View				view;				//kamera
	sf::Texture				texture;			//tekstura background
	sf::Sprite				background;			//duszek z t³em
	std::list<CFood*>		foods;				//lista jedzonek
	float					timeOnFood = 0.f;	//czas tworznia nowego jedzonka
	CPlayer *player = new CPlayer();			//wskaznik na nowego playera
};

#endif //_H_GAME