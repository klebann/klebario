//  __________________________________________
// | Control.h - class implementation	      |
// | Jakub Kleban - December 2016             |
// |__________________________________________|
//

#include "Control.h"


Control::Control(void)
	:
	howLazy(5.f),
	whereMaxSpeed(100.f),
	playerPosition(300.f, 300.f),
	enableCheating(false)
{

}

Control::Control(float _howLazy, float _whereMaxSpeed)
	:
	playerPosition(300.f,300.f),
	howLazy(_howLazy),
	whereMaxSpeed(_whereMaxSpeed),
	enableCheating(false)
{

}

Control::~Control(void)
{
	howLazy = NULL;
	whereMaxSpeed = NULL;
	playerPosition.x = NULL;
	playerPosition.y = NULL;
	enableCheating = NULL;
}

void Control::upDate(const sf::RenderWindow *okno, CPlayer *player, sf::View *camera)
{
	if (check(okno) == true)
	move(player, camera);
}

void Control::move(CPlayer *player, sf::View *camera)
{
	if (distanceTo() >= whereMaxSpeed)
	{
		updateDirection();
		player->mymove( (moveDirection.x * player->getCurrentSpeed()), (moveDirection.y * player->getCurrentSpeed()), camera);
	}

	else if (currentDistance < whereMaxSpeed  && currentDistance >= howLazy)
	{
		/*howLazy = 0%
		>=whereMaxSpeed = 100%*/
		updateDirection();

		float procent = (currentDistance - howLazy) / whereMaxSpeed;
		
		player->mymove((moveDirection.x * player->getCurrentSpeed() * procent), (moveDirection.y * player->getCurrentSpeed() * procent), camera);
	}

}

bool Control::check(const sf::RenderWindow *okno)
{
	mousePosition = sf::Mouse::getPosition(*okno);
	if (distanceTo() >= howLazy)
		return true;
	else
		return false;
}

float Control::distanceTo()
{
	currentDistance = std::sqrt(std::pow((playerPosition.x - mousePosition.x), 2) + std::pow((playerPosition.y - mousePosition.y), 2));
	return currentDistance;
}

void Control::updateDirection()
{
	//setup
	sf::Vector2f final = sf::Vector2f(mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y);
	float summary = std::sqrt(std::pow(final.x, 2) + std::pow(final.y, 2));

	moveDirection = sf::Vector2f((final.x / summary), (final.y / summary));
}

void Control::godMode(CPlayer *player)
{
	
	if (enableCheating)
	{
		player->setSpeed(5.f);
		enableCheating = false;
		std::cout << "Cheating off" << std::endl;
	}
	else
	{
		player->setSpeed(15.f);
		enableCheating = true;
		std::cout << "Cheating on" << std::endl;
	}
}