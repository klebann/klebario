//  __________________________________________
// | Enemy.cpp - class implementation	      |
// | Jakub Kleban - December 2016             |
// |__________________________________________|
//

#include "Enemy.h"

//Konstruktor
Enemy::Enemy(void)
	:
	GelAble(),
	m_speed(5.f),
	range(300.f)
{
	float _mass = float(std::rand() % 500)+10;
	setMass(int(_mass));

	unsigned char R = rand() % 255, G = rand() % 255, B = rand() % 255; //random color RGB
	circle.setFillColor(sf::Color(R, G, B));
	circle.setOutlineThickness(-1.5f);

	if (R >= 30 && G >= 30 && B >= 30)
	{
		R -= 30; G -= 30; B -= 30;
	}
	else
	{
		if (R <= 30)
			R = 0;
		else
			R -= 30;

		if (G <= 30)
			G = 0;
		else
			G -= 30;

		if (B <= 30)
			B = 0;
		else
			B -= 30;
	}

	circle.setOutlineThickness(-1.5f);
	circle.setOutlineColor(sf::Color(R, G, B));

	circle.setPointCount(20);
}

Enemy::~Enemy()
{
	m_speed = NULL;
	range = NULL;
}

//Sprawdza czy zachodzi kolizja
int Enemy::Kolizja(CPlayer* _player)
{
	float dystans = Distance(_player);
											  //sprawdzam
	float odejmij; // zmienna odejmuje promien mniejszego
	if (_player->getRadius() <= this->getRadius()) odejmij = _player->getRadius();
	else odejmij = this->getRadius();

	float suma = this->getRadius() + _player->getRadius();
	if (dystans < (suma-odejmij))
	{
		if (_player->getMass() >= getMass() * 1.25f) return 1;
		else if (_player->getMass() < getMass() * 0.85f) return 2;
		else return 3;
	}
	else return 3;
}

//Sprawdza czy zachodzi kolizja
bool Enemy::Kolizja(Enemy* _enemy)
{
	float dystans = Distance(_enemy);
	//sprawdzam
	float odejmij; // zmienna odejmuje promien mniejszego
	if (_enemy->getRadius() <= this->getRadius()) odejmij = _enemy->getRadius();
	else odejmij = this->getRadius();

	float suma = this->getRadius() + _enemy->getRadius();
	if (dystans < (suma - odejmij))
	{
		if (_enemy->getMass() >= getMass() * 1.25f) return true;
	}
	return false;
}

//Update'a obiekt
int Enemy::upDate(float time, CPlayer* _player, std::list<CFood*> *foods, std::list<Enemy*> *enemies)
{
	int ile = 0;
	setResistance();

	whereGo(_player, foods, enemies);

	FoodKolizja(foods);   ///DUZE OBCI¥¯ENIE!
	ile += Kanibal(enemies);	///TROCHE MNIEJSZE XD

	loseWeight();
	return ile;
}

///Quo vadis?!
void Enemy::whereGo(CPlayer* _player, std::list<CFood*> *foods, std::list<Enemy*> *enemies)
{
	std::vector < Enemy* > closeEnemies;
	std::list<Enemy*>::iterator i = enemies->begin(); //odliczanie

	while (i != enemies->end()) //szukanie najblizszego
	{
		float odleglosc = Distance((*i));
		if (odleglosc < range) //tylko te w zasiegu
		{
			closeEnemies.push_back((*i));
		}
		i++;
	}

	if (isNear(_player) && !(closeEnemies.empty()))
	{
		Enemy* bestEnemy = BestFrom(closeEnemies);

		if (_player->getMass() < (this->getMass() * 0.85f))
		{
			Move(_player, attack);
		}
		else if (_player->getMass() > (this->getMass() * 1.25f))
		{
			Move(_player, run);
		}
		else
		{
			if (bestEnemy->getMass() < (this->getMass() * 0.85f))
			{
				Move(bestEnemy, attack);
			}
			else if (bestEnemy->getMass() > (this->getMass() * 1.25f))
			{
				Move(bestEnemy, run);
			}
			else
			{
				Collect(foods);
			}
		}
	}
	else if (isNear(_player))
	{
		if (_player->getMass() < (this->getMass() * 0.85f))
		{
			Move(_player, attack);
		}
		else if (_player->getMass() > (this->getMass() * 1.25f))
		{
			Move(_player, run);
		}
		else
		{
			Collect(foods);
		}
	}
	else if (!closeEnemies.empty())
	{
		///NAJWIEKSZE SPOSRÓD ENEMY///
		Enemy* beastEnemy = BestFrom(closeEnemies);

		if (beastEnemy->getMass() < (this->getMass() * 0.85f))
		{
			Move(beastEnemy, attack);
		}
		else if (beastEnemy->getMass() > (this->getMass() * 1.25f))
		{
			Move(beastEnemy, run);
		}
		else
		{
			Collect(foods);
		}
	}
	else
	{
		Collect(foods);
	}
}

