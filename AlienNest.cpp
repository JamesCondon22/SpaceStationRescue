#include "AlienNest.h"


AlienNest::AlienNest(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100)
{

	m_rect.setOrigin(m_position.x + 100 / 2, m_position.y + 100 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(100, 100));
	m_position = pos;
	m_rect.setPosition(m_position);
	
	m_surroundingCircle.setRadius(150);
	m_surroundingCircle.setPosition(0,0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	//std::cout << m_surroundingCircle.getOrigin().x << ", " << m_surroundingCircle.getOrigin().y << std::endl;
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0,0,0,40));
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
	//m_surroundingCircle.rotate(2);
	//window.setView(follow);
	window.draw(m_surroundingCircle);
	window.draw(m_rect);
	
}

sf::Vector2f AlienNest::getPos()
{
	return m_rect.getPosition();
}
