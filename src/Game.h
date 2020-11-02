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
#include "Control.h"
#include "CPlayer.h"
#include "CFood.h"
#include "Enemy.h"
#include "MiniMap.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string.h>

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

	///
	///Dodoaj jedzonko zaleznie od czasu
	///
	void addEnemy(); //in cpp

	///
	///Skaluje mape do zmienionych rozmiarów
	///
	void resize(); //in cpp

	//ZEGAR//
	sf::Event				event;
	sf::Clock				timer;
	sf::Time				fps, accumulator;
	const float				TPF = 0.03f;						//czas na sekundê
	float					czasdosek = 0.f;					//czas do sekundy

	//WINDOW//
	float					width;								//szerokosc okna
	float					height;								//wysokosc okna	
	sf::Vector2f			m_size;								//rozmiar view
	sf::Vector2f			scale;								//skala

	//GRA//
	sf::RenderWindow		window;								//okno gry
	sf::Texture				textureBg;							//tekstura background
	sf::Texture				textureOver;						//tekstura przegrywu
	sf::Texture				playerTexture;						//tekstura gracza
	std::list<CFood*>		foods;								//lista jedzonek
	std::list<Enemy*>		enemies;							//lista przeciwników
	float					timeOnFood = 0.f;					//czas tworznia nowego jedzonka
	float					timeOnEnemy = 0.f;					//czas tworznia nowego przeciwnika
	bool					isDead = false;						//sprawdza czy przeciwnik umar³

	//Ustawienia//
	int	unsigned			foodlimit = 4000;					//limit jedzenia na mapie
	int	unsigned			enemylimit = 30;					//ilosc przeciwniów
	int						SkinNumber;							//ile dostêpnych skinów
	int						foodnumber;							//ilosc jedzenia
	int						enemynumber;						//ilosc przeciwniów
	bool					isSkin;								//w³¹czone skiny

	//OBIEKTY//
	Control					sterowanie;
	CPlayer					*player = new CPlayer();			//wskaznik na nowego playera
	MiniMap					*map = new MiniMap(WIDTH,HEIGHT);	//Tworzy mape
	sf::Sprite				background;							//duszek z t³em
	sf::View				view;								//kamera
	sf::Sprite				gameOver;							//duszek z tekstura gameOver

};

#endif //_H_GAME