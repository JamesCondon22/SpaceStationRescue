#include "Tile.h"



Tile::Tile(int x, int y, sf::Texture & texture, int dx, int dy, bool isObs) :
	m_position(x, y),
	posX(dx),
	posY(dy),
	m_gridPos(dx, dy),
	m_cost(0),
	isObstacle(isObs),
	m_current(Obstacles::Blank)

{
	
	if (isObs)
	{
		m_current = (Obstacles::Obstacle);
	}
	m_rect.setTexture(&texture);
	m_rect.setSize(sf::Vector2f(50.0, 50.0));
	m_rect.setPosition(m_position);
	
	
	circle.setRadius(5);
	circle.setPosition(0, 0);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(m_position.x + 25, m_position.y + 25);
	circle.setFillColor(sf::Color(0, 0, 0, 40));

	line.setSize(sf::Vector2f(2, 23));
	line.setPosition(m_position.x + 23, m_position.y + 23);
}


Tile::~Tile()
{
}

sf::Vector2f Tile::getCircleVec()
{
	return circle.getPosition();
}
void Tile::setCurrentState(Obstacles obs)
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = obs;
	}
}

void Tile::changeColor()
{

}

void Tile::setObstacle()
{
	isObstacle = true;
	m_current = Obstacles::Obstacle;
}

Obstacles Tile::getState()
{
	return m_current;
}

void Tile::render(sf::RenderWindow & window)
{
	//if (m_current == Obstacles::Start)
	//{
	//	m_rect.setFillColor(sf::Color::Green);
	//}
	//if (m_current == Obstacles::Goal)
	//{
	//	m_rect.setFillColor(sf::Color::Red);
	//}
	//if (m_current == Obstacles::Path)
	//{
	//	m_rect.setFillColor(sf::Color::Red);
	//}
	if (m_current == Obstacles::Obstacle)
	{
		m_rect.setFillColor(sf::Color::Black);
	}
	
	if (m_current == Obstacles::Blank)
	{
		m_rect.setFillColor(sf::Color::White);
	}
	
	window.draw(m_rect);
	if (m_current == Obstacles::Path)
	{
		m_rect.setFillColor(sf::Color::Yellow);
		//window.draw(line);
	}
	window.draw(circle);
	window.draw(m_label);

}

void Tile::setGoal()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Goal;
	}
}

void Tile::setStart()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Start;
	}
}

void Tile::setPath()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Path;
	}
}

void Tile::setCost(int num)
{
	m_cost = num;
	m_label.setString(std::to_string(m_cost));
}
sf::Vector2f Tile::getPosition()
{
	return m_position;
}
int Tile::getXpos() {
	return posX;
}

int Tile::getYpos() {
	return posY;
}

void Tile::setVisited(bool visit) {
	available = visit;
}

void Tile::setPos(int x, int y) {
	m_gridPos.first = x;
	m_gridPos.second = y;
}

void Tile::setColor(sf::Color col)
{
	m_rect.setFillColor(sf::Color(col));
}

void Tile::setPrevious(std::pair<int, int> tile)
{
	m_previous = tile;
}

void Tile::setRotation(double rot)
{
	line.setRotation(rot);
}


