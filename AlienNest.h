#pragma once
#ifndef ALIENNEST
#define ALIENNEST
#include <SFML/Graphics.hpp>
#include <iostream>
class AlienNest
{
public:
	AlienNest(sf::Texture & texture, sf::Vector2f pos);
	~AlienNest();
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int size;
	sf::RectangleShape m_rect;
	sf::CircleShape m_surroundingCircle;

	bool alive = false;
	int shotsTaken = 0;
	int maxLife = 4;
};

#endif