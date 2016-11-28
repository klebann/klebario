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


	///Publiczny interface klasy - metody dost�powe


	///
	///Update'a obiekt
	///
	///@param - czas
	///
	void upDate(float time, std::list<CFood*> *foods, sf::View *camera); //Cia�o w pliku *.cpp

	///
	///Metoda ustawia mas� obiektu
	///
	void setMass(int _mass); //Cia�o w pliku *.cpp

	///
	///Metoda zwraca mas� obiektu
	///
	int getMass() { return m_mass; }

	///
	///Metoda zwraca napis
	///
	sf::Text getTekst() { return tekst; }

	///
	///Metoda ustawia promie� obiektu
	///
	///@param - promie�(float)
	///
	void setRadius(float _radius); //Cia�o w pliku *.cpp

	///
	///Metoda zwraca promie� obiektu
	///
	float getRadius() { return m_radius; }

	///
	///Metoda ustawia pozycje obiektu
	///
	///@param - promie�(float)
	///
	void setPosition(sf::Vector2f _position); //Cia�o w pliku *.cpp

	///
	///Metoda zwraca pozycje obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj�ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const { targ.draw(circle); }

private:

	///
	///Metoda porusza obiektem
	///
	void moving(sf::View *camera); //cia�o w cpp

	///
	///Metoda sprawdza czy wyst�pi�a kolizja z jedzonkiem
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
	///Metoda pokazuje mas� na ekranie
	///
	void setPoints(int mass); //cia�o w cpp

	//NAPIS//
	sf::Font			font;			//czcionka
	sf::Text			tekst;			//tekst masy

	//PLAYER//
	sf::CircleShape		circle;				//cia�o gracza
	float				m_radius;			//promie� ko�a
	int					m_mass;				//masa obiektu
	float				m_speed;			//pr�dko�� obiektu
	bool				isAnimated=false;	//czy jest animacja?
	float				animSpeed = 0.5f;	//predkosc animacji kamery
	float				resistance = 0.f;	//opor gracza
};


#endif //_H_PLAYER
