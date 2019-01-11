#pragma once
#ifndef GAME
#define GAME
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Tile.h"
#include "Workers.h"
#include "Player.h"
#include "AlienNest.h"
#include "Worker.h"
//#include "SweeperBots.h"

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
	void generateNests();
	void generateWorkers();
	void createMap();

	void collision(int x, int y);
	// main window
	sf::RenderWindow m_window;
	//std::vector<Tile*> m_tiles;
	Tile *m_tile[50][50];
	Tile *m_starttile;
	Tile *m_goaltile;
	Workers *m_worker;
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
	//The two views that wil make up the render window
	sf::View gameView;
	sf::View miniMapView;
	sf::Sprite miniMapSprite;
	sf::Texture miniMapTexture;

	Player * m_player;
	std::vector<Worker*> m_workers;
	std::vector<AlienNest*> m_alienNests;
	//SweeperBots bot;

	int lastX = 25;
	int lastY = 25;
	bool start = false;
	bool colliding = false;
	sf::Vector2f playerPosition;
	sf::Texture m_tileTexture;
	sf::Texture nestTexture;
	sf::Texture workerTexture;
	sf::RectangleShape miniMapRect;
};

#endif