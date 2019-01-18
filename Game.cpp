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
	: m_window(sf::VideoMode(1920, 1080, 32), "SFML Playground", sf::Style::Default),
	m_score(false),
	m_count(0)

{
	// All textures loading in
	m_window.setVerticalSyncEnabled(true);
	
	if (!m_font.loadFromFile("images/bernhc.TTF"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	if (!miniMapTexture.loadFromFile("minimap.PNG"))
	{
		std::cout << "problem loading texture" << std::endl;
	}
	if (!m_tileTexture.loadFromFile("groundTile.jpg"))
	{
		std::cout << "problem loading texture" << std::endl;
	}
	if (!nestTexture.loadFromFile("nest.png"))
	{
		std::cout << "problem loading texture" << std::endl;
	}
	if (!workerTexture.loadFromFile("images/worker.png"))
	{
		std::cout << "problem loading texture" << std::endl;
	}

	if (!m_predTexture.loadFromFile("images/predator.png"))
	{
		std::cout << "problem loading texture" << std::endl;
	}
	if (!sweeperTexture.loadFromFile("UFOsweeper.png"))
	{
		std::cout << "problem loading UFO texture" << std::endl;
	}


	miniMapSprite.setTexture(miniMapTexture);
	miniMapSprite.setScale(2, 2);

	mouse.setPosition(sf::Vector2i(0, 0), m_window);
	
	miniMapView.setViewport(sf::FloatRect(0.01f, 0.74f, 0.25f, 0.25f));
	
	gameView.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
	gameView.setSize(1920, 1080);
	gameView.zoom(.7);


	int map[50][50] = {

		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,
		1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};


	srand(time(NULL));

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {	
			if (map[i][j] == 0)
			{
				m_tile[j][i] = new Tile(50 * j, 50 * i, m_tileTexture, j, i, false);
			}
			if (map[i][j] == 1)
			{
				m_tile[j][i] = new Tile(50 * j, 50 * i, m_tileTexture, j, i, true);
			}
		}
	}
	

	miniMapRect.setFillColor(sf::Color::Black);
	miniMapRect.setSize(sf::Vector2f(178, 112));
	
	m_workerUI.setSize(sf::Vector2f(40, 40));
	m_workerUI.setTexture(&workerTexture);
	m_workerUI.setPosition(gameView.getCenter());
	generateNests();
	generateWorkers();

	m_player = new Player(m_font, m_tile[25][25]->getPosition());

	generateSweepers();

	m_countText.setFont(m_font);
	m_countText.setCharacterSize(20);
	m_countText.setOutlineColor(sf::Color::White);
	m_countText.setFillColor(sf::Color::White);
	m_countText.setString(std::to_string(m_count));

	m_finishtext.setFont(m_font);
	m_finishtext.setCharacterSize(40);
	
	m_finishtext.setPosition(sf::Vector2f(200, 200));
	

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

}
/// <summary>
/// resets the tile maze 
/// </summary>
void Game::reset()
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {

			m_tile[j][i]->setCost(0);
			m_tile[j][i]->setVisited(false);
			m_tile[j][i]->setCurrentState(Blank);
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

	//only updates if the player hasnt won or lost 
	if (!m_winner || !m_gameover) {

		playerPosition = sf::Vector2f(m_player->getPos().x + 350, m_player->getPos().y + 200);
		gameView.setCenter(playerPosition);
		scoring();

		for (int i = 0; i < m_alienNests.size(); i++)
		{
			//updates the alien nests 
			m_alienNests[i]->update(dt, m_player->getPos(), m_player->getRadius(), m_player->getRotation());
			m_player->checkNests(m_alienNests[i]);//checks bullet collision with the nests 
			//checks the collision between the bullet and the player 
			if (m_alienNests[i]->bulletPlayerCollision(m_player->getPos(), m_player->getRadius()))
			{
				//updates the lifebar 
				m_player->updateLifeBar();
			}

			if (!predSpawned)
			{
				generatePredators(*m_alienNests[i]);
			}
		}

		m_player->update(dt);
		//sets the current position of the predators 
		int curPredX = round(m_predators[0]->getPos().x / 50);
		int curPredY = round(m_predators[0]->getPos().y / 50);

		//sets the start tile 
		m_starttile = m_tile[curPredX][curPredY];
		m_starttile->setStart();

		//sets the players tile position
		int curX = round(m_player->getPos().x / 50);
		int curY = round(m_player->getPos().y / 50);


		//Updates the sweeper bots for flee, seek and collection
		for (int i = 0; i < m_sweeper.size(); i++)
		{
			m_sweeper[i]->update(dt, m_player->getPos(), m_player->getRadius());
			for (int count = 0; count < m_workers.size(); count++)
			{
				m_sweeper[i]->radiusCollisionWorker(m_workers[count]->getPos(), m_workers[count]->getRadius(), m_workers[count]->m_swept);
				m_player->checkSweepers(m_sweeper[i]);
				if (m_player->score == true)
				{
					m_count += m_player->m_score;
					m_player->score = false;
				}
			}
		}



		//Detection for sweepers on worker end
		for (int i = 0; i < m_workers.size(); i++)
		{
			m_workers[i]->update(dt, m_player->getPos());
			for (int count = 0; count < m_sweeper.size(); count++)
			{
				sf::Vector2f pos = m_sweeper[count]->getPos();
				m_workers[i]->collisionSweeper(pos);
			}
		}

	
		collision(curX, curY);
		//sets the goal tile 
		m_goaltile = m_tile[curX][curY];
		m_goaltile->setGoal();

		//performs the breadth first search passes the goal tile positions
		breadthFirst(m_goaltile->getXpos(), m_goaltile->getYpos());
		//calls the shortest path function
		getPath(m_starttile->getXpos(), m_starttile->getYpos());

		//resets if the player has changed tile 
		if (curX != prevX) {
			reset();
		}
		if (curY != prevY) {
			reset();
		}
		//sets the previous 
		prevX = curX;
		prevY = curY;



		//checks the predator and the bullet 
		m_player->checkPreds(m_predators[0]);
		//calls the player and the bullet collision 
		if (m_predators[0]->bulletPlayerCollision(m_player->getPos(), m_player->getRadius()))
		{
			m_player->updateLifeBar();
			m_player->checkPreds(m_predators[0]);

			if (m_predators[0]->bulletPlayerCollision(m_player->getPos(), m_player->getRadius()))
			{
				m_player->updateLifeBar();
			}

		}

		//collisions with walls 
		workerWallCollision();
		bulletWallCollision();
		sweeperWallCollision();
		predbulletWallCollision();
		nestbulletWallCollision();

		iterateQueue(dt);
		//centres the minimap 
		miniMapView.setCenter(m_player->getPos());

		if (m_count >= 10)
		{
			m_winner = true;
		}
		//checks lose condition
		if (m_player->getLives() <= 0)
		{
			m_gameover = true;
		}
	}
	
}
/// <summary>
/// iterates throuugh the queue and passes a delta time and count 
/// calls the predator updates passing the position of the next tile in the queue 
/// increments the iterator 
/// </summary>
/// <param name="dt"></param>
void Game::iterateQueue(double dt)
{

	for (auto iter = queue.begin(); iter != queue.end();)
	{
		m_predators[0]->update(dt, m_tile[iter->getXpos()][iter->getYpos()]->getCircleVec(), m_player->getPos());
		iter++;
	}
}



/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{

	m_window.clear(sf::Color::Black);
	//renders the gameview 
	m_window.setView(gameView);
	//upodates the UI positions  
	miniMapRect.setPosition(miniMapView.getCenter().x - 320, miniMapView.getCenter().y + 98);
	m_workerUI.setPosition(miniMapView.getCenter().x - 300, miniMapView.getCenter().y - 170);
	m_countText.setPosition(m_workerUI.getPosition().x + 50, m_workerUI.getPosition().y + 5);
	m_player->setLifeBarPosition(m_workerUI.getPosition().x + 450, m_workerUI.getPosition().y + 5);
	//renders the tiles 
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			//only render what tiles are on the gamescreen 
			if (m_tile[j][i]->getPosition().x > playerPosition.x - 800 && m_tile[j][i]->getPosition().x < playerPosition.x
				&& m_tile[j][i]->getPosition().y > playerPosition.y - 500 && m_tile[j][i]->getPosition().y < playerPosition.y)
			{
				m_tile[j][i]->render(m_window);
			}
		}
	}

	for (int i = 0; i < m_alienNests.size(); i++)
	{
		m_alienNests[i]->render(m_window);
	}

	for (int i = 0; i < m_workers.size(); i++)
	{
		m_workers[i]->render(m_window);
	}
	for (int i = 0; i < m_predators.size(); i++)
	{
		m_predators[i]->render(m_window);
	}

	for (int i = 0; i < m_sweeper.size(); i++)
	{
		m_sweeper[i]->render(m_window);
	}

	m_player->render(m_window);
	//renders the UI
	m_window.draw(m_countText);
	m_window.draw(m_workerUI);
	m_player->renderBars(m_window);

	if (m_winner)
	{
		m_window.clear(sf::Color::White);
		m_finishtext.setOutlineColor(sf::Color::Black);
		m_finishtext.setOutlineThickness(3);
		m_finishtext.setFillColor(sf::Color::Red);
		m_finishtext.setString("YOU WIN");
		m_finishtext.setPosition(miniMapView.getCenter().x - 50, miniMapView.getCenter().y - 50);
		m_window.draw(m_finishtext);
	}
	if (m_gameover)
	{
		m_window.clear(sf::Color::Black);
		m_finishtext.setFillColor(sf::Color::White);
		m_finishtext.setString("YOU LOSE");
		m_finishtext.setPosition(miniMapView.getCenter().x - 50, miniMapView.getCenter().y - 50);
		m_window.draw(m_finishtext);
	}
	if (!m_winner)
	{
		m_window.draw(miniMapRect);
		m_window.setView(miniMapView);

		m_window.draw(miniMapSprite);
		m_player->render(m_window);
		for (int i = 0; i < m_alienNests.size(); i++)
		{
			m_alienNests[i]->render(m_window);
		}

		for (int i = 0; i < m_workers.size(); i++)
		{
			m_workers[i]->render(m_window);
		}

		for (int i = 0; i < m_sweeper.size(); i++)
		{
			m_sweeper[i]->render(m_window);
		}

	}
	
	
	m_window.display();
	
}
/// <summary>
/// collsion for the player and the walls 
/// passes the x and y tile positions 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Game::collision(int x, int y)
{
	
	if (m_tile[x][y-1]->getObstacle())
	{
		if (m_player->getPos().y < m_tile[x][y - 1]->getPosition().y + 65)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y - 1]->getPosition().y + 65);
		}
		
	}
	if (m_tile[x][y + 1]->getObstacle())
	{
		if (m_player->getPos().y > m_tile[x][y + 1]->getPosition().y - 30)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y + 1]->getPosition().y - 30);
		}
	}
	
	if (m_tile[x - 1][y]->getObstacle())
	{

		if (m_player->getPos().x < m_tile[x - 1][y]->getPosition().x + 65)
		{
			m_player->setPosition(m_tile[x - 1][y]->getPosition().x + 65, m_player->getPos().y);
		}
	}
	if (m_tile[x + 1][y]->getObstacle())
	{
	
		if (m_player->getPos().x > m_tile[x + 1][y]->getPosition().x - 30)
		{
			m_player->setPosition(m_tile[x + 1][y]->getPosition().x - 30, m_player->getPos().y);
		}
	}
}
/// <summary>
/// collision for the workers and the walls 
/// if collision is detected the workers change direction 
/// </summary>
void Game::workerWallCollision()
{
	
	for (int i = 0; i < m_workers.size(); i++)
	{
		int a = m_workers[i]->getTileX();
		int b = m_workers[i]->getTileY();

		if (m_tile[a][b - 1]->getObstacle())
		{
			m_workers[i]->changeDirection();
		}
		if (m_tile[a][b + 2]->getObstacle())
		{
			m_workers[i]->changeDirection();
		}
		if (m_tile[a - 1][b]->getObstacle())
		{
			m_workers[i]->changeDirection();
		}
		if (m_tile[a + 1][b]->getObstacle())
		{
			m_workers[i]->changeDirection();
		}
	}
}
/// <summary>
/// collision for the nest bullets and the walls 
/// if the collision is detected the bullet is reset
/// shoot bool is set to false 
/// </summary>
void Game::nestbulletWallCollision()
{
	for (int i = 0; i < m_alienNests.size(); i++)
	{
		int a = m_alienNests[i]->m_bullet->getTileX();
		int b = m_alienNests[i]->m_bullet->getTileY();
		
		if (m_tile[a][b - 1]->getObstacle() && m_alienNests[i]->getShoot())
		{	 
			m_alienNests[i]->m_bullet->resetToNest(m_alienNests[i]->getPos());
			m_alienNests[i]->setShoot();
		}
		if (m_tile[a][b + 1]->getObstacle() && m_alienNests[i]->getShoot())
		{
			m_alienNests[i]->m_bullet->resetToNest(m_alienNests[i]->getPos());
			m_alienNests[i]->setShoot();
		}
		if (m_tile[a - 1][b]->getObstacle() && m_alienNests[i]->getShoot())
		{
			m_alienNests[i]->m_bullet->resetToNest(m_alienNests[i]->getPos());
			m_alienNests[i]->setShoot();
		}
		if (m_tile[a + 1][b]->getObstacle() && m_alienNests[i]->getShoot())
		{
			m_alienNests[i]->m_bullet->resetToNest(m_alienNests[i]->getPos());
			m_alienNests[i]->setShoot();
		}
	}
}
/// <summary>
/// collision for the sweeper bots and the walls 
/// if collision is detected the sweepers change direction 
/// </summary>
void Game::predbulletWallCollision()
{
	for (int i = 0; i < m_predators.size(); i++)
	{
		int a = m_predators[i]->m_bullet->getTileX();
		int b = m_predators[i]->m_bullet->getTileY();

		if (m_tile[a][b - 1]->getObstacle())
		{
			m_predators[i]->m_bullet->resetToNest(m_predators[i]->getPos());
			//m_predators[i]->setShoot();
		}
		if (m_tile[a][b + 1]->getObstacle())
		{
			m_predators[i]->m_bullet->resetToNest(m_predators[i]->getPos());
			//m_predators[i]->setShoot();
		}
		if (m_tile[a - 1][b]->getObstacle())
		{
			m_predators[i]->m_bullet->resetToNest(m_predators[i]->getPos());
			//m_predators[i]->setShoot();
		}
		if (m_tile[a + 1][b]->getObstacle())
		{
			m_predators[i]->m_bullet->resetToNest(m_predators[i]->getPos());
			//m_predators[i]->setShoot();
		}
	}
}

