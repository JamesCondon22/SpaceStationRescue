#include "Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player() :
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0),
	m_speed(0),
	MAX_SPEED(100)
{
	if (!m_texture.loadFromFile("player.png")) {
		//do something
	}
	
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(30, 50));
	m_position = sf::Vector2f(1250, 1250);
	m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);
	m_rect.setPosition(m_position);

}


Player::~Player()
{
}

void Player::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);

}

void Player::collide()
{
	collision = true;
}

void Player::update(double dt)
{
	handleInput();

	m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_rect.setRotation(m_rotation);

	for (Bullet * bullet : m_bullets)
	{
		bullet->update(dt);

		if (bullet->m_life > bullet->max_life)
		{
			m_bullets.erase(m_bullets.begin());
		}
	}


	//follow.setCenter(m_position.x, m_position.y);
}

void Player::handleInput()
{

	//key presses 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}

	m_bulletCount++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_bulletCount > m_bulletTime)
	{
		m_bulletCount = 0;
		m_bullets.push_back(new Bullet(m_rect.getPosition(), m_rect.getRotation()));
	}
}

void Player::render(sf::RenderWindow & window)
{
	//window.setView(follow);

	for (Bullet * bullet : m_bullets)
	{
		if (bullet)
		{
			bullet->render(window);
		}
	}
	window.draw(m_rect);
}

void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Player::increaseSpeed()
{
	if (m_speed < MAX_SPEED)
	{
		m_speed += 1;
	}
}

void Player::decreaseSpeed()
{
	if (m_speed > 0)
	{
		m_speed -= 1;
	}
}

sf::Vector2f Player::getPos()
{
	return m_rect.getPosition();
}

sf::Vector2f Player::getVel()
{
	return m_velocity;
}