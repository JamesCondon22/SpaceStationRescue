#pragma once
#ifndef GAME
#define GAME
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Tile.h"
#include "Player.h"
#include "Predator.h"
#include "AlienNest.h"
#include "Worker.h"
#include "Sweeper.h"


#include <list>

class Game
{
public:
	Game();
	void run();
	sf::Vector2f getPlayerPos();
protected:
	int countB = 0;
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	void breadthFirst(int posx, int posy);
	void addToQueue(std::pair<int, int>& currentPos, std::pair<int, int>& pos, int& cost, std::list<Tile*>& queue, std::pair<int, int>& prevpos);
	void checkLowest(int lowest, int current);
	void generateNests();
	void generateWorkers();
	void generatePredators(AlienNest alien);
	void createMap();
	void reset();
	void iterateQueue(double dt, int i);

	void collision(int x, int y);
	void workerWallCollision();
	void bulletWallCollision();
	void nestbulletWallCollision();
	void bulletNestCollision(AlienNest *nest);
	void checkDirections();
	void getPath(int posX, int posY);
	// main window
	sf::RenderWindow m_window;
	//std::vector<Tile*> m_tiles;
	Tile *m_tile[50][50];
	Tile *containingTile;
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
	//The two views that wil make up the render window
	sf::View gameView;
	sf::View miniMapView;
	sf::Sprite miniMapSprite;
	sf::Texture miniMapTexture;

	Sweeper * m_sweeper;
	Player * m_player;
	//Predator * m_predator;
	std::vector<Worker*> m_workers;
	std::vector<AlienNest*> m_alienNests;
	std::vector<Predator*> m_predators;
	//SweeperBots bot;

	int lastX = 25;
	int lastY = 25;
	bool start = false;
	bool colliding = false;
	sf::Vector2f playerPosition;
	sf::Texture m_tileTexture;
	sf::Texture nestTexture;
	sf::Texture workerTexture;
	sf::Texture m_predTexture;
	sf::RectangleShape miniMapRect;
	sf::RectangleShape m_workerUI;
	sf::Text m_countText;

	bool hitNest = false;
	int m_count = 0;

	int curX;
	int curY;
	int prevX;
	int prevY;

	//std::list<Tile>::iterator m_iter;
	std::list<Tile> queue;
	sf::Clock m_clock;
	double m_time = 0;

	bool predSpawned;
};

#endif