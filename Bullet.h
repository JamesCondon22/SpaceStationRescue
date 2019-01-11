#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
public:
	Bullet(sf::Vector2f pos, float rotation);
	~Bullet();
	int getTileX();
	int getTileY();
	//void killBullet();
	int max_life = 200;

	float m_life;

	sf::Vector2f getPosition();
	void update(double dt);
	void render(sf::RenderWindow & window);

private:
	float m_rotation;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	float m_speed;

	sf::Vector2f m_heading;
	double const DEG_TO_RAD = 3.14 / 180.0f;

	sf::RectangleShape m_rect;

	//bool alive = false;
};

