#pragma once
#ifndef PLAYER
#define PLAYER
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "AlienNest.h"
#include <iostream>


class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void checkNests(AlienNest * nest);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	void increaseRotation();
	void decreaseRotation();
	void increaseSpeed();
	void decreaseSpeed();
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void setLifeBarPosition(float x, float y);
	void updateLifeBar();
	void collide();
	double getRotation();
	void handleInput();
	int getRadius();
	std::vector<Bullet *> m_bullets;
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double m_rotation;
	double m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
	bool collision = false;
	sf::View follow;



	int m_bulletCount = 0;
	int m_bulletTime = 30;
	sf::Vector2f currentBulletPosition;
	sf::CircleShape m_surroundingCircle;
	int m_radius = 20;
	int lives = 3;
	sf::RectangleShape lifebar;
	sf::RectangleShape underLie;
};

#endif