//Sprawdza czy zachodzi kolizja z jedzeniem
void Enemy::FoodKolizja(std::list<CFood*> *foods)
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

///Sprawdza czy zachodzi kolizja z kolegami
int Enemy::Kanibal(std::list<Enemy*> *enemies) 
{
	int ile=0;
	std::list<Enemy*>::iterator j = enemies->begin();
	while (j != enemies->end())
	{
		int new_mass;
		if ((*j)->Kolizja(this))///WIEKSZY
		{
			ile++; //licznik

			new_mass = this->getMass() + (*j)->getMass(); //nowa masa to suma
			setMass(new_mass);

			enemies->erase(j++); //i = list.erase(i);
		}
		else
			++j;
	}
	return ile;
}

//Zbiera jedzonka w poblizu
void Enemy::Collect(std::list<CFood*> *foods)
{
	std::list<CFood*>::iterator best = foods->begin();
	std::list<CFood*>::iterator i = foods->begin();
	float poprzedni = Distance((*i));
	
	while (i != foods->end()) //szukanie najblizszego
	{
		float dystans = Distance((*i));
		if (dystans < poprzedni)
		{	
			poprzedni = dystans;
			best = i;
		}
		i++;
	}

	goFood((*best));
}

//czy jest w polu widzenia playera
bool Enemy::isNear(CPlayer* _player)
{
	float dystans = Distance(_player);

	if (dystans <= range)
	{
		return true;
	}
	else return false;
}

//Metoda liczy odleg³oœæ
float Enemy::Distance(CPlayer* _player)
{
	//zbieram pozycje
	sf::Vector2f Venemy = this->getPosition();
	sf::Vector2f Vplayer = _player->getPosition();

	//licze
	float dx = Venemy.x - Vplayer.x; //odleg³oœæ w osi x
	float dy = Venemy.y - Vplayer.y; //odleg³oœæ w osi y

	return sqrt(dx * dx + dy * dy); //pitagolas
}

//Metoda liczy odleg³oœæ
float Enemy::Distance(Enemy* _enemy)
{
	//zbieram pozycje
	sf::Vector2f Venemy = this->getPosition();
	sf::Vector2f Vme = _enemy->getPosition();

	//licze
	float dx = Venemy.x - Vme.x; //odleg³oœæ w osi x
	float dy = Venemy.y - Vme.y; //odleg³oœæ w osi y

	return sqrt(dx * dx + dy * dy); //pitagolas
}

//Metoda liczy odleg³oœæ
float Enemy::Distance(CFood* _food)
{
	//zbieram pozycje
	sf::Vector2f Venemy = this->getPosition();
	sf::Vector2f Vfood = _food->getPosition();

	//licze
	float dx = Venemy.x - Vfood.x; //odleg³oœæ w osi x
	float dy = Venemy.y - Vfood.y; //odleg³oœæ w osi y

	return sqrt(dx * dx + dy * dy); //pitagolas
}

