//  __________________________________________
// | Enemy.h - class definition			      |
// | Jakub Kleban - December 2016             |
// |__________________________________________|
//

#ifndef _H_ENEMY
#define _H_ENEMY

#include "CPlayer.h"
#include "CFood.h"
#include "GelAble.h"
#include <list>
#include <vector>

class CPlayer;
class CFood;

class Enemy : public GelAble
{
	enum Direction { attack = 1, run };

public:

	Enemy(void);
	virtual ~Enemy(void);

	///Publiczny interface klasy - metody dost瘼owe

	///
	///Sprawdza czy zachodzi kolizja
	///
	int Kolizja(CPlayer* _player); //cia這 w cpp

	///
	///Update'a obiekt
	///
	///@param - czas
	///
	int upDate(float time, CPlayer* _player, std::list<CFood*> *foods, std::list<Enemy*> *enemies); //Cia這 w pliku *.cpp

private:
	///
	///Sprawdza czy zachodzi kolizja
	///
	bool Kolizja(Enemy* _enemy); //cia這 w cpp

	///Quo vadis?!
	void whereGo(CPlayer* _player, std::list<CFood*> *foods, std::list<Enemy*> *enemies); //body in cpp files

	///Sprawdza czy zachodzi kolizja z jedzeniem
	void FoodKolizja(std::list<CFood*> *foods); //cia這 w cpp

	///Sprawdza czy zachodzi kolizja z kolegami
	int Kanibal(std::list<Enemy*> *enemies); //cia這 w cpp

	///Zbiera jedzonka w poblizu
	void Collect(std::list<CFood*> *foods); //body in *.cpp file

	///Metoda sprawdza czy jest w polu widzenia
	bool isNear(CPlayer* _player); //cialo w pliku *.cpp

	///Metoda liczy odleg這��
	float Distance(CPlayer* _player); //cialo w pliku *.cpp

	///Metoda liczy odleg這��
	float Distance(Enemy* _enemy); //cialo w pliku *.cpp

	///Metoda liczy odleg這��
	float Distance(CFood* _food); //cialo w pliku *.cpp

	///Metoda zwraca najwiekszego enemy z wektora enemies
	Enemy* BestFrom(std::vector < Enemy* > _vector); //body in cpp file

	///Metoda ucieka lub goni playera
	void Move(CPlayer* _player, Direction action); //cialo w pliku cpp

	///Metoda ucieka lub goni enemy
	void Move(Enemy* _enemy, Direction action); //cialo w pliku cpp

	///Metoda 豉pie jedzonko
	void goFood(CFood* _food); //cialo w pliku cpp

	///update the current direction of move
	void updateDirection(CPlayer* _player);

	///update the current direction of move
	void updateDirection(Enemy* _enemy);

	///update the current direction of move
	void updateDirection(CFood* _food);

	///
	///Metoda ustawia obiekt na mapie jezeli z niej wyjdzie
	///
	void stayOnMap(); //body in cpp

	///
	///Metoda ustawia aktualny op鏎
	///
	void setResistance(); //cia這 w cpp

	///
	///Metoda kontroluje zeby player nie byl za duzy
	///
	void loseWeight(); //in cpp

	//ENEMY//
	float						m_speed;		//predkosc przeciwnika
	sf::Vector2f				moveDirection;	//kierunek ataku i uciekania player
	sf::Vector2f				moveDirection2;	//kierunek ataku i uciekania food
	sf::Vector2f				moveDirection3;	//kierunek ataku i uciekania enemy

	float						nearest;		//najblizsza osoba od aktualnego enemy
	float						range;			//zakres widzenia enemy

	//Z PLAYER//
	float						lossMassF = 0.00003f;	//si豉 utraty masy
	float						lostMassPerFrame;		//utracona masa na klatk�
	float						Mcollector = 0.f;			//kolektor utraconej masy

	float						cur_speed;				//rzeczywista pr璠ko�� obiektu
	float						resistance = 0.f;		//opor gracza
	float						resistanceF = 0.002f;	//si豉 oporu gracza
};


#endif //_H_ENEMY