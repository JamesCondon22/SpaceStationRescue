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
	: m_window(sf::VideoMode(1920, 1080, 32), "SFML Playground", sf::Style::Default)

{

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);
	
	if (!m_font.loadFromFile("mytype.ttf"))
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
	if (!workerTexture.loadFromFile("worker.png"))
	{
		std::cout << "problem loading texture" << std::endl;
	}


	miniMapSprite.setTexture(miniMapTexture);
	mouse.setPosition(sf::Vector2i(0, 0), m_window);
	
	miniMapView.setViewport(sf::FloatRect(0.75f, 0.0f, 0.25f, 0.25f));

	
	gameView.setViewport(sf::FloatRect(0.f, 0.f, 3.0f, 3.0f));
	gameView.setSize(1250, 1250);


	int map[50][50] = {

		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
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
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};
	//myfile.open("map.txt");
	srand(time(NULL));

	m_worker = new Workers(100,100,10);


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
	miniMapRect.setSize(sf::Vector2f(150, 112));
	
	generateNests();
	generateWorkers();

	m_player = new Player();

	//AlienNest*  nestOne =  new AlienNest(nestTexture, m_tile[25][25]->getPosition());

	//m_alienNests.push_back(nestOne);
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
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 2500) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 2500) {
				int x = mouse.getPosition(m_window).x / 50;
				int y = mouse.getPosition(m_window).y / 50;
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
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 2500) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 2500) {
				int x = mouse.getPosition(m_window).x / 50;
				int y = mouse.getPosition(m_window).y / 50;
				if (m_goaltile != NULL) {
					//m_goaltile->changeColor();
				}
				m_goaltile = m_tile[x][y];
				std::cout << x << "," << y;
				//m_tile[x][y]->setGoal();
				breadthFirst(m_goaltile->getXpos(), m_goaltile->getYpos());

			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
       		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 2500) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 2500) {
				int x = mouse.getPosition(m_window).x / 50;
				int y = mouse.getPosition(m_window).y / 50;
				m_tile[x][y]->setObstacle();
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 50;
				int y = mouse.getPosition(m_window).y / 50;
				m_tile[x][y]->removeObstacle();
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {

				m_tile[j][i]->setCost(0);
				m_tile[j][i]->setVisited(false);
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

	m_player->update(dt);
	playerPosition = sf::Vector2f(m_player->getPos().x + 400, m_player->getPos().y + 400);
	gameView.setCenter(playerPosition);
	
	for (int i = 0; i < m_workers.size(); i++)
	{
		m_workers[i]->update(dt, m_player->getPos());
	}
	int curX =  round(m_player->getPos().x / 50);
	int curY = round(m_player->getPos().y / 50);

	
	collision(curX, curY);
	
	
	std::cout << m_player->getPos().x << ", " << m_player->getPos().y << std::endl;

	
	miniMapView.setCenter(m_player->getPos());
	
}








/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	
	m_window.setView(gameView);
	
	miniMapRect.setPosition(miniMapView.getCenter().x + 86, miniMapView.getCenter().y - 230);
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {

			if (m_tile[j][i]->getPosition().x > playerPosition.x - 700 && m_tile[j][i]->getPosition().x < playerPosition.x - 200
				&& m_tile[j][i]->getPosition().y > playerPosition.y - 700 && m_tile[j][i]->getPosition().y < playerPosition.y - 200)
			{
				m_tile[j][i]->render(m_window);
			}
			
		}
	}

	m_worker->render(m_window);

	for (int i = 0; i < m_alienNests.size(); i++)
	{
		m_alienNests[i]->render(m_window);
	}

	for (int i = 0; i < m_workers.size(); i++)
	{
		m_workers[i]->render(m_window);
	}

	m_player->render(m_window);
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

	m_window.display();

	
	
	
	
}

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
		m_tile[currentPos.first][currentPos.second]->setColor(sf::Color(255, 200 - (cost * 4), 215 - (cost * 2), 221 - (cost * 3)));
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

void Game::generateNests()
{
	int i, j;
	int count = 0;
	AlienNest*  nest[3];

	while (m_alienNests.size() < 3)
	{
		i = (rand() % 50) + 1;
		j = (rand() % 50) + 1;

		if (!m_tile[i][j]->getObstacle() && !m_tile[i][j]->containsNest)
		{
			m_tile[i][j]->containsNest = true;
			nest[count] = new AlienNest(nestTexture, m_tile[i][j]->getPosition());
			m_alienNests.push_back(nest[count]);
			count++;
		}

	}
}

void Game::generateWorkers()
{
	int i, j;
	int count = 0;
	Worker*  worker[20];

	while (m_workers.size() < 20)
	{
		i = (rand() % 49) + 1;
		j = (rand() % 49) + 1;

		if (!m_tile[i][j]->getObstacle() && !m_tile[i][j]->containsNest && !m_tile[i][j]->containsWorker)
		{
			m_tile[i][j]->containsWorker = true;
			worker[count] = new Worker(workerTexture, m_tile[i][j]->getPosition());
			m_workers.push_back(worker[count]);
			count++;
		}

	}
}