///Metoda zwraca najwiekszego enemy z wektora enemies
Enemy* Enemy::BestFrom(std::vector < Enemy* > _vector)
{
	Enemy *bestEnemy = _vector[0];
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (_vector[i]->getMass() > bestEnemy->getMass())
		{
			bestEnemy = _vector[i];
		}
	}

	return bestEnemy;
}

//Metoda ucieka lub goni playera
void Enemy::Move(CPlayer* _player, Direction action)
{
	if (action == attack)
	{
		updateDirection(_player);
		circle.move((moveDirection.x * cur_speed), (moveDirection.y * cur_speed));
		stayOnMap();
	}
	else if (action == run)
	{
		updateDirection(_player);
		circle.move((-moveDirection.x * cur_speed), (-moveDirection.y * cur_speed));
		stayOnMap();
	}
}

//Metoda ucieka lub goni enemy
void Enemy::Move(Enemy* _enemy, Direction action)
{
	if (action == attack)
	{
		updateDirection(_enemy);
		circle.move((moveDirection3.x * cur_speed), (moveDirection3.y * cur_speed));
		stayOnMap();
	}
	else if (action == run)
	{
		updateDirection(_enemy);
		circle.move((-moveDirection3.x * cur_speed), (-moveDirection3.y * cur_speed));
		stayOnMap();
	}
}

///Metoda ³apie jedzonko
void Enemy::goFood(CFood* _food)
{
	updateDirection(_food);
	circle.move((moveDirection2.x * cur_speed), (moveDirection2.y * cur_speed));
}

void Enemy::updateDirection(CPlayer* _player)
{
	//setup
	sf::Vector2f final = sf::Vector2f(_player->getPosition().x - this->getPosition().x, _player->getPosition().y - this->getPosition().y);
	float summary = std::sqrt(std::pow(final.x, 2) + std::pow(final.y, 2));

	moveDirection = sf::Vector2f((final.x / summary), (final.y / summary));
}

void Enemy::updateDirection(Enemy* _enemy)
{
	//setup
	sf::Vector2f final = sf::Vector2f(_enemy->getPosition().x - this->getPosition().x, _enemy->getPosition().y - this->getPosition().y);
	float summary = std::sqrt(std::pow(final.x, 2) + std::pow(final.y, 2));

	moveDirection3 = sf::Vector2f((final.x / summary), (final.y / summary));
}

void Enemy::updateDirection(CFood* _food)
{
	//setup
	sf::Vector2f final = sf::Vector2f(_food->getPosition().x - this->getPosition().x, _food->getPosition().y - this->getPosition().y);
	float summary = std::sqrt(std::pow(final.x, 2) + std::pow(final.y, 2));

	moveDirection2 = sf::Vector2f((final.x / summary), (final.y / summary));
}

//Metoda ustawia obiekt na mapie jezeli z niej wyjdzie
void Enemy::stayOnMap()
{
	if (this->getPosition().x > 3000.0f)
		this->setPosition(sf::Vector2f(3000.f, this->getPosition().y));
	else if (this->getPosition().x < 0.f)
		this->setPosition(sf::Vector2f(0.f, this->getPosition().y));

	if (this->getPosition().y > 3000.0f)
		this->setPosition(sf::Vector2f(this->getPosition().x, 3000.f));
	else if (this->getPosition().y < 0.f)
		this->setPosition(sf::Vector2f(this->getPosition().x, 0.f));
}

void Enemy::loseWeight()
{
	if (getMass() > 10)
	{
		lostMassPerFrame = lossMassF * getMass();

		Mcollector += lostMassPerFrame;
		if (Mcollector >= 1.f)
		{
			setMass(getMass() - int(Mcollector));
			Mcollector -= int(Mcollector);
		}
	}
}

//ustawia aktualny opór cia³a
void Enemy::setResistance()
{
	if (getMass() < 1000)
		resistance = getMass() * resistanceF;
	else if (getMass() < 5000)
		resistance = (getMass() * resistanceF / 10) + 2.f; //max 2.015
	else
		resistance = 2.1f;

	cur_speed = m_speed - (resistance+2.2f);
}