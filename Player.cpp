#include "Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player() :
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0),
	m_speed(0),
	MAX_SPEED(150)
{
	if (!m_texture.loadFromFile("player.png")) {
		//do something
	}
	
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(30, 50));
	m_position = sf::Vector2f(1250, 1250);
	m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);
	m_rect.setPosition(m_position);

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	lifebar.setOutlineColor(sf::Color::Black);
	lifebar.setSize(sf::Vector2f(150, 10));
	lifebar.setOutlineThickness(2);
	lifebar.setFillColor(sf::Color::Green);

	underLie.setOutlineColor(sf::Color::Black);
	underLie.setSize(sf::Vector2f(150, 10));
	underLie.setOutlineThickness(2);
	underLie.setFillColor(sf::Color(0,0,0,40));
	//lifebar.setPosition(m_position);
}


Player::~Player()
{
}

void Player::setPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
	m_rect.setPosition(m_position);

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
		bullet->getPosition();
		bullet->update(dt);

		if (bullet->m_life > bullet->max_life)
		{
			m_bullets.erase(m_bullets.begin());
		}
	}
	m_surroundingCircle.setPosition(m_rect.getPosition());
}

void Player::checkNests(AlienNest * nest)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->getPosition().x > nest->getPos().x&& m_bullets[i]->getPosition().x < nest->getPos().x + 100
		&& m_bullets[i]->getPosition().y> nest->getPos().y&& m_bullets[i]->getPosition().y < nest->getPos().y + 100)
		{
			m_bullets.erase(m_bullets.begin());
			nest->killNest();
		}
	}
}
void Player::setLifeBarPosition(float x, float y)
{
	lifebar.setPosition(x, y);
	underLie.setPosition(x, y);
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
		sf::Vector2f newPos = m_rect.getPosition();
		
		m_bullets.push_back(new Bullet(m_rect.getPosition(), m_rect.getRotation(), true));
	}
}

void Player::render(sf::RenderWindow & window)
{
	//window.setView(follow);
	window.draw(m_surroundingCircle);
	for (Bullet * bullet : m_bullets)
	{
		if (bullet)
		{
			bullet->render(window);
		}
	}
	window.draw(m_rect);
	window.draw(underLie);
	window.draw(lifebar);
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

int Player::getRadius()
{
	return m_radius;
}

double Player::getRotation()
{
	return m_rect.getRotation();
}

void Player::updateLifeBar()
{
	lives--;
	if (lives == 2)
	{
		lifebar.setSize(sf::Vector2f(100, 10));
		lifebar.setFillColor(sf::Color(255, 140, 0));
	}
	if (lives == 1)
	{
		lifebar.setSize(sf::Vector2f(50, 10));
		lifebar.setFillColor(sf::Color::Red);
	}
}