#include "Worker.h"


Worker::Worker(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100)
	
{
	
	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = pos;
	m_rect.setPosition(m_position.x + 20 , m_position.y + 10);
	
}


Worker::~Worker()
{
}

void Worker::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);

}


void Worker::update(double dt, sf::Vector2f playerPosition)
{
	if (!collected)
	{
		collisionPlayer(playerPosition);
	}
}

void Worker::render(sf::RenderWindow & window)
{
	if (!collected) {
		window.draw(m_rect);
	}
	
}

sf::Vector2f Worker::getPos()
{
	return m_rect.getPosition();
}

void  Worker::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{		
		collected = true;				
	}
	
}
