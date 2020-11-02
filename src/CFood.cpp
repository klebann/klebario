//  __________________________________________
// | CFood.cpp - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "CFood.h"


//Konstruktor
CFood::CFood(void)
	:
	GelAble()
{
	circle.setFillColor(sf::Color(0, 153, 0, 255));
}

//Konstruktor (z mas¹)
CFood::CFood (int _mass)
	:
	GelAble(_mass)
{
	circle.setFillColor(sf::Color(0, 153, 0, 255));
}

//Konstruktor (z promieniem)
CFood::CFood(float _radius)
	:
	GelAble(_radius)
{
	circle.setFillColor(sf::Color(0, 153, 0, 255));
}

//Dekonstruktor
CFood::~CFood(void)
{
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

//Sprawdza czy zachodzi kolizja
bool CFood::ifKolizja(Enemy* _enemy)
{
	//zbieram pozycje
	sf::Vector2f Vfood = this->getPosition();
	sf::Vector2f Venemy = _enemy->getPosition();

	//licze
	float dx = Vfood.x - Venemy.x; //odleg³oœæ w osi x
	float dy = Vfood.y - Venemy.y; //odleg³oœæ w osi y
	float distance = sqrt(dx * dx + dy * dy); //pitagolas

											  //sprawdzam
	if (distance < _enemy->getRadius())	return true;
	else								return false;
}