void Game::sweeperWallCollision()
{

	for (int i = 0; i < m_sweeper.size(); i++)
	{
		int a = m_sweeper[i]->getTileX();
		int b = m_sweeper[i]->getTileY();

		if (m_tile[a][b - 1]->getObstacle())
		{
			m_sweeper[i]->changeDirection();
		}
		if (m_tile[a][b + 1]->getObstacle())
		{
			m_sweeper[i]->changeDirection();
		}
		if (m_tile[a - 1][b]->getObstacle())
		{
			m_sweeper[i]->changeDirection();
		}
		if (m_tile[a + 1][b]->getObstacle())
		{
			m_sweeper[i]->changeDirection();
		}
	}
}
/// <summary>
/// collision for the bullets and the walls 
/// erases the bullets from the vector if they collide with the walls 
/// </summary>
void Game::bulletWallCollision()
{
	for (int i = 0; i < m_player->m_bullets.size(); i++)
	{
		int a = m_player->m_bullets[i]->getTileX();
		int b = m_player->m_bullets[i]->getTileY();

		if (m_tile[a][b - 1]->getObstacle())
		{

			if (m_player->m_bullets[i]->getPosition().y < m_tile[a][b - 1]->getPosition().y + 65)
			{
				m_player->m_bullets.erase(m_player->m_bullets.begin());
			}
			
		}
		if (m_tile[a][b + 1]->getObstacle())
		{
			if (m_player->m_bullets[i]->getPosition().y > m_tile[a][b + 1]->getPosition().y - 30)
			{
				m_player->m_bullets.erase(m_player->m_bullets.begin());
			}
		}
		if (m_tile[a - 1][b]->getObstacle())
		{
			if (m_player->m_bullets[i]->getPosition().x < m_tile[a - 1][b]->getPosition().x + 65)
			{
				m_player->m_bullets.erase(m_player->m_bullets.begin());
			}
		}
		if (m_tile[a + 1][b]->getObstacle())
		{
			if (m_player->m_bullets[i]->getPosition().x > m_tile[a + 1][b]->getPosition().x - 30)
			{
				m_player->m_bullets.erase(m_player->m_bullets.begin());
			}
		}
	}
}

