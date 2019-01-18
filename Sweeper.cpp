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
	m_radius(150),
	m_flee(false),
	m_maxSpeed(1),
	m_wander(true),
	wallcollide(false),
	m_wanderCollide(false),
	m_seeking(true),
	m_velocity(0.2,0.2)

{
	//setting up the rectangle
	m_rect.setOrigin(m_position.x + 15 / 2, m_position.y + 15 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(25, 25));
	m_position = position;
	m_rect.setPosition(m_position.x + 20, m_position.y + 10);

	//circle detection
	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

}


Sweeper::~Sweeper()
{
}

void Sweeper::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}


/// <summary>
/// Update function
/// Calls all primary functions
/// Takes the time, vector position, and integer
/// </summary>
/// <param name="dt"></param>
/// <param name="playerPosition"></param>
/// <param name="radPlayer"></param>
void Sweeper::update(double dt, sf::Vector2f playerPosition, int radPlayer)
{
	
	if (alive) {
	radiusCollisionPlayer(playerPosition, radPlayer);
	m_position = m_rect.getPosition();
	if (!collected)
	{
		collisionPlayer(playerPosition);
	}

	//checking for flee detection
	if (m_flee)
	{
		KinematicFlee(playerPosition);
	}
	
	
	
	//checks how far the player is from the sweepers
	distance(300, playerPosition);
	
	//implimenting wander functionality
	if (m_wander)
	{
		wander(dt);
	}
		

	m_position = m_position + m_velocity;
	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_rect.getPosition().x, m_rect.getPosition().y + 10);
		m_position = m_position + m_velocity;
		m_sprite.setPosition(m_position);
		m_surroundingCircle.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 10);
	}
}

void Sweeper::wander(double dt)
{
	//start timer
	//check timer
	timer = m_clock.getElapsedTime().asSeconds();

	if (timer >= m_timeCheck)
	{
		int min = -2;
		int max = 2;
		float r = (float)rand() / (float)RAND_MAX;
		m_random = min + r * (max - min);
		m_velocity.x = m_random;

		float random = 0;
		int minSec = -2;
		int maxSec = 2;
		float rSec = (float)rand() / (float)RAND_MAX;
		random = minSec + rSec * (maxSec - minSec);
		m_velocity.y = random;

		m_velocity.x = m_velocity.x * m_speed;
		m_velocity.y = m_velocity.y * m_speed;
		//std::cout << "velocity x: " << m_velocity.x << "  velocity y: " << m_velocity.y << std::endl;
		//timer = 0;
		m_timeCheck += 5;
		

	}

	m_velocity = normalise();
	m_velocity = m_velocity * 0.2f;

	m_rect.setRotation(m_rotation - 90);
	m_sprite.setRotation(m_rect.getRotation());
	

	//randomize rotation
	//repeat

}

void Sweeper::kill()
{
	alive = false;
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
void  Sweeper::collisionPlayer(sf::Vector2f playerPosition)
{
	if (playerPosition.x > m_rect.getPosition().x && playerPosition.x < m_rect.getPosition().x + 25
		&& playerPosition.y > m_rect.getPosition().y && playerPosition.y < m_rect.getPosition().y + 50)
	{
		m_collected = true;
	}
}

/// <summary>
/// Collision detection with the view of the sweeper to engage flee function
/// Takes a vector psition and an integer
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
void Sweeper::radiusCollisionPlayer(sf::Vector2f position, int rad)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_rect.getPosition().x;
	int y2 = m_rect.getPosition().y;

	int radius1 = 150;
	int radius2 = rad;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2) && wallcollide == false)
	{
		m_flee = true;
	}
	else
	{
		m_flee = false;
	}
}

/// <summary>
/// Checks range for worker to seek them at range
/// Also sets collision
/// Adds to the count of workers collected by the sweeper
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
/// <param name="swept"></param>
void Sweeper::radiusCollisionWorker(sf::Vector2f position, int rad, bool swept)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_rect.getPosition().x;
	int y2 = m_rect.getPosition().y;

	int radius1 = 150;
	int radius2 = rad;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2) && swept == false)
	{
		seek(position);
		if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < 75)
		{
			m_scoreCount++;
		}
	}
}

/// <summary>
/// Basic function that checks distance between two vector positions
/// takes an integer and a 2d vector
/// </summary>
/// <param name="distance"></param>
/// <param name="position"></param>
void Sweeper::distance(int distance, sf::Vector2f position)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_rect.getPosition().x;
	int y2 = m_rect.getPosition().y;


	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) > distance)
	{
		m_flee = true;
		wallcollide = false;
		m_seeking = false;
	}
}


/// <summary>
/// simple render
/// </summary>
/// <param name="window"></param>
void Sweeper::render(sf::RenderWindow & window)
{
	if (alive)
	{
		window.draw(m_rect);
	}
	

}

/// <summary>
/// seek Function that moves the sweeper towards the workers 
/// takes a 2D vector
/// </summary>
/// <param name="workerPos"></param>
void Sweeper::seek(sf::Vector2f workerPos)
{

	m_velocity = workerPos - m_position;
	m_velocity = normalise();


	m_velocity = m_velocity * 0.2f;

	m_rotation = getNewRotation(m_rotation, m_velocity);

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

/// <summary>
/// Math function for movement
/// Normalises a vector
/// </summary>
/// <returns></returns>
sf::Vector2f Sweeper::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}

/// Returns the length of the vector
float Sweeper::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

//returns tile xPosition of an obj
int Sweeper::getTileX()
{
	return m_rect.getPosition().x / 50;
}

//return tile yPosition of an obj
int Sweeper::getTileY()
{
	return m_rect.getPosition().y / 50;
}

/// <summary>
/// Used for rebounding off of walls
/// </summary>
void Sweeper::changeDirection()
{
	
	m_velocity = m_velocity * -0.2f;
	wallcollide = true;

}

/// <summary>
/// Flee function
/// Used to flee from the player charachter at range
/// Takes a vector position
/// </summary>
/// <param name="playerPos"></param>
void Sweeper::KinematicFlee(sf::Vector2f playerPos)
{
	m_velocity =  m_position - playerPos;
	m_velocity = normalise();
	
	
	m_velocity = m_velocity * 0.2f;
	
	m_rotation = getNewRotation(m_rotation, m_velocity);
	m_wanderCollide = false;
	

	
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

/// <summary>
/// Just a function to pass on the score to the player
/// </summary>
/// <returns></returns>
int Sweeper::getScoreCount()
{
	return m_scoreCount;
}