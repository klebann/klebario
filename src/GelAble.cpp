//  __________________________________________
// | GelAble.cpp - class implementation	      |
// | Jakub Kleban - February 2k17             |
// |__________________________________________|
//

#include "GelAble.h"


///default constructor
GelAble::GelAble()
	:
	m_radius(3.f),
	m_mass(1)
{
	float x = float(std::rand() % 3000);
	float y = float(std::rand() % 3000);

	sf::CircleShape _circle(m_radius);
	circle = _circle;
	circle.setOrigin(m_radius, m_radius);
	circle.setPointCount(5);
	circle.setPosition(x, y);
	circle.setFillColor(sf::Color(255, 255, 0, 255));
}

///Konstruktor (z mas¹)
GelAble::GelAble(int _mass)
{
	m_mass = _mass;
	m_radius = sqrt(m_mass * 9.f);

	float x = float(std::rand() % 3000);
	float y = float(std::rand() % 3000);

	sf::CircleShape _circle(m_radius);
	circle = _circle;
	circle.setOrigin(m_radius, m_radius);
	circle.setPointCount(5);
	circle.setPosition(x, y);
	circle.setFillColor(sf::Color(255, 255, 0, 255));
}

///Konstruktor (z promieniem)
GelAble::GelAble(float _radius)
{
	m_mass = (_radius * _radius) / 9;
	m_radius = sqrt(m_mass * 9.f);

	float x = float(std::rand() % 3000);
	float y = float(std::rand() % 3000);

	sf::CircleShape _circle(m_radius);
	circle = _circle;
	circle.setOrigin(m_radius, m_radius);
	circle.setPointCount(5);
	circle.setPosition(x, y);
	circle.setFillColor(sf::Color(255, 255, 0, 255));
}

GelAble::~GelAble()
{
	m_mass = 0;
	m_radius = 0;
}

//Metoda ustawiajaca masê obiektu
void GelAble::setMass(int _mass)
{
	m_mass = _mass;
	m_radius = sqrt(m_mass * 9.f);

	circle.setRadius(m_radius);
	circle.setOrigin(m_radius, m_radius);
}

//Metoda ustawia promieñ obiektu
void GelAble::setRadius(float _radius)
{
	float n_mass = (_radius * _radius) / 9;
	setMass(int(n_mass));
}