#include "Worker.h"

double const Worker::DEG_TO_RAD = 3.14 / 180.0f;
Worker::Worker(sf::Texture & texture, sf::Vector2f pos) :
	//m_position(0, 0),
	size(100),
	m_speed(10),
	m_timeCheck(5),
	m_radius(25)
	
{

	
	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = pos;
	m_rect.setPosition(m_position.x + 20 , m_position.y + 10);

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	m_sprite.setTexture(texture);
	m_sprite.setScale(0.1, 0.1);
	m_sprite.setPosition(m_position.x + 18, m_position.y + 20);
	

	//srand(time(0));
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

	//implimenting wander functionality
	wander(dt);

	int curX = round(m_sprite.getPosition().x / 50);
	int curY = round(m_sprite.getPosition().y / 50);
	m_surroundingCircle.setPosition(m_sprite.getPosition());
}

void Worker::wander(double dt)
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

void Worker::render(sf::RenderWindow & window)
{
	if (!collected && !m_swept) {
		window.draw(m_sprite);
		window.draw(m_surroundingCircle);
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

/*void Worker::distance(int rad, sf::Vector2f position)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_sprite.getPosition().x;
	int y2 = m_sprite.getPosition().y;


	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) <= ((m_radius + rad)))
	{
		collected = true;
	}
	
}*/


void  Worker::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{		
		collected = true;
	}
	
}

void  Worker::collisionSweeper(sf::Vector2f & sweeperPosition)
{
	if (sweeperPosition.x > m_rect.getPosition().x && sweeperPosition.x < m_rect.getPosition().x + 25
		&& sweeperPosition.y > m_rect.getPosition().y && sweeperPosition.y < m_rect.getPosition().y + 25)
	{
		m_swept = true;
	}

}



int Worker::getTileX()
{
	return m_rect.getPosition().x / 50;
}

int Worker::getTileY()
{
	return m_rect.getPosition().y / 50;
}

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

