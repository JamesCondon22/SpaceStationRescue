#include "Bullet.h"

double const Bullet::DEG_TO_RAD = 3.14 / 180.0f;
double const Bullet::RAD_TO_DEG = 180.0f / 3.14;

Bullet::Bullet(sf::Vector2f pos, float rotation, bool isPlayer, bool isPred) :
	m_rotation(rotation),
	m_position(0,0),
	m_velocity(0,0)
{
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
	
	
	
	m_life = 0;
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

sf::Vector2f Bullet::getPosition()
{
	return m_rect.getPosition();
}


void Bullet::update(double dt)
{
	m_heading = sf::Vector2f(cos(m_rotation * DEG_TO_RAD) * m_speed, sin(m_rotation * DEG_TO_RAD)) * m_speed;

	m_position += m_heading;

	m_life++;

	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position);
}

void Bullet::resetToNest(sf::Vector2f pos)
{
	m_position = pos;
	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_position);
}

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

int Bullet::getTileX()
{
	return m_rect.getPosition().x / 50;
}

int Bullet::getTileY()
{
	return m_rect.getPosition().y / 50;
}

sf::Vector2f Bullet::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}

float Bullet::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}


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

void checkCollision(sf::Vector2f pos)
{

}

void Bullet::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	//window.draw(m_surroundingCircle);
}
