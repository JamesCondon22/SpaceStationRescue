#include "Workers.h"



Workers::Workers(int x, int y, int speed):
	m_position(x,y),
	m_speed(speed)
{
	if (!m_texture.loadFromFile("images/worker.png"))
	{
		std::cout << "worker png not loaded" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.1, 0.1);
}

void Workers::update()
{
	wander();
}

void Workers::wander()
{
	//random angle assigned
	//rotation set to new angle
	/*m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_rect.setRotation(m_rotation);*/
	//start timer
	//check timer
	//randomize rotation
	//repeat
}

void Workers::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

