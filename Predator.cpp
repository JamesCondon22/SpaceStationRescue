#include "Predator.h"

double const Predator::DEG_TO_RAD = 3.14 / 180.0f;
Predator::Predator(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100),
	m_speed(10),
	m_timeCheck(5)

{

	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = pos;
	m_rect.setPosition(m_position.x + 20, m_position.y + 10);

}


Predator::~Predator()
{
}

void Predator::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}


void Predator::update(double dt, sf::Vector2f playerPosition)
{
	if (!collected)
	{
		collisionPlayer(playerPosition);
	}

	//implimenting wander functionality
	wander(dt);

	int curX = round(m_sprite.getPosition().x / 50);
	int curY = round(m_sprite.getPosition().y / 50);
}

void Predator::wander(double dt)
{
	//start timer
	//check timer
	timer = m_clock.getElapsedTime().asSeconds();

	if (timer >= m_timeCheck)
	{

		m_random = (rand() % -90 + 90);
		m_rotation = m_random;
		m_timeCheck += 5;

	}
	//random angle assigned
	//rotation set to new angle

	m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_sprite.setPosition(m_rect.getPosition());
	m_rect.setRotation(m_rotation - 90);
	m_sprite.setRotation(m_rect.getRotation());

	//randomize rotation
	//repeat

}

void Predator::render(sf::RenderWindow & window)
{
	if (!collected) {
		window.draw(m_rect);
	}

}

sf::Vector2f Predator::getPos()
{
	return m_rect.getPosition();
}

void  Predator::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{
		collected = true;
	}

}

int Predator::getTileX()
{
	return m_sprite.getPosition().x / 50;
}

int Predator::getTileY()
{
	return m_sprite.getPosition().y / 50;
}

void Predator::changeDirection()
{
	m_speed = -m_speed;
}

