#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"


class Predator
{
public:
	Predator(sf::Texture & texture, sf::Vector2f pos);
	~Predator();
	void update(double dt, sf::Vector2f position, sf::Vector2f playPos);
	void render(sf::RenderWindow & window);
	bool bulletPlayerCollision(sf::Vector2f position, int rad);
	//void killPred(sf::Vector2f position);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void wander(double dt);
	int getTileX();
	int getTileY();
	sf::Vector2f normalize(sf::Vector2f vec);
	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);
	bool circleCollision(sf::Vector2f position, int distance);
	void reset();
	Bullet * m_bullet;
private:
	sf::Vector2f m_position;
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
	sf::Vector2f m_bulletTraj;
	int m_speed;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;
	int m_bulletRotation;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	bool collected = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	int m_random;

	sf::CircleShape m_surroundingCircle;
	int m_bulletCount = 0;
	int m_bulletTime = 300;
	sf::Vector2f spawningPosition;
	bool shoot = false;
	sf::Clock m_clock;
	double m_time = 0;
	bool hit = false;

};
