#pragma once
#ifndef WORKER
#define WORKER
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <math.h>

class Worker
{
public:
	Worker(sf::Texture & texture, sf::Vector2f pos);
	~Worker();
	void update(double dt, sf::Vector2f playerPosition);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void collisionPlayer(sf::Vector2f & playerPosition);
	void wander(double dt);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
	int m_speed;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
	double static const DEG_TO_RAD;
	bool collected = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	int m_random;


};

#endif