#include "Game.h"

/// <summary>
/// @author RP
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()
	: m_window(sf::VideoMode(1250, 1250, 32), "SFML Playground", sf::Style::Default)

{

	m_window.setVerticalSyncEnabled(true);

	if (!m_font.loadFromFile("mytype.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	mouse.setPosition(sf::Vector2i(0, 0), m_window);

	int map[50][50] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,
		0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,1,
		1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};
	//myfile.open("map.txt");

	m_worker = new Workers(100,100,0,0);

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {	
			if (map[i][j] == 0)
			{
				m_tile[j][i] = new Tile(25 * j, 25 * i, m_font, j, i, false);
			}
			if (map[i][j] == 1)
			{
				m_tile[j][i] = new Tile(25 * j, 25 * i, m_font, j, i, true);
			}
		}
	}
}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();

		}
		processGameEvents(event);
	}
}
/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !pressed)
	{
		pressed = true;
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				count++;
				if (m_tile[j][i]->getObstacle())
				{
					myfile << "1,";
				}
				if (!m_tile[j][i]->getObstacle())
				{
					myfile << "0,";
				}
				if (count >= 50)
				{
					myfile << "\n";
					count = 0;
				}
				
			}
		}

	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pressed)
	{
		myfile.close();
	}*/
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Leftpressed = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		Rightpressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Leftpressed)
	{
		Leftpressed = true;
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				if (m_starttile != NULL)
				{
					m_starttile->changeColor();

					m_starttile = m_tile[x][y];
				}
				m_tile[x][y]->setStart();
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !Rightpressed) {
		Rightpressed = true;
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				if (m_goaltile != NULL) {
					//m_goaltile->changeColor();
				}
				m_goaltile = m_tile[x][y];
				//m_tile[x][y]->setGoal();
				breadthFirst(m_goaltile->getXpos(), m_goaltile->getYpos());

			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
       		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				m_tile[x][y]->setObstacle();
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				m_tile[x][y]->removeObstacle();
			}
		}
	}
	


}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;


}








/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {

			m_tile[j][i]->render(m_window);
		}
	}
	m_worker->render(m_window);
	m_window.display();
}



void Game::breadthFirst(int posX, int posY) {


	m_tile[posX][posY]->setVisited(true);
	std::list<Tile*> queue;
	queue.push_back(m_tile[posX][posY]);
	int lowest = 0;

	while (!queue.empty())
	{
		auto gridPos = queue.front()->getGridPos();
		auto costPos = gridPos;
		auto cost = queue.front()->getCost();
		auto rotation = 0.0f;


		if (costPos.first > 0)
		{
			costPos.first--;
			addToQueue(costPos, gridPos, cost, queue);
		}
		if (costPos.first < 49)
		{
			costPos.first++;
			addToQueue(costPos, gridPos, cost, queue);
		}

		if (costPos.second > 0)
		{
			costPos.second--;
			addToQueue(costPos, gridPos, cost, queue);
		}
		if (costPos.second < 49)
		{
			costPos.second++;
			addToQueue(costPos, gridPos, cost, queue);
		}
		queue.pop_front();

	}


}
void Game::addToQueue(std::pair<int, int>& currentPos, std::pair<int, int>& pos, int& cost, std::list<Tile*>& queue) {
	if (!m_tile[currentPos.first][currentPos.second]->getVisited() && !m_tile[currentPos.first][currentPos.second]->getObstacle())
	{
		auto currentTop = (queue.front()->getGridPos());
		//m_tile[currentPos.first][currentPos.second]->setColor(sf::Color(255, 200 - (cost * 4), 215 - (cost * 2), 221 - (cost * 3)));
		m_tile[currentPos.first][currentPos.second]->setVisited(true);
		m_tile[currentPos.first][currentPos.second]->setCost(cost + 1);
		queue.push_back(m_tile[currentPos.first][currentPos.second]);

	}
	currentPos = pos;
}

void Game::checkLowest(int lowest, int current)
{
	if (current < lowest)
	{
		current = lowest;
	}
}