/// <summary>
/// breadth first search 
/// </summary>
/// <param name="posX"></param>
/// <param name="posY"></param>
void Game::breadthFirst(int posX, int posY) {


	m_tile[posX][posY]->setVisited(true);
	std::list<Tile*> queue;
	queue.push_back(m_tile[posX][posY]);
	int lowest = 0;

	while (!queue.empty())
	{
		auto gridPos = queue.front()->getGridPos();
		auto costPos = gridPos;
		auto prevPos = costPos;
		auto cost = queue.front()->getCost();
		auto rotation = 0.0f;


		if (costPos.first < 49)
		{
			prevPos = costPos;
			costPos.first++;
			addToQueue(costPos, gridPos, cost, queue, prevPos);
		}
		if (costPos.second < 49)
		{
			prevPos = costPos;
			costPos.second++;
			addToQueue(costPos, gridPos, cost, queue, prevPos);
		}
		if (costPos.first > 0)
		{
			prevPos = costPos;
			costPos.first--;
			addToQueue(costPos, gridPos, cost, queue, prevPos);
		}
		if (costPos.second > 0)
		{
			prevPos = costPos;
			costPos.second--;
			addToQueue(costPos, gridPos, cost, queue, prevPos);
		}

		queue.pop_front();

	}


}
/// <summary>
/// adds each node to the back of the queue
/// </summary>
/// <param name="currentPos"></param>
/// <param name="pos"></param>
/// <param name="cost"></param>
/// <param name="queue"></param>
/// <param name="prevpos"></param>
void Game::addToQueue(std::pair<int, int>& currentPos, std::pair<int, int>& pos, int& cost, std::list<Tile*>& queue, std::pair<int, int>& prevpos) {
	if (!m_tile[currentPos.first][currentPos.second]->getVisited() && !m_tile[currentPos.first][currentPos.second]->getObstacle())
	{
		auto currentTop = (queue.front()->getGridPos());
		m_tile[currentPos.first][currentPos.second]->setVisited(true);
		m_tile[currentPos.first][currentPos.second]->setPrevious(prevpos);
		m_tile[currentPos.first][currentPos.second]->setCost(cost + 1);
		queue.push_back(m_tile[currentPos.first][currentPos.second]);

	}
	currentPos = pos;
}
/// <summary>
/// checks for the lowest 
/// </summary>
/// <param name="lowest"></param>
/// <param name="current"></param>
void Game::checkLowest(int lowest, int current)
{
	if (current < lowest)
	{
		current = lowest;
	}
}
/// <summary>
/// generates the nests at a random position in the maze 
/// only spawns if there are no obstacles or nests already in that position 
/// spwans predator in the nest 
/// </summary>
void Game::generateNests()
{
	int i, j;
	int count = 0;
	AlienNest*  nest[3];

	while (m_alienNests.size() < 3)
	{
		i = (rand() % 49) + 1;
		j = (rand() % 49) + 1;

		if (!m_tile[i][j]->getObstacle() && !m_tile[i][j]->containsNest)
		{
			m_tile[i][j]->containsNest = true;
			nest[count] = new AlienNest(nestTexture, m_tile[i][j]->getPosition());

			if (!nest[count]->getSpawn())
			{
				generatePredators(*nest[count]);
			}
			m_alienNests.push_back(nest[count]);
			count++;
		}

	}
}
/// <summary>
/// generates the workers at random positions in the maze 
/// only places them at a position that doesnt contain a worker, obstacle, nest 
/// doesnts spawn on top of wall obstacles 
/// </summary>
void Game::generateWorkers()
{
	int i, j;
	int count = 0;
	Worker*  worker[15];

	while (m_workers.size() < 15)
	{
		i = (rand() % 49) + 1;
		j = (rand() % 49) + 1;

		if (!m_tile[i][j]->getObstacle() && !m_tile[i][j]->containsNest && !m_tile[i][j]->containsWorker)
		{
			if (!m_tile[i][j - 1]->getObstacle() && !m_tile[i][j + 1]->getObstacle() &&
				!m_tile[i - 1][j]->getObstacle() && !m_tile[i + 1][j]->getObstacle())
			{
				m_tile[i][j]->containsWorker = true;
				worker[count] = new Worker(workerTexture, m_tile[i][j]->getPosition());
				m_workers.push_back(worker[count]);
				m_score.push_back(false);
				count++;
			}
			
		}

	}
}
/// <summary>
/// generates the predator and pushes into vector 
/// </summary>
void Game::generatePredators(AlienNest alien)
{
	
	Predator *pred = new Predator(m_predTexture, alien.getPos());
	m_predators.push_back(pred);
	predSpawned = true;
	alien.setSpawn();
}



