#include "Worker.h"

double const Worker::DEG_TO_RAD = 3.14 / 180.0f;
Worker::Worker(sf::Texture & texture, sf::Vector2f pos) :
	size(100),
	m_speed(10),
	m_timeCheck(5),
	m_radius(25)
	
{

	
	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(20, 20));
	m_position = pos;
	m_rect.setPosition(m_position.x + 20 , m_position.y + 10);

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	
}


Worker::~Worker()
{
}

void Worker::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}

/// <summary>
/// Update function calls primary functions
/// Takes a time and 2D vector
/// </summary>
/// <param name="dt"></param>
/// <param name="playerPosition"></param>
void Worker::update(double dt, sf::Vector2f playerPosition)
{
	if (!collected)
	{
		collisionPlayer(playerPosition);
	}

	//implimenting wander functionality
	wander(dt);

	int curX = round(m_rect.getPosition().x / 50);
	int curY = round(m_rect.getPosition().y / 50);
	m_surroundingCircle.setPosition(m_rect.getPosition());
}

/// <summary>
/// Wander function
/// Causes the worker to meander around the screen at all times
/// Changes the rotation based on time
/// Takes a time
/// </summary>
/// <param name="dt"></param>
void Worker::wander(double dt)
{
	//start timer
	timer = m_clock.getElapsedTime().asSeconds();

	//check timer
	if (timer >= m_timeCheck)
	{
		//random angle assigned
		//rotation set to new angle
		//randomize rotation
		m_random = (rand() % -90 + 90);
		m_rotation = m_random;
		m_timeCheck += 5;
		
	}

	//Assigning the new rotation to the player
	m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_sprite.setPosition(m_rect.getPosition());
	m_rect.setRotation(m_rotation - 90);
	m_sprite.setRotation(m_rect.getRotation());
	
}

/// <summary>
/// basic render
/// </summary>
/// <param name="window"></param>
void Worker::render(sf::RenderWindow & window)
{
	if (!collected && !m_swept) {
		window.draw(m_rect);
	}
	
}

sf::Vector2f Worker::getPos()
{
	return m_rect.getPosition();
}

bool Worker::getCollision()
{
	return increment;
}

/// <summary>
/// Checks collision with the player based on rectangles
/// Takes a 2D vector
/// </summary>
/// <param name="playerPosition"></param>
void  Worker::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{		
		collected = true;
	}
	
}

/// <summary>
/// Checks collision with the sweepers based on rectangles
/// Takes a 2D vector
/// </summary>
/// <param name="sweeperPosition"></param>
void  Worker::collisionSweeper(sf::Vector2f & sweeperPosition)
{
	if (sweeperPosition.x > m_rect.getPosition().x && sweeperPosition.x < m_rect.getPosition().x + 25
		&& sweeperPosition.y > m_rect.getPosition().y && sweeperPosition.y < m_rect.getPosition().y + 25)
	{
		m_swept = true;
	}

}


/// <summary>
/// function to etirn current tile x coordinate
/// </summary>
/// <returns></returns>
int Worker::getTileX()
{
	return m_rect.getPosition().x / 50;
}

/// <summary>
/// function to etirn current tile y coordinate
/// </summary>
/// <returns></returns>
int Worker::getTileY()
{
	return m_rect.getPosition().y / 50;
}

//rebounding
void Worker::changeDirection()
{
	m_speed = -m_speed;
}

bool Worker::getCollected()
{
	return collected;
}

int Worker::getRadius()
{
	return m_radius;
}

