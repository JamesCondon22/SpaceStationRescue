#pragma once
#ifndef SWEEPERBOTS
#define SWEEPERBOTS
#include <SFML/Graphics.hpp>
#include <iostream>
class SweeperBots
{
public:
	SweeperBots();
	SweeperBots(sf::Texture & texture, sf::Vector2f pos);
	~SweeperBots();
	void update(double dt, sf::Vector2f playerPosition);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void collisionPlayer(sf::Vector2f & playerPosition);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
	bool collected = false;
};

#endif