//  __________________________________________
// | CFood.h - class definition			      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#ifndef _H_FOOD
#define _H_FOOD

#include <SFML/Graphics.hpp>
#include "CPlayer.h"
#include <math.h>
#include <list>


class CPlayer;

///
///Klasa reprezentuje gracza
///
class CFood : public sf::Drawable
{
public:

	///
	///Konstruktor
	///
	CFood(void);

	///
	///Konstruktor (z parametrami)
	///
	CFood(sf::Vector2f _position, float _radius, int _mass);

	///
	///Dekonstruktor
	///
	~CFood(void);


	///Publiczny interface klasy - metody dost�powe

	///
	///Metoda ustawia mas� obiektu
	///
	void setMass(int _mass); //Cia�o w pliku *.cpp

	///
	///Metoda zwraca mas� obiektu
	///
	int getMass() { return m_mass; }

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
	///Metoda ustawia promie� obiektu
	///
	///@param - promie�(float)
	///
	void setPosition(sf::Vector2f _position); //Cia�o w pliku *.cpp

	///
	///Metoda zwraca promie� obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj�ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const {	targ.draw(circle); }

	///
	///Sprawdza czy zachodzi kolizja
	///
	bool ifKolizja(CPlayer* _player); //cia�o w cpp

private:

	sf::CircleShape		circle;				//cia�o gracza
	float				m_radius;			//promie� jedzonka
	int					m_mass;				//masa jedzonka
};


#endif //_H_FOOD
