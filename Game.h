#pragma once
#ifndef GAME
#define GAME
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Tile.h"
#include <list>

class Game
{
public:
	Game();
	void run();
protected:
	int countB = 0;
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	void breadthFirst(int posx, int posy);
	void addToQueue(std::pair<int, int>& currentPos, std::pair<int, int>& pos, int& cost, std::list<Tile*>& queue);
	void checkLowest(int lowest, int current);
	void createMap();
	// main window
	sf::RenderWindow m_window;
	//std::vector<Tile*> m_tiles;
	Tile *m_tile[50][50];
	Tile *m_starttile;
	Tile *m_goaltile;
	sf::Mouse mouse;
	sf::Font m_font;
	bool Leftpressed = false;
	bool Rightpressed = false;
	//Tile dijkstraGrid;
	int startX;
	int startY;
	bool startCalc = false;
	std::vector<Tile> pq;
	std::vector<int> m_costs;
	std::ofstream myfile;
	bool pressed = false;
	int count = 0;
};

#endif