//  __________________________________________
// | CFood.cpp - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "CFood.h"


//Konstruktor
CFood::CFood(void)
{
	float _radius(3.f);
	int _mass(1);
	m_radius = _radius;
	m_mass = _mass;

	float x = float(std::rand() % 3000);
	float y = float(std::rand() % 3000);

	sf::CircleShape _circle(3.f);
	circle = _circle;
	circle.setOrigin(m_radius, m_radius);
	circle.setPointCount(5);
	circle.setPosition(x, y);
	circle.setFillColor(sf::Color(0, 153, 0, 255));
}

//Konstruktor (z parametrami)
CFood::CFood(sf::Vector2f _position = {100.0f, 100.0f} , float _radius = 7.0f, int _mass = 5)
	:
	m_radius(_radius),
	m_mass(_mass),
	circle(sf::CircleShape(_radius))
{
	circle.setOrigin(m_radius, m_radius);
	circle.setPointCount(50);
	circle.setPosition(_position);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(-1);
	circle.setOutlineColor(sf::Color::Black);
}

//Dekonstruktor
CFood::~CFood(void)
{
	m_mass = 0;
	m_radius = 0;
}

//Metoda ustawiajaca masê obiektu
void CFood::setMass(int _mass)
{
	m_mass = _mass;
}

//Metoda ustawia promieñ obiektu
void CFood::setRadius(float _radius)
{
	m_radius = _radius;
}

//Metoda ustawia promieñ obiektu
void CFood::setPosition(sf::Vector2f _position)
{
	circle.setPosition(_position);
}

//Sprawdza czy zachodzi kolizja
bool CFood::ifKolizja(CPlayer* _player)
{
	//zbieram pozycje
	sf::Vector2f Vfood = this->getPosition();
	sf::Vector2f Vplayer = _player->getPosition();

	//licze
	float dx = Vfood.x - Vplayer.x; //odleg³oœæ w osi x
	float dy = Vfood.y - Vplayer.y; //odleg³oœæ w osi y
	float distance = sqrt(dx * dx + dy * dy); //pitagolas

	//sprawdzam
	if (distance < _player->getRadius())	return true;
		else								return false;
}