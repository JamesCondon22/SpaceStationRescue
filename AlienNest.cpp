#include "AlienNest.h"

/// <summary>
/// 
/// </summary>
/// <param name="texture"></param>
/// <param name="pos"></param>
AlienNest::AlienNest(sf::Texture & texture, sf::Vector2f pos) :
	m_position(0, 0),
	size(100)
{
	

	m_rect.setOrigin(m_position.x + 150 / 2, m_position.y + 150 / 2);
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(150, 150));
	m_position = pos;
	m_rect.setPosition(m_position);
	
	m_bullet = new Bullet(m_position, 0, false);

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0,0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position.x, m_position.y);
	m_surroundingCircle.setFillColor(sf::Color(0,0,0,40));

	lifebar.setOutlineColor(sf::Color::Black);
	lifebar.setSize(sf::Vector2f(100, 10));
	lifebar.setOutlineThickness(2);
	lifebar.setFillColor(sf::Color::Green);

	underLie.setOutlineColor(sf::Color::Black);
	underLie.setSize(sf::Vector2f(100, 10));
	underLie.setOutlineThickness(2);
	underLie.setFillColor(sf::Color(255, 255, 255, 60));
}


AlienNest::~AlienNest()
{
}
/// <summary>
/// sets the nest position to the x and y values
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void AlienNest::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);

}

Bullet * AlienNest::getBulletPos()
{
	return m_bullet;
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="position"></param>
/// <param name="rad"></param>
/// <param name="rot"></param>
void AlienNest::update(double dt, sf::Vector2f position, int rad, double rot)
{
	if (alive)
	{
		circleCollision(position, rad);
		bulletPlayerCollision(position, rad);
	}
	
	if (shoot)
	{
		m_bullet->seek(position, m_position, rot);
		m_time += m_clock.restart().asMilliseconds();
		if (m_time > 5000)
		{
			shoot = false;
			m_bullet->resetToNest(m_rect.getPosition());
			m_time = 0;
		}
		if (hit)
		{
			hit = false;
			shoot = false;
			m_bullet->resetToNest(m_rect.getPosition());
			m_time = 0;
		}
	
	}
	else
	{
		m_clock.restart() = sf::Time::Zero;
	}

	if (lives <= 0)
	{
		alive = false;
	}

	underLie.setPosition(m_position.x - 50, m_position.y - 100);
	lifebar.setPosition(m_position.x - 50, m_position.y - 100);
}
/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
/// <returns></returns>
bool AlienNest::bulletPlayerCollision(sf::Vector2f position, int rad)
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

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int AlienNest::getLives()
{
	return lives;
}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="rad"></param>
void AlienNest::circleCollision(sf::Vector2f position, int rad)
{
	int x1 = position.x;
	int y1 = position.y;
	int x2 = m_position.x;
	int y2 = m_position.y;
	
	int radius1 = m_radius;
	int radius2 = rad;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2))
	{
		shoot = true;
	}
}
/// <summary>
/// decrements the nests lives 
/// changes the lifebar size and color
/// </summary>
void AlienNest::killNest()
{
	--lives;
	if (lives == 3)
	{
		lifebar.setSize(sf::Vector2f(75, 10));
		lifebar.setFillColor(sf::Color::Green);
	}
	if (lives == 2)
	{
		lifebar.setSize(sf::Vector2f(50, 10));
		lifebar.setFillColor(sf::Color(255, 140, 0));
	}
	if (lives == 1)
	{
		lifebar.setSize(sf::Vector2f(25, 10));
		lifebar.setFillColor(sf::Color::Red);
	}
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool AlienNest::getShoot()
{
	return shoot;
}

/// <summary>
/// 
/// </summary>
void AlienNest::setShoot()
{
	shoot = false;
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void AlienNest::render(sf::RenderWindow & window)
{
	if (alive)
	{
		window.draw(m_surroundingCircle);
		window.draw(m_rect);
		window.draw(underLie);
		window.draw(lifebar);
	}
	
	if (shoot)
	{
		m_bullet->render(window);
	}
	
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Vector2f AlienNest::getPos()
{
	return m_rect.getPosition();
}





