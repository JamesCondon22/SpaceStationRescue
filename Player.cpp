#include "Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player(sf::Font & font) :
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

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));
	
	m_shieldCircle.setRadius(shieldRadius);
	m_shieldCircle.setPosition(0, 0);
	m_shieldCircle.setOrigin(m_shieldCircle.getRadius(), m_shieldCircle.getRadius());
	m_shieldCircle.setPosition(m_position);
	m_shieldCircle.setFillColor(sf::Color(0, 0, 255, 60));


	lifebar.setOutlineColor(sf::Color::Black);
	lifebar.setSize(sf::Vector2f(150, 10));
	lifebar.setOutlineThickness(2);
	lifebar.setFillColor(sf::Color::Green);

	underLie.setOutlineColor(sf::Color::Black);
	underLie.setSize(sf::Vector2f(150, 10));
	underLie.setOutlineThickness(2);
	underLie.setFillColor(sf::Color(255,255,255,60));
	//lifebar.setPosition(m_position);

	m_lifeLabel.setFont(font);
	m_lifeLabel.setCharacterSize(15);
	m_lifeLabel.setOutlineThickness(1);
	m_lifeLabel.setOutlineColor(sf::Color::White);
	m_lifeLabel.setString("SHIELD READY\n    PRESS X");
	m_lifeLabel.setFillColor(sf::Color(0, 0, 0));

	m_boostLabel.setFont(font);
	m_boostLabel.setCharacterSize(15);
	m_boostLabel.setOutlineThickness(1);
	m_boostLabel.setOutlineColor(sf::Color::White);
	m_boostLabel.setString("BOOST READY\n    PRESS Z");
	m_boostLabel.setFillColor(sf::Color(0, 0, 0));
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

void Player::animateShield()
{
	if (shieldRadius < 20)
	{
		movingIn = false;
		movingOut = true;
		shieldRadius = 20;
	}
	if (shieldRadius > 30)
	{
		movingIn = true;
		movingOut = false;
		shieldRadius = 30;
	}
	if (shieldRadius >= 20 && shieldRadius <= 30 && movingIn)
	{
		shieldRadius -= 0.05;
		m_shieldCircle.setRadius(shieldRadius);
	}
	if (shieldRadius >= 20 && shieldRadius <= 30 && movingOut)
	{
		shieldRadius += 0.05;
		m_shieldCircle.setRadius(shieldRadius);
	}
	m_shieldCircle.setOrigin(m_shieldCircle.getRadius(), m_shieldCircle.getRadius());
	//m_shieldCircle.rotate(10);
}
void Player::update(double dt)
{
	handleInput();
	if (activateShield)
	{
		m_time += m_clockOne.restart().asMilliseconds();
		if (m_time > 10000)
		{
			//activateShield = false;
			fader -= 0.05;
			m_shieldCircle.setFillColor(sf::Color(0, 0, 255, fader));
			if (fader <= 0)
			{
				activateShield = false;
			}
		}
	}
	std::cout << m_time << std::endl;
	if (speedBoost)
	{
		MAX_SPEED = 200;
		m_timeTwo += m_clockTwo.restart().asMilliseconds();
		if (m_timeTwo > 15000)
		{
			speedBoost = false;
			MAX_SPEED = 100;
			m_speed = 100;
		}
	}
	std::cout << m_speed << std::endl;

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
	m_shieldCircle.setPosition(m_rect.getPosition());
	
	if (activateShield)
	{
		animateShield();
	}
	
}

void Player::checkNests(AlienNest * nest)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->getPosition().x > nest->getPos().x - 50 && m_bullets[i]->getPosition().x < nest->getPos().x + 100
		&& m_bullets[i]->getPosition().y> nest->getPos().y - 50 && m_bullets[i]->getPosition().y < nest->getPos().y + 100)
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
	m_lifeLabel.setPosition(lifebar.getPosition().x - 100, lifebar.getPosition().y - 10);
	m_boostLabel.setPosition(m_lifeLabel.getPosition().x - 100, m_lifeLabel.getPosition().y);
}

bool Player::getActivate()
{
	return activateShield;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !activateShield)
	{
		activateShield = true;
		shieldUsed = true;
		m_clockOne.restart() = sf::Time::Zero;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !speedBoost)
	{
		speedBoost = true;
		speedUsed = true;
		m_clockTwo.restart() = sf::Time::Zero;
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

void Player::renderBars(sf::RenderWindow & window)
{
	window.draw(underLie);
	window.draw(lifebar);
	if (!shieldUsed)
	window.draw(m_lifeLabel);
	if(!speedUsed)
	window.draw(m_boostLabel);
}


void Player::render(sf::RenderWindow & window)
{
	if (activateShield)
	{
		window.draw(m_shieldCircle);
	}

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
	if (!activateShield)
	{
		--lives;
		if (lives == 3)
		{
			lifebar.setSize(sf::Vector2f(112.5, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 2)
		{
			lifebar.setSize(sf::Vector2f(75, 10));
			lifebar.setFillColor(sf::Color(255, 140, 0));
		}
		if (lives == 1)
		{
			lifebar.setSize(sf::Vector2f(37.5, 10));
			lifebar.setFillColor(sf::Color::Red);
		}
	}
	
}