#include "Bullet.h"

double const Bullet::DEG_TO_RAD = 3.14 / 180.0f;
double const Bullet::RAD_TO_DEG = 180.0f / 3.14;
/// <summary>
/// initialises the bullet and passes a position, rotation
/// checks if the there is a player or a predator firing the bullet 
/// </summary>
/// <param name="pos"></param>
/// <param name="rotation"></param>
/// <param name="isPlayer"></param>
/// <param name="isPred"></param>
Bullet::Bullet(sf::Vector2f pos, float rotation, bool isPlayer, bool isPred) :
	m_rotation(rotation),
	m_position(0,0),
	m_velocity(0,0)
{
	//sets the bullet speed accordingly
	if (isPlayer)
	{
		m_speed = 3;
	}
	else if (isPred)
	{
		m_speed = 1;
	}
	else
	{
		m_speed = 3;
	}
	//sets lifespan
	m_life = 0;
	//loads corresponding texture 
	if (isPlayer)
	{
		m_texture.loadFromFile("bullet.png");
	}
	else
	{
		m_texture.loadFromFile("images/alienBullet.png");
	}
	
	m_rect.setSize(sf::Vector2f(10, 10));
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);
	m_position = pos;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);

	m_surroundingCircle.setRadius(10);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));
}




Bullet::~Bullet()
{
}
/// <summary>
/// returns the bullet position
/// </summary>
/// <returns></returns>
sf::Vector2f Bullet::getPosition()
{
	return m_rect.getPosition();
}

/// <summary>
/// updates the bullet depending on the direction 
/// </summary>
/// <param name="dt"></param>
void Bullet::update(double dt)
{
	m_heading = sf::Vector2f(cos(m_rotation * DEG_TO_RAD) * m_speed, sin(m_rotation * DEG_TO_RAD)) * m_speed;
	//updates the position 
	m_position += m_heading;
	//increments the life 
	m_life++;

	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position);
}
/// <summary>
/// resets the bullet to the nest position 
/// </summary>
/// <param name="pos"></param>
void Bullet::resetToNest(sf::Vector2f pos)
{
	m_position = pos;
	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_position);
}
/// <summary>
/// heat seeking missile 
/// passses a position to seek the player
/// </summary>
/// <param name="position"></param>
/// <param name="pos"></param>
/// <param name="rot"></param>
void Bullet::seek(sf::Vector2f position, sf::Vector2f pos, double rot)
{
	m_velocity = position - m_position;
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * 0.5f;
	m_rotation = getNewOrientation(m_rotation, m_velocity);

	m_position += m_velocity;
	

	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position.x , m_position.y);
	m_rect.setRotation(m_rotation);
}

/// <summary>
/// the seek for the predator 
/// passes the player position
/// </summary>
/// <param name="position"></param>
/// <param name="pos"></param>
/// <param name="rot"></param>
void Bullet::predSeek(sf::Vector2f position, sf::Vector2f pos, double rot)
{
	m_velocity = position - m_position;
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * 0.2f;
	m_rotation = getNewOrientation(m_rotation, m_velocity);

	m_position += m_velocity;


	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position.x, m_position.y);
	m_rect.setRotation(m_rotation);
}
/// <summary>
/// returns the bullet X position in Tile format 
/// </summary>
/// <returns></returns>
int Bullet::getTileX()
{
	return m_rect.getPosition().x / 50;
}
/// <summary>
/// returns the bullet Y position in Tile format 
/// </summary>
/// <returns></returns>
int Bullet::getTileY()
{
	return m_rect.getPosition().y / 50;
}
/// <summary>
/// normalize funtion 
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
sf::Vector2f Bullet::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}
/// <summary>
/// length formula 
/// </summary>
/// <param name="vel"></param>
/// <returns></returns>
float Bullet::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

/// <summary>
/// sets the new Orientation of the bullet 
/// uses the velocity and the current orientation to set the new one 
/// </summary>
/// <param name="curOrientation"></param>
/// <param name="velocity"></param>
/// <returns></returns>
float Bullet::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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



void Bullet::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}
