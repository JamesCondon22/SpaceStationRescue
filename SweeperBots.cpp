#include "SweeperBots.h"


SweeperBots::SweeperBots(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100)

{

	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = pos;
	m_rect.setPosition(m_position.x, m_position.y + 10);

}


SweeperBots::~SweeperBots()
{
}

void SweeperBots::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);

}


void SweeperBots::update(double dt, sf::Vector2f playerPosition)
{

}

void SweeperBots::render(sf::RenderWindow & window)
{
	
	window.draw(m_rect);

}

sf::Vector2f SweeperBots::getPos()
{
	return m_rect.getPosition();
}

void  SweeperBots::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{
		collected = true;
	}

}
