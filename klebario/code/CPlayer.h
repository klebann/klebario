//  __________________________________________
// | CPlayer.h - class definition		      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#ifndef _H_PLAYER
#define _H_PLAYER

#include <SFML/Graphics.hpp>
#include "CFood.h"
#include <list>
#include <sstream>
#include <iostream>

class CFood;

///
///Klasa reprezentuje gracza
///
class CPlayer : public sf::Drawable
{
public:

	///
	///Konstruktor
	///
	CPlayer(void);

	///
	///Konstruktor (z parametrami)
	///
	CPlayer(float _radius, int _mass, float _speed);

	///
	///Dekonstruktor
	///
	~CPlayer(void);


	///Publiczny interface klasy - metody dostêpowe


	///
	///Update'a obiekt
	///
	///@param - czas
	///
	void upDate(float time, std::list<CFood*> *foods, sf::View *camera); //Cia³o w pliku *.cpp

	///
	///Metoda ustawia masê obiektu
	///
	void setMass(int _mass); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca masê obiektu
	///
	int getMass() { return m_mass; }

	///
	///Metoda zwraca napis
	///
	sf::Text getTekst() { return tekst; }

	///
	///Metoda ustawia promieñ obiektu
	///
	///@param - promieñ(float)
	///
	void setRadius(float _radius); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca promieñ obiektu
	///
	float getRadius() { return m_radius; }

	///
	///Metoda ustawia pozycje obiektu
	///
	///@param - promieñ(float)
	///
	void setPosition(sf::Vector2f _position); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca pozycje obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj¹ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const { targ.draw(circle); }

private:

	///
	///Metoda porusza obiektem
	///
	void moving(sf::View *camera); //cia³o w cpp

	///
	///Metoda sprawdza czy wyst¹pi³a kolizja z jedzonkiem
	///
	void kolizja(std::list<CFood*> *foods, sf::View *cam);

	///
	///Metoda ustawia obiekt na mapie jezeli z niej wyjdzie
	///
	void stayOnMap(sf::View *cam); //body in cpp

	///
	///Metoda ustawia zoom kamery
	///
	void zoom(sf::View *cam); //body in cpp

	///
	///zoom animation
	///
	void zoomAnimation(float toNumber, sf::View *cam); //body in cpp

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
	///Metoda ustawia wstepne wartosci tekstu
	///
	void setText(int mass);

	///
	///Metoda pokazuje masê na ekranie
	///
	void setPoints(int mass); //cia³o w cpp

	//NAPIS//
	sf::Font			font;			//czcionka
	sf::Text			tekst;			//tekst masy

	//PLAYER//
	sf::CircleShape		circle;				//cia³o gracza
	float				m_radius;			//promieñ ko³a
	int					m_mass;				//masa obiektu
	float				m_speed;			//prêdkoœæ obiektu
	bool				isAnimated=false;	//czy jest animacja?
	float				animSpeed = 0.5f;	//predkosc animacji kamery
	float				resistance = 0.f;	//opor gracza
};


#endif //_H_PLAYER
