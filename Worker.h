#pragma once
#ifndef WORKER
#define WORKER
#include <SFML/Graphics.hpp>
#include <iostream>
class Worker
{
public:
	Worker(sf::Texture & texture, sf::Vector2f pos);
	~Worker();
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
};

#endif