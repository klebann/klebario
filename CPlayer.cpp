//  __________________________________________
// | CPlayer.h - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "CPlayer.h"

//Konstruktor
CPlayer::CPlayer(void)
	://Lista inicjalizacynja
		circle			(sf::CircleShape(10.0f)),
		m_mass			(10),
		m_radius		(10.0f),
		m_speed			(7.0f),
		tekst			(sf::Text()),
		font			(sf::Font())
{
	//kó³ko//
	circle.setOrigin			(10.0f, 10.0f);
	circle.setPointCount		(100); 
	circle.setPosition			(1500, 1500);
	circle.setFillColor			(sf::Color(0, 49, 255, 255));
	circle.setOutlineThickness	(-3);
	circle.setOutlineColor		(sf::Color(0, 0, 153, 255));

	//Napis//
	setText(m_mass);
}

//Konstruktor (z parametrami)
CPlayer::CPlayer(float _radius, int _mass, float _speed)
	:
	m_radius		(_radius),
	m_mass			(_mass),
	m_speed			(_speed),
	circle			(sf::CircleShape(_radius)),
	tekst			(sf::Text()),
	font			(sf::Font())
{
	//kó³ko//
	circle.setOrigin(m_radius, m_radius);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::Blue);

	//Napis//
	setText(m_mass);
}

//Dekonstruktor
CPlayer::~CPlayer(void)
{
	m_mass = 0;
	m_radius = 0;
	m_speed = 0;
}

//Metoda zbieraj¹ca wejœcie programu
void CPlayer::moving(sf::View *camera)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		circle.move(0.0f, -m_speed);
		camera->move(0.0f, -m_speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		circle.move(m_speed,0.0f);
		camera->move(m_speed, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		circle.move(0.0f,m_speed);
		camera->move(0.0f, m_speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		circle.move(-m_speed, 0.0f);
		camera->move(-m_speed, 0.0f);
	}
}

//Update'a obiekt
void CPlayer::upDate(float time, std::list<CFood*> *foods, CPlayer *player, sf::View *camera)
{
	moving(camera);
	kolizja(foods, player);
	setPoints( getMass() );
}

//Metoda ustawiajaca masê obiektu
void CPlayer::setMass(int _mass)
{
	m_mass = _mass;
}

//Metoda ustawia promieñ obiektu
void CPlayer::setPosition(sf::Vector2f _position)
{
	circle.setPosition(_position);
}

//Metoda ustawia promieñ obiektu
void CPlayer::setRadius(float _radius)
{
	m_radius = _radius;
	circle.setRadius(m_radius);
	circle.setOrigin(m_radius, m_radius);
}

//Metoda sprawdza czy wyst¹pi³a kolizja
void CPlayer::kolizja(std::list<CFood*> *foods, CPlayer *player)
{
	std::list<CFood*>::iterator i = foods->begin();
	while (i != foods->end())
	{
		if ((*i)->kolizja(player))
		{
			foods->erase(i++); //i = list.erase(i);
		}
		else
			++i;
	}
}

void CPlayer::setText(int mass)
{
	// ustawia czcionkê
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error";
	}

	// Tworze tekst
	std::ostringstream ss;
	ss << "Mass: " << 10;

	tekst.setFont(font);
	tekst.setString(ss.str());

	// parametry
	tekst.setCharacterSize(20);
	tekst.setColor(sf::Color::Black);
	tekst.setOrigin(0.0f, 20.0f);
	tekst.setPosition(10.0f, 590.0f);
}

void CPlayer::setPoints(int mass)
{
	// Tworze tekst
	std::ostringstream ss;
	ss << "Mass: " << mass;
	tekst.setString(ss.str());
}