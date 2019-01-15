#include "Sweeper.h"


double const Sweeper::DEG_TO_RAD = 3.14 / 180.0f;
double const Sweeper::RAD_TO_DEG = 180.0f / 3.14;
/// <summary>
/// Constructor function
/// </summary>
/// <param name="texture"></param>
/// <param name="position"></param>
Sweeper::Sweeper(sf::Texture texture, sf::Vector2f position) :
	m_position(0, 0),
	m_texture(texture),
	size(100),
	m_speed(20),
	m_timeCheck(8),
	m_collected(false),
	m_radius(150),
	m_flee(false),
	m_maxSpeed(1)

{

	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = position;
	m_rect.setPosition(m_position.x + 20, m_position.y + 10);

	//circle detection
	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	//std::cout << m_surroundingCircle.getOrigin().x << ", " << m_surroundingCircle.getOrigin().y << std::endl;
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	//assigning sprite textures
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.1, 0.1);
	m_sprite.setPosition(m_position.x + 18, m_position.y + 20);

}


Sweeper::~Sweeper()
{
}

void Sweeper::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}


void Sweeper::update(double dt, sf::Vector2f playerPosition, int rad, sf::Vector2f workerPos)
{
	radiusCollisionPlayer(playerPosition, rad);
	m_position = m_sprite.getPosition();
	if (!collected)
	{
		collisionPlayer(playerPosition);
	}

	//checking for flee detection
	if (m_flee == true)
	{
		KinematicFlee(playerPosition);
	}
	
	//checks how far the player is from the sweepers
	distance(400, playerPosition);
	if (m_flee == false)
	{
		//implimenting wander functionality
		wander(dt);
		std::cout << "flee is " << m_flee << std::endl;
	}
	

	m_surroundingCircle.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 10);

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
	m_sprite.setPosition(m_sprite.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_sprite.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_sprite.setPosition(m_sprite.getPosition());
	m_sprite.setRotation(m_rotation - 90);
	m_sprite.setRotation(m_rect.getRotation());

	//randomize rotation
	//repeat

}


sf::Vector2f Sweeper::getPos()
{
	return m_rect.getPosition();
}

/// <summary>
/// Actual collision with the player
/// Checks the obj's bumping
/// </summary>
/// <param name="playerPosition"></param>
void  Sweeper::collisionPlayer(sf::Vector2f & playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{
		m_collected = true;
	}

}

/// <summary>
/// Collision detection with the view of the sweeper to engage flee function
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
void Sweeper::radiusCollisionPlayer(sf::Vector2f position, int rad)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_sprite.getPosition().x;
	int y2 = m_sprite.getPosition().y;

	int radius1 = 150;
	int radius2 = rad;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2))
	{
		m_flee = true;
	}
}

void Sweeper::distance(int distance, sf::Vector2f position)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_sprite.getPosition().x;
	int y2 = m_sprite.getPosition().y;


	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) > distance)
	{
		m_flee = false;
		
	}
}

void Sweeper::render(sf::RenderWindow & window)
{
	if (!m_collected)
	{
		window.draw(m_sprite);
		window.draw(m_surroundingCircle);
	}
	
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

int Sweeper::getTileX()
{
	return m_sprite.getPosition().x / 50;
}

int Sweeper::getTileY()
{
	return m_sprite.getPosition().y / 50;
}


void Sweeper::changeDirection()
{
	m_speed = -m_speed;
}

void Sweeper::KinematicFlee(sf::Vector2f playerPos)
{
	m_position = m_sprite.getPosition();
	m_velocity = playerPos - m_position;
	m_velocity = normalise();
	m_velocity = m_velocity * 0.5f;
	m_rotation = getNewRotation(m_rotation, m_velocity);
	m_position = m_position - m_velocity;
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);

}

float Sweeper::getNewRotation(float currentRotation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentRotation;
	}
}