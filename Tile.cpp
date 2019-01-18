#include "Tile.h"


/// <summary>
/// initialises the Tile 
/// passes grid positions and vector positions of the tile 
/// checks if the tile is an obstacle 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="texture"></param>
/// <param name="dx"></param>
/// <param name="dy"></param>
/// <param name="isObs"></param>
Tile::Tile(int x, int y, sf::Texture & texture, int dx, int dy, bool isObs) :
	m_position(x, y),
	posX(dx),
	posY(dy),
	m_gridPos(dx, dy),
	m_cost(0),
	isObstacle(isObs),
	m_current(Obstacles::Blank)

{
	//checks if the tile is an obstacle 
	if (isObs)
	{
		m_current = (Obstacles::Obstacle);
	}
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(50.0, 50.0));
	m_rect.setPosition(m_position);
	
	if (!isObs)
	{
		circle.setRadius(5);
		circle.setPosition(0, 0);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(m_position.x + 25, m_position.y + 25);
		circle.setFillColor(sf::Color(0, 0, 0, 40));
	}
	

	line.setSize(sf::Vector2f(2, 23));
	line.setPosition(m_position.x + 23, m_position.y + 23);
}


Tile::~Tile()
{
}
/// <summary>
/// gets the circle centre position 
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getCircleVec()
{
	return circle.getPosition();
}
/// <summary>
/// sets the current state if the obstacle
/// </summary>
/// <param name="obs"></param>
void Tile::setCurrentState(Obstacles obs)
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = obs;
	}
}

/// <summary>
/// sets the obstacle 
/// </summary>
void Tile::setObstacle()
{
	isObstacle = true;
	m_current = Obstacles::Obstacle;
}
/// <summary>
/// gets the current state 
/// </summary>
/// <returns></returns>
Obstacles Tile::getState()
{
	return m_current;
}
/// <summary>
/// renders all the tiles accordingly 
/// </summary>
/// <param name="window"></param>
void Tile::render(sf::RenderWindow & window)
{
	
	if (m_current == Obstacles::Obstacle)
	{
		m_rect.setFillColor(sf::Color::Black);
	}
	
	if (m_current == Obstacles::Blank)
	{
		m_rect.setFillColor(sf::Color::White);
	}
	if (m_current == Obstacles::Path)
	{
		m_rect.setFillColor(sf::Color::Yellow);
		window.draw(circle);
	}
	if (m_current == Obstacles::Start)
	{
		m_rect.setFillColor(sf::Color::Green);
	}
	if (m_current == Obstacles::Goal)
	{
		m_rect.setFillColor(sf::Color::Red);
	}

	window.draw(m_rect);
	window.draw(m_label);

}
/// <summary>
/// sets the goal 
/// </summary>
void Tile::setGoal()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Goal;
	}
}
/// <summary>
/// sets the start 
/// </summary>
void Tile::setStart()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Start;
	}
}
/// <summary>
/// sets the current to path 
/// </summary>
void Tile::setPath()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Path;
	}
}
/// <summary>
/// sets the cost of the tile 
/// </summary>
/// <param name="num"></param>
void Tile::setCost(int num)
{
	m_cost = num;
	m_label.setString(std::to_string(m_cost));
}
/// <summary>
/// gets the current vector position of the tile 
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getPosition()
{
	return m_position;
}
/// <summary>
/// gets the tile x position 
/// </summary>
/// <returns></returns>
int Tile::getXpos() {
	return posX;
}
/// <summary>
/// gets the tile y position
/// </summary>
/// <returns></returns>
int Tile::getYpos() {
	return posY;
}
/// <summary>
/// sets the visited to check if that tile is available 
/// </summary>
/// <param name="visit"></param>
void Tile::setVisited(bool visit) {
	available = visit;
}
/// <summary>
/// sets the tile x and y positions to the grid position 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Tile::setPos(int x, int y) {
	m_gridPos.first = x;
	m_gridPos.second = y;
}
/// <summary>
/// sets the color of the tile 
/// </summary>
/// <param name="col"></param>
void Tile::setColor(sf::Color col)
{
	m_rect.setFillColor(sf::Color(col));
}
/// <summary>
/// sets the previous tile 
/// </summary>
/// <param name="tile"></param>
void Tile::setPrevious(std::pair<int, int> tile)
{
	m_previous = tile;
}
/// <summary>
/// sets the vector rotation 
/// </summary>
/// <param name="rot"></param>
void Tile::setRotation(double rot)
{
	line.setRotation(rot);
}


