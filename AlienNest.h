#pragma once
#ifndef ALIENNEST
#define ALIENNEST
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>
class AlienNest
{
public:
	AlienNest(sf::Texture & texture, sf::Vector2f pos);
	~AlienNest();
	void update(double dt, sf::Vector2f position, int rad, double rot);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void circleCollision(sf::Vector2f position, int rad);
	bool bulletPlayerCollision(sf::Vector2f position, int rad);
	void killNest();
	int getLives();
	bool getHit();
	//bool circleCollision();
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int size;
	sf::RectangleShape m_rect;
	sf::CircleShape m_surroundingCircle;

	//bool alive = false;
	int shotsTaken = 0;
	int lives = 4;
	int m_radius = 150;
	double m_time = 0;
	sf::Clock m_clock;
	int m_bulletCount = 0;
	int m_bulletTime = 30;
	sf::Vector2f currentBulletPosition;

	Bullet * m_bullet;
	bool shoot = false;
	bool alive = true;
	bool hit = false;

	sf::RectangleShape lifebar;
	sf::RectangleShape underLie;
};

#endif