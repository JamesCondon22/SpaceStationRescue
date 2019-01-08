#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

class Workers
{
public:
	Workers(int x, int y, int vx, int vy);
	void update();
	void render(sf::RenderWindow &window);


private :
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

