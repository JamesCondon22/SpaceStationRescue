#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Predator
{
public:
	Predator(sf::Texture & texture, sf::Vector2f pos);
	~Predator();
	void update(sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	void collisionPlayer(sf::Vector2f & playerPosition);
	void wander(double dt);
	void changeDirection();
	int getTileX();
	int getTileY();
	sf::Vector2f normalize(sf::Vector2f vec);
	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);
	bool circleCollision(sf::Vector2f position, int rad);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
	int m_speed;
	int size;
	sf::RectangleShape m_rect;
	int m_rotation;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	bool collected = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Clock m_clock;
	int timer;
	int m_timeCheck;
	int m_random;

	sf::CircleShape m_surroundingCircle;
};
