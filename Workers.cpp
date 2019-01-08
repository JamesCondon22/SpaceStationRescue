#include "Workers.h"



Workers::Workers(int x, int y, int vx, int vy):
	m_position(x,y),
	m_velocity(vx, vy)
{
	if (!m_texture.loadFromFile("images/worker.png"))
	{
		std::cout << "worker png not loaded" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.2, 0.2);
}

void Workers::update()
{

}

void Workers::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

