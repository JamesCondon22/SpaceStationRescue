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
	//generate AI 
	void generateNests();
	void generateWorkers();
	void generatePredators(AlienNest alien);
	void reset();
	void iterateQueue(double);
	void generateSweepers();
	void scoring();
	void collision(int x, int y);
	void workerWallCollision();
	void sweeperWallCollision();
	void bulletWallCollision();
	void nestbulletWallCollision();

	void predbulletWallCollision();
	void checkDirections();
	void getPath(int posX, int posY);

	// main window
	sf::RenderWindow m_window;

	Tile *m_tile[50][50];
	Tile *containingTile;
	Tile *m_starttile;
	Tile *m_goaltile;

	sf::Mouse mouse;
	sf::Font m_font;
	
	std::vector<Tile> pq;
	std::vector<int> m_costs;
	std::ofstream myfile;
	
	int count = 0;
	//The two views that wil make up the render window
	sf::View gameView;
	sf::View miniMapView;
	sf::Sprite miniMapSprite;
	sf::Texture miniMapTexture;

	
	Player * m_player;
	std::vector<Worker*> m_workers;
	std::vector<AlienNest*> m_alienNests;
	std::vector<Predator*> m_predators;
	std::vector<Sweeper*> m_sweeper;

	int lastX = 25;
	int lastY = 25;
	bool start = false;
	bool colliding = false;
	sf::Vector2f playerPosition;

	sf::Texture m_tileTexture;
	sf::Texture nestTexture;
	sf::Texture workerTexture;
	sf::Texture m_predTexture;
	sf::Texture sweeperTexture;

	sf::RectangleShape miniMapRect;
	sf::RectangleShape m_workerUI;

	sf::Text m_countText;
	sf::Text m_finishtext;

	std::vector<bool>m_score;

	bool hitNest = false;
	int m_count = 0;

	int curX;
	int curY;
	int prevX;
	int prevY;

	std::list<Tile> queue;
	sf::Clock m_clock;
	double m_time = 0;

	bool predSpawned;
	bool m_winner = false;
	bool m_gameover = false;

};

#endif