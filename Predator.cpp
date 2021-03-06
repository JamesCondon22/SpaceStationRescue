#include "Predator.h"

double const Predator::DEG_TO_RAD = 3.14 / 180.0f;
double const Predator::RAD_TO_DEG = 180.0f / 3.14;

Predator::Predator(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100),
	m_speed(10),
	m_bulletRotation(0)

{

	

	m_rect.setSize(sf::Vector2f(50, 50));
	m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);
	m_rect.setTexture(&texture);
	
	m_position = sf::Vector2f(pos.x, pos.y);
	spawningPosition = m_position;
	m_rect.setPosition(m_position.x, m_position.y);

	m_bullet = new Bullet(m_position, 0, false, true);
	m_surroundingCircle.setRadius(5);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

}


Predator::~Predator()
{
}

void Predator::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="position"></param>
/// <param name="playPos"></param>
void Predator::update(double dt, sf::Vector2f position, sf::Vector2f playPos)
{
	
	m_velocity = position - m_position;
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * 0.3f;
	m_rotation = getNewOrientation(m_rotation, m_velocity);


	if (circleCollision(playPos, 100) && !shoot)
	{
		m_bullet->resetToNest(m_rect.getPosition());
		shoot = true;	
	}

	if (shoot)
	{
		m_bullet->predSeek(playPos, m_position, m_rotation);
		m_time += m_clock.restart().asMilliseconds();
		if (m_time > 5000)
		{
			shoot = false;
			
			m_time = 0;
		}
		if (hit)
		{
			hit = false;
			m_bullet->resetToNest(m_rect.getPosition());
			shoot = false;
		}
	}
	else
	{
		m_clock.restart() = sf::Time::Zero;
		
	}

	m_position += m_velocity;
	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position.x, m_position.y);
	m_rect.setRotation(m_rotation);
	
}
/// <summary>
/// 
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
sf::Vector2f Predator::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}
/// <summary>
/// 
/// </summary>
/// <param name="curOrientation"></param>
/// <param name="velocity"></param>
/// <returns></returns>
float Predator::getNewOrientation(float curOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-velocity.x, velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="vel"></param>
/// <returns></returns>
float Predator::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}
/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="distance"></param>
/// <returns></returns>
bool Predator::circleCollision(sf::Vector2f position, int distance)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_position.x;
	int y2 = m_position.y;


	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < distance)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
/// <returns></returns>
bool Predator::bulletPlayerCollision(sf::Vector2f position, int rad)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_bullet->getPosition().x;
	int y2 = m_bullet->getPosition().y;

	int radius1 = rad;
	int radius2 = 10;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2))
	{
		hit = true;
		return true;
	}
	else
	{
		return false;
	}
}


void Predator::wander(double dt)
{


}

void Predator::render(sf::RenderWindow & window)
{
	m_bullet->render(window);
	window.draw(m_rect);
	//window.draw(m_surroundingCircle);
}

sf::Vector2f Predator::getPos()
{
	return m_rect.getPosition();
}



int Predator::getTileX()
{
	return m_sprite.getPosition().x / 50;
}

int Predator::getTileY()
{
	return m_sprite.getPosition().y / 50;
}




