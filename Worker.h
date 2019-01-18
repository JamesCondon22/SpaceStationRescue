#pragma once
#ifndef WORKER
#define WORKER
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <math.h>
#include "Tile.h"

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
	void changeDirection();
	int getTileX();
	int getTileY();
	bool getCollision();
	bool getCollected();
	void collisionSweeper(sf::Vector2f & SweeperPosition);
	int getRadius();
	void distance(int rad, sf::Vector2f position);
	bool collected = false;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
	int m_speed;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
	double static const DEG_TO_RAD;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	int m_random;
	int m_count = 0;

	bool increment = false;

	//radius range
	sf::CircleShape m_surroundingCircle;
	float m_radius;
	
};

#endif