//  __________________________________________
// | GelAble.h - class definition			  |
// | Jakub Kleban - February 2k17             |
// |__________________________________________|
//

#ifndef _H_GEL
#define _H_GEL

#include <SFML/Graphics.hpp>

///
///Klasa podstawowa wszystkich glut�w
///
class GelAble : public sf::Drawable
{
public:

	///KONSTRUKTORY ~ DESTRUKTORY

	GelAble(void);

	///Konstruktor (z mas�)
	GelAble(int _mass);

	///Konstruktor (z promieniem)
	GelAble(float _radius);


	virtual ~GelAble(void);

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
	void setPosition(sf::Vector2f _position) { circle.setPosition(_position); }

	///
	///Metoda zwraca promie� obiektu
	///
	sf::Vector2f getPosition() { return circle.getPosition(); }

	///
	///Metoda rysuj�ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const { targ.draw(circle); }


	///Publiczne zmienne
	sf::CircleShape		circle;				//cia�o gracza

private:

	float				m_radius;			//promie� jedzonka
	int					m_mass;				//masa jedzonka

};


#endif //_H_GEL