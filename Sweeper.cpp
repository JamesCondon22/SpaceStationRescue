#include "Sweeper.h"


double const Sweeper::DEG_TO_RAD = 3.14 / 180.0f;
double const Sweeper::RAD_TO_DEG = 180.0f / 3.14;
Sweeper::Sweeper() :
	m_position(1250, 1250),
	size(100),
	m_speed(10),
	m_timeCheck(5)

{
	if (!m_texture.loadFromFile("images/UFOsweeper.png"))
	{
		std::cout << "UFOsweeper png not loaded" << std::endl;
	}

	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	//m_rect.setTexture(m_texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	//m_position = pos;
	m_rect.setPosition(m_position.x + 20, m_position.y + 10);

	

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.1, 0.1);
	m_sprite.setPosition(m_position.x + 18, m_position.y + 20);

	//srand(time(0));
}


Sweeper::~Sweeper()
{
}

void Sweeper::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}


void Sweeper::update(double dt, sf::Vector2f playerPosition)
{
	if (!collected)
	{
		collisionPlayer(playerPosition);
		//std::cout << "updat" << std::endl;
	}

	//implimenting wander functionality
	wander(dt);

}

void Sweeper::wander(double dt)
{
	//start timer
	//check timer
	timer = m_clock.getElapsedTime().asSeconds();

	if (timer >= m_timeCheck)
	{

		m_random = (rand() % -90 + 90);
		m_rotation = m_random;
		//timer = 0;
		m_timeCheck += 5;

	}
	//int clocktimer = m_clock.getElapsedTime().asSeconds();
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

/*void Sweeper::render(sf::RenderWindow & window)
{
	if (!collected) {
		//window.draw(m_rect);
		window.draw(m_sprite);
	}

}*/

sf::Vector2f Sweeper::getPos()
{
	return m_rect.getPosition();
}

void  Sweeper::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{
		m_collected = true;
	}

}

void Sweeper::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	window.draw(m_label);
	window.draw(m_sprite);
}

void Sweeper::seek()
{
	//m_velocity = m_game->getPlayerPos() - m_position;
	m_velocity = normalise();
	m_velocity = m_velocity * m_maxSpeed;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
}

float Sweeper::getNewOrientation(float curOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-m_velocity.x, m_velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}

sf::Vector2f Sweeper::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}

// Returns the length of the vector
float Sweeper::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}