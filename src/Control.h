//  __________________________________________
// | Control.h - class definition		      |
// | Jakub Kleban - December 2016             |
// |__________________________________________|
//

#ifndef _H_CONTROL
#define _H_CONTROL

#include <SFML/Graphics.hpp>
#include "CPlayer.h"
#include <math.h>
#include <iostream>

///
///Klasa reprezentuje sterowanie gracza
///
class Control
{
public:

	///
	///Konstruktor
	///
	Control(void);

	///
	///Konstruktor z parametrami
	///
	///@param - _howFar(how far must be cursor to move), _fromWhereMaxSpeed(Distance from begin max speed)
	///
	Control(float _howLazy, float _whereMaxSpeed);

	///
	///Destruktor
	///
	~Control(void);


	///Publiczny interface klasy - metody dostêpowe

	///
	///funkcja aktualizuj¹ca
	///
	void upDate(const sf::RenderWindow *okno, CPlayer *player, sf::View *camera);


	///GodMode!
	void godMode(CPlayer *player);

	//Ustawia pozycje gracza
	void setPlayerPosition(float _width, float _height) { playerPosition = { _width / 2,_height / 2 }; }

private:

	//move the player in the current direction with appropriate speed
	void move(CPlayer *player, sf::View *camera);

	//check if the player must move
	bool check(const sf::RenderWindow *okno);

	//Distance to cursor
	float distanceTo();

	//update the current direction of move
	void updateDirection();

	//settings//
	float						howLazy;
	float						whereMaxSpeed;
	float						currentDistance;
	bool						enableCheating;				//god mode

	//parametrs//
	sf::Vector2f				moveDirection;
	sf::Vector2i				mousePosition;
	sf::Vector2f				playerPosition;
};

#endif //_H_PLAYER