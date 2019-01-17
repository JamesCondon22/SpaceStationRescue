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
	Player(sf::Font & font);
	~Player();
	void update(double dt);
	void checkNests(AlienNest * nest);
	void render(sf::RenderWindow & window);
	void renderBars(sf::RenderWindow & window);
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
	void animateShield();
	bool getActivate();
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
	sf::Clock m_clockOne;
	sf::Clock m_clockTwo;
	double m_time;
	double m_timeTwo;

	int m_bulletCount = 0;
	int m_bulletTime = 30;
	sf::Vector2f currentBulletPosition;
	sf::CircleShape m_surroundingCircle;
	sf::CircleShape m_shieldCircle;
	int m_radius = 20;
	double shieldRadius = 30;
	int lives = 4;
	sf::RectangleShape lifebar;
	sf::RectangleShape underLie;
	bool movingOut = false;
	bool movingIn = true;
	bool activateShield = false;
	bool speedBoost = false;
	bool speedUsed = false;
	bool shieldUsed = false;
	double fader = 60;
	//text and labels 
	sf::Text m_lifeLabel;
	sf::Text m_boostLabel;
};

#endif