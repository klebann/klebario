//  __________________________________________
// | MiniMap.h - class definition			  |
// | Jakub Kleban - March 2k17				  |
// |__________________________________________|
//

#ifndef _H_MINIMAP
#define _H_MINIMAP

#include <SFML/Graphics.hpp>
#include <list>
#include "CFood.h"
#include "Enemy.h"

class MiniMap : public sf::Drawable
{
public:
	MiniMap(int _width, int _height);
	~MiniMap();

	///
	///Metoda ustawia parametry i rysuje obiekt
	///
	void print(sf::RenderTarget& targ, sf::RenderStates states, std::list<CFood*> *foods, std::list<Enemy*> *enemies, CPlayer* _player);

	///
	///Przeskalowuje minimape
	///
	void reSize(sf::Vector2f _scale, float _width, float _height, float mniejszy, float mniejsza_skala);

	///
	///Updatuje pozycje lini
	///
	void UpDate(CPlayer* _player);

private:

	///
	///Metoda rysuj¹ca obiekt
	///
	virtual void draw(sf::RenderTarget& targ, sf::RenderStates states) const;

	int						m_width;					//szerokosc okna
	int						m_height;					//wysokosc okna
	sf::View				minimapView;				//minimapa
	sf::RectangleShape		minimapBG;					//bialy prostokat
	sf::RectangleShape		minimapFrame;				//czarny prostokat
	std::list<CFood*>*		m_foods;
	std::list<Enemy*>*		m_enemies;
	CPlayer*				m_player;
	sf::RectangleShape		lineX;						//celownik mapy na osi X
	sf::RectangleShape		lineY;						//celownik mapy na osi Y

};

#endif //_H_MINIMAP