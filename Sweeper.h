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
	Sweeper(sf::Texture texture, sf::Vector2f position);
	~Sweeper();
	void update(double dt, sf::Vector2f playerPosition, int rad, sf::Vector2f workerPos);
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
	void changeDirection();
	sf::Vector2f getPos();
	void collisionPlayer(sf::Vector2f & playerPosition);
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;

	int getTileX();
	int getTileY();
	void KinematicFlee(sf::Vector2f enemyPosition);
	float getNewRotation(float currentRotation, sf::Vector2f velocity);

	void radiusCollisionPlayer(sf::Vector2f position, int rad);
	void distance(int distance, sf::Vector2f position);


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

	//collisionDetection
	bool m_flee;
	

	sf::Text m_label;
	sf::Font m_font;

	sf::Vector2f m_heading;
	int m_speed;
	int size;
	bool collected;

	sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	float m_random;

	//Attack/flee range
	bool m_wander;
	sf::CircleShape m_surroundingCircle;
	bool wallcollide;
	bool m_wanderCollide;
};

#endif // !SWEEPER