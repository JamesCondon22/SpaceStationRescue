#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum Obstacles
{
	Goal,
	Start,
	Path,
	Obstacle,
	Blank
};
class Tile
{
public:
	Tile(int x, int y, sf::Texture & texture, int X, int Y, bool isObs);
	~Tile();
	void render(sf::RenderWindow &window);
	void setVisited(bool visit);
	bool getVisited() { return available; }
	void setPos(int x, int y);
	void changeColor();
	void setGoal();
	void setRotation(double rot);
	void setPath();
	Obstacles getState();
	sf::Vector2f getPosition();
	int getCost() { return m_cost; }
	void setStart();
	bool getObstacle() { return isObstacle; }
	std::pair<int, int> getGridPos() { return m_gridPos; }
	void setColor(sf::Color col);
	void setObstacle();
	void setCurrentState(Obstacles obs);
	void setCost(int num);
	int getXpos();
	int getYpos();
	sf::Vector2f getCircleVec();

	bool available = false;
	int posX;
	int posY;
	int weight = 0;
	std::vector<int> costs;
	std::pair<int, int>  m_previous;
	void setPrevious(std::pair<int, int>  tile);

	bool containsWorker = false;
	bool containsNest = false;
	bool containsSweeper = false;


private:
	sf::RectangleShape m_rect;
	sf::Vector2f m_position;
	sf::Text m_label;
	sf::RectangleShape m_line;
	bool m_selected = false;
	bool isObstacle;
	Obstacles m_current;
	int m_cost;
	std::pair<int, int> m_gridPos;
	sf::Vector2f vectors[9];
	double m_rotation;
	sf::CircleShape circle;
	sf::RectangleShape line;
};
