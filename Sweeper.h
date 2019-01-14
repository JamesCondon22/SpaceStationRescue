#pragma once
#ifndef SWEEPER
#define SWEEPER




#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>


class Sweeper
{
public:
	Sweeper();
	~Sweeper();
	void update(double dt, sf::Vector2f playerPosition);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	//sf::Vector2f collisionAvoidance(std::vector<Enemy*> enemy);
	int getId();
	float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
	sf::Vector2f normalise();
	float length(sf::Vector2f vel);
	void seek();
	void checkBorders();
	void setPosition(float x, float y);
	void wander(double dt);
	sf::Vector2f getPos();
	void collisionPlayer(sf::Vector2f & playerPosition);
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	void KinematicFlee(sf::Vector2f enemyPosition);


private:
	int id = 1;
	float m_maxSpeed;
	float m_radius;
	float m_threshold;
	int m_behaviour;
	float m_orientation;
	float m_velocityF;
	sf::Vector2f m_direction;
	float m_distance;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	//Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float m_maxRotation;
	bool m_collected;

	sf::Text m_label;
	sf::Font m_font;

	sf::Vector2f m_heading;
	int m_speed;
	int size;
	bool collected = false;

	sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	int m_random;

};

#endif // !SWEEPER