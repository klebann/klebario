//  __________________________________________
// | CPlayer.h - class definition		      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#ifndef _H_PLAYER
#define _H_PLAYER

#include <SFML/Graphics.hpp>
#include "CFood.h"
#include "Enemy.h"
#include "GelAble.h"
#include <list>
#include <sstream>
#include <iostream>

class Control;
class CFood;
class Enemy;

///
///Klasa reprezentuje gracza
///
class CPlayer : public GelAble
{
public:

	///
	///Konstruktor
	///
	CPlayer(void);

	///
	///Konstruktor (z mas¹)
	///
	CPlayer(int _mass, float _speed);

	///
	///Dekonstruktor
	///
	virtual ~CPlayer(void);


	///Publiczny interface klasy - metody dostêpowe


	///
	///Update'a obiekt
	///
	///@param - czas
	///
	bool upDate(float time, std::list<CFood*> *foods, std::list<Enemy*> *enemies, sf::View *camera, sf::Vector2f* _view, sf::Vector2f _scale); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca napis
	///
	sf::Text* getTekst() { return &tekst; }

	///
	///Metoda zmienia predkosc
	///
	void setSpeed(float _value) { m_speed = _value; }

	///
	///Metoda zwraca aktualn¹ prêdkoœæ
	///
	float getCurrentSpeed() { return cur_speed; }

	///
	///porusza graczem i scena
	///
	void mymove(float x, float y, sf::View *cam)
	{
		circle.move(x, y);
		cam->move(x, y);
	}

	///
	///ustawia graczem i scena
	///
	void mySetPos(float x, float y, sf::View *cam)
	{
		circle.setPosition(x, y);
		cam->setCenter(x, y);
	}

	///
	///Metoda rysuj¹ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const { targ.draw(circle); }

private:

	///
	///Metoda sprawdza czy wyst¹pi³a kolizja z jedzonkiem
	///
	bool kolizja(std::list<CFood*> *foods, std::list<Enemy*> *enemies, sf::View *cam);

	///
	///Metoda ustawia obiekt na mapie jezeli z niej wyjdzie
	///
	void stayOnMap(sf::View *cam); //body in cpp

	///
	///Metoda ustawia zoom kamery
	///
	void zoom(sf::View *cam, sf::Vector2f _scale, sf::Vector2f* _size); //body in cpp

	///
	///zoom animation
	///
	void zoomAnimation(sf::Vector2f _size, sf::Vector2f _scale, sf::View *cam); //body in cpp

	///
	///Metoda ustawia wstepne wartosci tekstu
	///
	void setText(int mass);

	///
	///Metoda pokazuje masê na ekranie
	///
	void setPoints(int mass); //cia³o w cpp

	///
	///Metoda ustawia aktualny opór
	///
	void setResistance(); //cia³o w cpp

	///
	///Metoda kontroluje zeby player nie byl za duzy
	///
	void loseWeight(); //in cpp

	//NAPIS//
	sf::Font			font;					//czcionka
	sf::Text			tekst;					//tekst masy

	//PLAYER//
	float				lossMassF = 0.00003f;	//si³a utraty masy
	float				lostMassPerFrame;		//utracona masa na klatkê
	float				Mcollector=0.f;			//kolektor utraconej masy

	float				m_speed;				//prêdkoœæ obiektu
	float				cur_speed;				//rzeczywista prêdkoœæ obiektu
	float				resistance = 0.f;		//opor gracza
	float				resistanceF = 0.002f;	//si³a oporu gracza

	//CAMERA//
	bool				isAnimated=false;		//czy jest animacja?
	float				animSpeed = 0.5f;		//predkosc animacji kamery
};


#endif //_H_PLAYER
