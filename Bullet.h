#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
public:
	Bullet(sf::Vector2f pos, float rotation, bool isPlayer, bool isPred);
	~Bullet();
	int getTileX();
	int getTileY();
	void seek(sf::Vector2f position, sf::Vector2f pos, double rot);
	void predSeek(sf::Vector2f position, sf::Vector2f pos, double rot);
	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	int max_life = 200;
	float m_life;

	sf::Vector2f normalize(sf::Vector2f vec);
	sf::Vector2f getPosition();
	void resetToNest(sf::Vector2f pos);
	void update(double dt);
	void render(sf::RenderWindow & window);

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
private:
	sf::Vector2f m_heading;
	sf::Vector2f m_position;
	sf::Texture m_texture;

	float m_speed;
	double m_rotation;

	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::CircleShape m_surroundingCircle;
	//bool alive = false;
};

