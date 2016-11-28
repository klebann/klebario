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


	///Publiczny interface klasy - metody dostêpowe

	///
	///Metoda ustawia masê obiektu
	///
	void setMass(int _mass); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca masê obiektu
	///
	int getMass() { return m_mass; }

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
	///Metoda ustawia promieñ obiektu
	///
	///@param - promieñ(float)
	///
	void setPosition(sf::Vector2f _position); //Cia³o w pliku *.cpp

	///
	///Metoda zwraca promieñ obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj¹ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const {	targ.draw(circle); }

	///
	///Sprawdza czy zachodzi kolizja
	///
	bool ifKolizja(CPlayer* _player); //cia³o w cpp

private:

	sf::CircleShape		circle;				//cia³o gracza
	float				m_radius;			//promieñ jedzonka
	int					m_mass;				//masa jedzonka
};


#endif //_H_FOOD
