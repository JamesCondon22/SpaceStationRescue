#include "Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player(sf::Font & font, sf::Vector2f pos) :
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
	m_position = pos;
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
/// <summary>
/// sets the rectangle position to the x and y position 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Player::setPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
	m_rect.setPosition(m_position);

}
/// <summary>
/// sets the collision
/// </summary>
void Player::collide()
{
	collision = true;
}
/// <summary>
/// animation for the shield 
/// </summary>
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
}

/// <summary>
/// updates the player 
/// </summary>
/// <param name="dt"></param>
void Player::update(double dt)
{
	handleInput();
	//if the shield is activated
	if (activateShield)
	{
		//starts the timer 
		m_time += m_clockOne.restart().asMilliseconds();
		//checks if the timer is more than 10 seconds 
		if (m_time > 10000)
		{
			//starts the fading of the shield 
			fader -= 0.05;
			m_shieldCircle.setFillColor(sf::Color(0, 0, 255, fader));
			if (fader <= 0)
			{
				//shield is deleted 
				activateShield = false;
			}
		}
	}
	//sets the speed boost to a new max_speed 
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

	m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	

	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_rect.setRotation(m_rotation);

	//creates the bullets and updates 
	for (Bullet * bullet : m_bullets)
	{
		bullet->getPosition();
		bullet->update(dt);
		//erases bullet after a certain time length
		if (bullet->m_life > bullet->max_life)
		{
			m_bullets.erase(m_bullets.begin());
		}
	}
	//updates the shield position 
	m_shieldCircle.setPosition(m_rect.getPosition());
	
	if (activateShield)
	{
		animateShield();
	}
	
}
/// <summary>
/// checks if bullets have collided with nest
/// if there is collision the bullets are deleted and the nest life is updated
/// </summary>
/// <param name="nest"></param>
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
/// <summary>
/// checks if bullets have collided with predators
/// if there is collision the bullets are deleted and the predator is reset
/// </summary>
/// <param name="nest"></param>
void Player::checkPreds(Predator * pred)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->getPosition().x > pred->getPos().x - 25 && m_bullets[i]->getPosition().x < pred->getPos().x + 50
			&& m_bullets[i]->getPosition().y> pred->getPos().y - 25 && m_bullets[i]->getPosition().y < pred->getPos().y + 50)
		{
			m_bullets.erase(m_bullets.begin());
			pred->reset();
		}
	}
}
/// <summary>
/// checks the collision for the sweepers ansd the bullets 
/// erases the bullet upon collision and kills the sweeper bot 
/// </summary>
/// <param name="sweep"></param>
void Player::checkSweepers(Sweeper * sweep)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->getPosition().x > sweep->getPos().x - 25 && m_bullets[i]->getPosition().x < sweep->getPos().x + 50
			&& m_bullets[i]->getPosition().y> sweep->getPos().y - 25 && m_bullets[i]->getPosition().y < sweep->getPos().y + 50)
		{
			m_bullets.erase(m_bullets.begin());
			sweep->kill();
		}
	}
}
/// <summary>
/// sets the lifebar position to the x and y positions passed 
/// adjusts the positions accordingly 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Player::setLifeBarPosition(float x, float y)
{
	lifebar.setPosition(x, y);
	underLie.setPosition(x, y);
	m_lifeLabel.setPosition(lifebar.getPosition().x - 100, lifebar.getPosition().y - 10);
	m_boostLabel.setPosition(m_lifeLabel.getPosition().x - 100, m_lifeLabel.getPosition().y);
}
/// <summary>
/// checks if the shield is activated 
/// </summary>
/// <returns></returns>
bool Player::getActivate()
{
	return activateShield;
}

/// <summary>
/// where all the inputs are handled 
/// </summary>
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
		
		m_bullets.push_back(new Bullet(m_rect.getPosition(), m_rotation, true, false));
	}
}
/// <summary>
/// renders the life bars and the text for the power ups 
/// </summary>
/// <param name="window"></param>
void Player::renderBars(sf::RenderWindow & window)
{
	window.draw(underLie);
	window.draw(lifebar);
	if (!shieldUsed)
	window.draw(m_lifeLabel);
	if(!speedUsed)
	window.draw(m_boostLabel);
}

/// <summary>
/// renders the bullets, rectagle and shield   
/// </summary>
/// <param name="window"></param>
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

/// <summary>
/// adds to the rotation
/// </summary>
void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 0;
	}
}
/// <summary>
/// takes from the rotation
/// </summary>
void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}
/// <summary>
/// increases the players speed 
/// </summary>
void Player::increaseSpeed()
{
	if (m_speed < MAX_SPEED)
	{
		m_speed += 1;
	}
}
/// <summary>
/// decreases the players speed 
/// </summary>
void Player::decreaseSpeed()
{
	if (m_speed > 0)
	{
		m_speed -= 1;
	}
}
/// <summary>
/// returns the player position 
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPos()
{
	return m_rect.getPosition();
}
/// <summary>
/// returns the players velocity 
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getVel()
{
	return m_velocity;
}
/// <summary>
/// returns the player radius 
/// </summary>
/// <returns></returns>
int Player::getRadius()
{
	return m_radius;
}
/// <summary>
/// returns the current rotation of the player
/// </summary>
/// <returns></returns>
double Player::getRotation()
{
	return m_rect.getRotation();
}
/// <summary>
/// updates the lifebar depending on the amount of lives 
/// </summary>
void Player::updateLifeBar()
{
	if (!activateShield)
	{
		--lives;
		if (lives == 9)
		{
			lifebar.setSize(sf::Vector2f(135, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 8)
		{
			lifebar.setSize(sf::Vector2f(120, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 7)
		{
			lifebar.setSize(sf::Vector2f(105, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 6)
		{
			lifebar.setSize(sf::Vector2f(90, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 5)
		{
			lifebar.setSize(sf::Vector2f(75, 10));
			lifebar.setFillColor(sf::Color(255, 140, 0));
		}
		if (lives == 4)
		{
			lifebar.setSize(sf::Vector2f(60, 10));
			lifebar.setFillColor(sf::Color(255, 140, 0));
		}
		if (lives == 3)
		{
			lifebar.setSize(sf::Vector2f(45, 10));
			lifebar.setFillColor(sf::Color::Green);
		}
		if (lives == 2)
		{
			lifebar.setSize(sf::Vector2f(30, 10));
			lifebar.setFillColor(sf::Color::Red);
		}
		if (lives == 1)
		{
			lifebar.setSize(sf::Vector2f(15, 10));
			lifebar.setFillColor(sf::Color::Red);
		}
	}
	
}
/// <summary>
/// returns the players current lives 
/// </summary>
/// <returns></returns>
int Player::getLives()
{
	return lives;
}