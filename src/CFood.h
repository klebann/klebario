//  __________________________________________
// | CFood.h - class definition			      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#ifndef _H_FOOD
#define _H_FOOD

#include <SFML/Graphics.hpp>
#include "CPlayer.h"
#include "Enemy.h"
#include "GelAble.h"
#include <math.h>
#include <list>


class CPlayer;
class Enemy;

///
///Klasa reprezentuje gracza
///
class CFood : public GelAble
{
public:

	///
	///Konstruktor
	///
	CFood(void);

	///
	///Konstruktor (z mas¹)
	///
	CFood(int _mass);

	///Konstruktor (z promieniem)
	CFood(float _radius);

	///
	///Dekonstruktor
	///
	virtual ~CFood(void);

	///Publiczny interface klasy - metody dostêpowe

	///
	///Sprawdza czy zachodzi kolizja
	///
	bool ifKolizja(CPlayer* _player); //cia³o w cpp

	///
	///Sprawdza czy zachodzi kolizja
	///
	bool ifKolizja(Enemy* _enemy); //cia³o w cpp
};


#endif //_H_FOOD
