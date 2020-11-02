//  __________________________________________
// | MiniMap.h - class implementation		  |
// | Jakub Kleban - March 2k17				  |
// |__________________________________________|
//

#include "MiniMap.h"



MiniMap::MiniMap(int _width, int _height)
	:
	minimapView		(sf::FloatRect(0, 0, 3000.f, 3000.f)),
	minimapBG		({ _width*0.25f, _height*0.25f }),
	minimapFrame	({ _width*0.254f, _height*0.254f }),
	lineX			({ _width*0.25f, 0.25f }),
	lineY			({ 0.25f, _height*0.25f }),
	m_width			(_width),
	m_height		(_height)
{
	//Set MiniMap//
	// _________
	// |	|__|
	// |_______|
	//
	minimapView.setViewport(sf::FloatRect(0.74f, 0.01f, 0.25f, 0.25f));
	minimapBG.setOrigin(m_width*0.125f, 0 );
	minimapBG.setPosition( m_width*0.865f, m_height*0.01f); //0.74,0.01
	minimapBG.setFillColor(sf::Color(240, 240, 240, 255));
	minimapFrame.setOrigin( m_width*0.127f, m_width*0.002f);
	minimapFrame.setPosition(m_width*0.865f, m_height*0.01f);
	minimapFrame.setFillColor(sf::Color::Black);

	lineX.setOrigin(m_width*0.125f, 0);
	lineX.setPosition(m_width*0.865f, m_height*0.135f);
	lineY.setPosition(m_width*0.865f, m_height*0.01f);
	lineX.setFillColor(sf::Color::Black);
	lineY.setFillColor(sf::Color::Black);
}


MiniMap::~MiniMap()
{
}

//Metoda ustawia parametry i rysuje obiekt
void MiniMap::print(sf::RenderTarget& targ, sf::RenderStates states, std::list<CFood*> *foods, std::list<Enemy*> *enemies, CPlayer* _player)
{
	m_foods = foods;
	m_enemies = enemies;
	m_player = _player;

	draw(targ, states);
}

//Przeskalowuje minimape
void MiniMap::reSize(sf::Vector2f _scale, float _width, float _height, float mniejszy, float mniejsza_skala)
{
	//DANE//
	sf::Vector2f displacement;
	displacement.x = (_width - m_width);
	displacement.y = (_height - m_height);

	sf::Vector2f new_size;
	m_width = int(_width);
	m_height = int(_height);

	//ustaw rozmiar view
	minimapView.setSize((minimapView.getSize().x * _scale.x), (minimapView.getSize().y * _scale.y));
	minimapView.setSize(minimapView.getSize().x * 1/_scale.y, minimapView.getSize().y * 1/_scale.y);
	//minimapView.setViewport(sf::FloatRect(minimapView.getViewport().left, minimapView.getViewport().top, minimapView.getViewport().width * _scale.y, minimapView.getViewport().height * _scale.y));

	//rozmiar bialego kwadratu
	minimapBG.scale({ 1 / _scale.x, 1 / _scale.y });
	minimapBG.scale(_scale.y, _scale.y);

	////pozycja view
	//minimapView.setViewport( sf::FloatRect(	(minimapView.getViewport().left + (150 * _scale.x) - 150) / 600 , 
	//										minimapView.getViewport().top, 
	//										0.25f, 0.25f));

	//rozmiar obramowania
	minimapFrame.scale({ 1 / _scale.x, 1 / _scale.y });
	minimapFrame.scale(_scale.y, _scale.y);
	//minimapFrame.setPosition( (minimapBG.getPosition().x * 1.0020202f + (1.0020202f * _scale.x)), ((minimapBG.getPosition().y * 0.8f) + (0.8f * _scale.y)) );

	lineX.scale(1 / _scale.x, 1/_scale.y);
	lineX.scale(_scale.y, _scale.y);
}

//Updatuje pozycje line
void MiniMap::UpDate(CPlayer* _player)
{
	sf::Vector2f przesuniecie;
	przesuniecie.x = (_player->getPosition().y / 3000 * minimapBG.getSize().x )  - (minimapBG.getSize().x / 2);
	przesuniecie.y = (_player->getPosition().x / 3000 * minimapBG.getSize().y) - (minimapBG.getSize().y / 2);

	lineX.setPosition(600*0.865f, 600*0.135f + przesuniecie.x);
	lineY.setPosition(600*0.865f + (przesuniecie.y / float(m_width / 600) * float(m_height / 600)), 600*0.01f);
}

//Metoda rysuj¹ca obiekt
void MiniMap::draw(sf::RenderTarget& targ, sf::RenderStates states) const
{
	targ.draw(minimapFrame);
	targ.draw(minimapBG);

	//MINIMAPA//
	targ.setView(minimapView);

	for (std::list<CFood*>::iterator i = m_foods->begin(); i != m_foods->end(); i++)
	{
		(*i)->draw(targ, sf::RenderStates::Default);
	}
	for (std::list<Enemy*>::iterator j = m_enemies->begin(); j != m_enemies->end(); j++)
	{
		(*j)->draw(targ, sf::RenderStates::Default);
	}
	m_player->draw(targ, sf::RenderStates::Default);

	targ.setView(targ.getDefaultView());

	targ.draw(lineX);
	targ.draw(lineY);
}