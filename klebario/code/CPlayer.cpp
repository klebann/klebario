//  __________________________________________
// | CPlayer.h - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "CPlayer.h"


//Konstruktor
CPlayer::CPlayer(void)
	://Lista inicjalizacynja
		circle			(sf::CircleShape(9.48f)),
		m_mass			(10),
		m_radius		(9.48f),
		m_speed			(5.0f),
		tekst			(sf::Text()),
		font			(sf::Font())
{
	//kó³ko//
	circle.setOrigin			(9.48f, 9.48f);
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
		mymove(0.f, -m_speed, camera);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mymove(m_speed, 0.0f, camera);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mymove(0.0f, m_speed, camera);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mymove(-m_speed, 0.0f, camera);
	}
}

//Update'a obiekt
void CPlayer::upDate(float time, std::list<CFood*> *foods, sf::View *camera)
{
	moving(camera);
	stayOnMap(camera);
	kolizja(foods, camera);
	zoom(camera);
	setPoints( getMass() );
}

//Metoda ustawiajaca masê obiektu
void CPlayer::setMass(int _mass)
{
	m_mass = _mass;
	float n_radius = sqrt(m_mass * 9.f);
	m_radius = n_radius;
	circle.setRadius(n_radius);
	circle.setOrigin(n_radius, n_radius);
}

//Metoda ustawia promieñ obiektu
void CPlayer::setPosition(sf::Vector2f _position)
{
	circle.setPosition(_position);
}

//Metoda ustawia promieñ obiektu
void CPlayer::setRadius(float _radius)
{
	int n_mass = (m_radius * m_radius) / 9 ;
	setMass(n_mass);
}

//Metoda sprawdza czy wyst¹pi³a kolizja
void CPlayer::kolizja(std::list<CFood*> *foods, sf::View *cam)
{
	std::list<CFood*>::iterator i = foods->begin();
	while (i != foods->end())
	{
		if ((*i)->ifKolizja(this))
		{
			int new_mass = this->getMass() + (*i)->getMass(); //nowa masa to suma

			setMass(new_mass);
			//cam->zoom(new_zoom);


			foods->erase(i++); //i = list.erase(i);
		}
		else
			++i;
	}
}

//Metoda ustawia zoom kamery
void CPlayer::zoom(sf::View *cam)
{
	if (m_mass > 0 && m_mass <= 20)
	{
		cam->setSize({ 150,150 });	
	}
	else if (m_mass > 20 && m_mass <= 100)
	{
		isAnimated = true;
		zoomAnimation(250.f, cam);
	}
	else if (m_mass > 100 && m_mass <= 300)
	{
		isAnimated = true;
		zoomAnimation(350.f, cam);
	}
	else if (m_mass > 300 && m_mass <= 600)
	{
		isAnimated = true;
		zoomAnimation(450.f, cam);
	}
	else if (m_mass > 600 && m_mass <= 1000)
	{
		isAnimated = true;
		zoomAnimation(600.f, cam);
	}
	else if (m_mass > 1000 && m_mass <= 3000)
	{
		isAnimated = true;
		zoomAnimation(700.f, cam);
	}
	else if (m_mass > 3000 && m_mass <= 5000)
	{
		isAnimated = true;
		zoomAnimation(850.f, cam);
	}
	else if (m_mass > 5000 && m_mass <= 10000)
	{
		isAnimated = true;
		zoomAnimation(1000.f, cam);
	}
	else if (m_mass > 10000)
	{
		isAnimated = true;
		zoomAnimation(1250.f, cam);
	}
}

//zoom animation
void CPlayer::zoomAnimation(float toNumber, sf::View *cam)
{
	if (isAnimated == false)
		return;

	if (isAnimated)
	{
		cam->setSize(cam->getSize().x + animSpeed, cam->getSize().y + animSpeed);

		if (cam->getSize().x >= toNumber)
		{
			cam->setSize({ toNumber, toNumber });
			isAnimated = false;
		}

	}
}

//metoda ustawia parametry tekstu
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

//Metoda ustawia obiekt na mapie jezeli z niej wyjdzie
void CPlayer::stayOnMap( sf::View *cam )
{
	if ( this->getPosition().x > 3000.0f)
		this->mySetPos( 3000.0f, this->getPosition().y , cam );
	else if ( this->getPosition().x < 0.f)
		this->mySetPos( 0.0f, this->getPosition().y , cam );

	if ( this->getPosition().y > 3000.0f)
		this->mySetPos( this->getPosition().x, 3000.f , cam );
	else if ( this->getPosition().y < 0.f)
		this->mySetPos( this->getPosition().x, 0.f , cam );
}