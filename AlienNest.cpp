#include "AlienNest.h"


AlienNest::AlienNest(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100)
{
	
	m_rect.setOrigin(m_position.x + 30 / 2, m_position.y + 50 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(100, 100));
	m_position = pos;
	m_rect.setPosition(m_position);

}


AlienNest::~AlienNest()
{
}

void AlienNest::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);

}


void AlienNest::update(double dt)
{



}

void AlienNest::render(sf::RenderWindow & window)
{
	//window.setView(follow);
	window.draw(m_rect);
}

sf::Vector2f AlienNest::getPos()
{
	return m_rect.getPosition();
}
