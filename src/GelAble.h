//  __________________________________________
// | GelAble.h - class definition			  |
// | Jakub Kleban - February 2k17             |
// |__________________________________________|
//

#ifndef _H_GEL
#define _H_GEL

#include <SFML/Graphics.hpp>

///
///Klasa podstawowa wszystkich glutów
///
class GelAble : public sf::Drawable
{
public:

	///KONSTRUKTORY ~ DESTRUKTORY

	GelAble(void);

	///Konstruktor (z mas¹)
	GelAble(int _mass);

	///Konstruktor (z promieniem)
	GelAble(float _radius);


	virtual ~GelAble(void);

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
	void setPosition(sf::Vector2f _position) { circle.setPosition(_position); }

	///
	///Metoda zwraca promieñ obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj¹ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const { targ.draw(circle); }


	///Publiczne zmienne
	sf::CircleShape		circle;				//cia³o gracza

private:

	float				m_radius;			//promieñ jedzonka
	int					m_mass;				//masa jedzonka

};


#endif //_H_GEL