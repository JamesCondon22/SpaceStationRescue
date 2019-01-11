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
	void update(double dt, sf::Vector2f playerPosition);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void collisionPlayer(sf::Vector2f & playerPosition);
	void wander();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int m_speed;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
	bool collected = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif