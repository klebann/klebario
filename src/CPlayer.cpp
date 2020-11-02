//  __________________________________________
// | CPlayer.h - class implementation	      |
// | Jakub Kleban - November 2016             |
// |__________________________________________|
//

#include "CPlayer.h"


//Konstruktor
CPlayer::CPlayer(void)
	://Lista inicjalizacynja
		GelAble			(10),
		m_speed			(5.0f),
		tekst			(sf::Text()),
		font			(sf::Font()),
		cur_speed		(4.98f)
{
	srand(unsigned int(time(NULL)));
	//kó³ko//
	circle.setPointCount		(100); 
	circle.setPosition			(1500, 1500);
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

	circle.setOutlineThickness	(-1.5f);
	circle.setOutlineColor		(sf::Color(R,G,B));

	//Napis//
	setText(getMass());
}

//Konstruktor (z mas¹ i predkoœci¹)
CPlayer::CPlayer(int _mass, float _speed)
	:
	GelAble			(_mass),
	m_speed			(_speed),
	tekst			(sf::Text()),
	font			(sf::Font())
{
	//kó³ko//
	circle.setOrigin(getRadius(), getRadius());
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::Blue);

	//Napis//
	setText(getMass());
}

//Dekonstruktor
CPlayer::~CPlayer(void)
{
	m_speed = NULL;
}

//Update'a obiekt
bool CPlayer::upDate(float time, std::list<CFood*> *foods, std::list<Enemy*> *enemies, sf::View *camera, sf::Vector2f* _size, sf::Vector2f _scale)
{
	static bool check = false;
	setResistance();
	stayOnMap(camera);
	if (kolizja(foods, enemies, camera)) check = true;
	loseWeight();
	zoom(camera, _scale, _size);
	setPoints( getMass() );

	if (check) return true;
	else return false;
}

//Metoda sprawdza czy wyst¹pi³a kolizja
bool CPlayer::kolizja(std::list<CFood*> *foods, std::list<Enemy*> *enemies, sf::View *cam)
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

	std::list<Enemy*>::iterator j = enemies->begin();
	while (j != enemies->end())
	{
		int new_mass;
		switch ((*j)->Kolizja(this))
		{
		case 1:
			new_mass = this->getMass() + (*j)->getMass(); //nowa masa to suma

			setMass(new_mass);
			//cam->zoom(new_zoom);


			enemies->erase(j++); //i = list.erase(i);
			break;
		case 2:
			new_mass = this->getMass() + (*j)->getMass(); //nowa masa to suma

			(*j)->setMass(new_mass);

			return true; //œmieræ
			break;
		case 3:
			++j;
			break;
		default:
			break;
		}
	}
	return false;
}

//Metoda ustawia zoom kamery
void CPlayer::zoom(sf::View *cam, sf::Vector2f _scale, sf::Vector2f* _size)
{
	if (getMass() > 0 && getMass() <= 20)
	{
		cam->setSize( *_size );	
	}
	else if (getMass() > 20 && getMass() <= 100)
	{
		isAnimated = true;
		zoomAnimation( sf::Vector2f(_size->x * 1.5f, _size->y * 1.5f) , _scale, cam );
	}
	else if (getMass() > 100 && getMass() <= 300)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 2.5f, _size->y * 2.5f), _scale, cam);
	}
	else if (getMass() > 300 && getMass() <= 600)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 3.5f, _size->y * 3.5f), _scale, cam);
	}
	else if (getMass() > 600 && getMass() <= 1000)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 4.f, _size->y * 4.f), _scale, cam);
	}
	else if (getMass() > 1000 && getMass() <= 3000)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 4.5f, _size->y * 4.5f), _scale, cam);
	}
	else if (getMass() > 3000 && getMass() <= 5000)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 5.5f, _size->y * 5.5f), _scale, cam);
	}
	else if (getMass() > 5000 && getMass() <= 10000)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 6.5f, _size->y * 6.5f), _scale, cam);
	}
	else if (getMass() > 10000)
	{
		isAnimated = true;
		zoomAnimation(sf::Vector2f(_size->x * 8.5f, _size->y * 8.5f), _scale, cam);
	}
}

//zoom animation
void CPlayer::zoomAnimation(sf::Vector2f _size, sf::Vector2f _scale, sf::View *cam)
{
	if (isAnimated == false)
		return;

	if (isAnimated)
	{
		cam->setSize(cam->getSize().x + (animSpeed * _scale.x) , cam->getSize().y + (animSpeed * _scale.y ));

		//popraw to
		if (cam->getSize().x >= _size.x || cam->getSize().y >= _size.y )
		{
			cam->setSize({ _size.x , _size.y });
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

void CPlayer::loseWeight()
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
void CPlayer::setResistance()
{
	if (getMass() < 1000)
		resistance = getMass() * resistanceF;
	else if (getMass() < 5000)
		resistance = (getMass() * resistanceF / 10) + 2.f;
	else if (getMass() < 20000)
		resistance = (getMass() * resistanceF / 40) + 3.f;
	else
		resistance = 4.f;

	cur_speed = m_speed - resistance;
}