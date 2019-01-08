#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

class Workers
{
public:
	Workers(int x, int y, int speed);
	void update();
	void render(sf::RenderWindow &window);
	void wander();


private :
	sf::Vector2f m_position;
	const int m_speed;
	sf::Vector2f m_heading;
	float m_rotation;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

