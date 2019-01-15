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
	
	m_bullet = new Bullet(m_position, 10.0f, false);

	m_surroundingCircle.setRadius(150);
	m_surroundingCircle.setPosition(0,0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
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


void AlienNest::update(double dt, sf::Vector2f position, int rad, double rot)
{
	checkCollision(position, rad);
	
	if (shoot)
	{
		m_bullet->seek(position, m_position, rot);
	}

}

void AlienNest::checkCollision(sf::Vector2f position, int rad)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_position.x;
	int y2 = m_position.y;
	
	int radius1 = 150;
	int radius2 = rad;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2))
	{
		shoot = true;
	}
}

void AlienNest::render(sf::RenderWindow & window)
{
	window.draw(m_surroundingCircle);
	window.draw(m_rect);
	if (shoot)
	{
		m_bullet->render(window);
	}
	
}

sf::Vector2f AlienNest::getPos()
{
	return m_rect.getPosition();
}


