#include "Bullet.h"


Bullet::Bullet(sf::Vector2f pos, float rotation) :
	m_rotation(rotation),
	m_position(pos)
{
	m_speed = 2;
	m_life = 0;
	m_texture.loadFromFile("bullet.png");
	m_rect.setSize(sf::Vector2f(10, 10));
	m_rect.setTexture(&m_texture);

	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);


}


Bullet::~Bullet()
{
}

void Bullet::update(double dt)
{
	m_heading = sf::Vector2f(cos(m_rotation * DEG_TO_RAD) * m_speed, sin(m_rotation * DEG_TO_RAD)) * m_speed;

	m_position += m_heading;

	m_life++;


	m_rect.setPosition(m_position);
}

void Bullet::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}