void Game::generateSweepers()
{
	int i, j;
	int count = 0;
	Sweeper*  sweeper[5];

	while (m_sweeper.size() < 5)
	{
		i = (rand() % 49) + 1;
		j = (rand() % 49) + 1;

		if (!m_tile[i][j]->getObstacle() && !m_tile[i][j]->containsNest && !m_tile[i][j]->containsWorker && !m_tile[i][i]->containsSweeper)
		{
			if (!m_tile[i][j - 1]->getObstacle() && !m_tile[i][j + 1]->getObstacle() &&
				!m_tile[i - 1][j]->getObstacle() && !m_tile[i + 1][j]->getObstacle())
			{
				m_tile[i][j]->containsSweeper = true;
				sweeper[count] = new Sweeper(sweeperTexture, m_tile[i][j]->getPosition());
				m_sweeper.push_back(sweeper[count]);
				count++;
			}

		}

	}
}
/// <summary>
/// gets the player position
/// </summary>
/// <returns></returns>
sf::Vector2f Game::getPlayerPos()
{
	return m_player->getPos();
}

/// <summary>
/// gets the Path travelled by the predator AI 
/// passes the starting x and y positions 
/// </summary>
/// <param name="posX"></param>
/// <param name="posY"></param>
void Game::getPath(int posX, int posY)
{
	queue.clear();

	queue.push_back(*m_tile[posX][posY]);

	auto iter = queue.begin();

	while (iter->getCost() != 0 && m_tile[iter->m_previous.first][iter->m_previous.second]->getState() != Goal)
	{
		m_tile[iter->m_previous.first][iter->m_previous.second]->setPath();
		queue.push_back(*m_tile[iter->m_previous.first][iter->m_previous.second]);

		iter++;
	}

}

void Game::scoring()
{
	//scoring
	for (int i = 0; i < m_workers.size(); i++)
	{
		if (m_workers[i]->getCollected() == true && m_score[i] == false)
		{
			m_count++;
			m_score[i] = true;
			m_countText.setString(std::to_string(m_count));
		}
	}
}