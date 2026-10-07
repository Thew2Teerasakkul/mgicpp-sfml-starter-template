
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{

}

// We call this once after the game class is instantiated
bool Game::init()
{
	inMenu = true;

	mainMenu();
	inGame();

  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{			
    if (inMenu == false)
	{
		speed = 200;
		if (bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().size.x) || bird.getPosition().x < 0)
		{
			reverse = !reverse;
		}

		if (reverse == false)
		{
			bird.move({ 1 * speed * dt, 0 });
		}

		if (reverse == true)
		{
			bird.move({ -1 * speed * dt, 0 });
		}
	}
}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	if (inMenu == true)
	{
		window.draw(menubackground);
		window.draw(titleText);
		window.draw(startOption);
		window.draw(quitOption);
	}
	if (inMenu == false)
	{
		window.draw(background);
		window.draw(bird);
		window.draw(scoreText);
	}
}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
    sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(position);

		if (inMenu == true)
		{
			if (startOption.getGlobalBounds().contains(mousePos))
			{
				inMenu = false;
			}
			else if (quitOption.getGlobalBounds().contains(mousePos))
			{
				window.close();
			}
		}
		
		if (inMenu == false)
		{
			if (bird.getGlobalBounds().contains(mousePos))
			{
				std::cout << "Bird was clicked! \n";
				score += 100;
				std::cout << "Score: " << score << "\n";
				scoreText.setString("Score: " + std::to_string(score));
				spawn();
			}
		}
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}

void Game::mainMenu()
{
	if (!menubackgroundTexture.loadFromFile("../Data/Images/WhackaMole Worksheet/background.png"))
	{
		std::cout << "Failed to load menu background texture \n";
	}
	menubackground.setTexture(menubackgroundTexture);

	if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "Failed to load font \n";
	}
	titleText.setString("Whack-a-Mole (Again)");
	titleText.setCharacterSize(48);
	titleText.setFillColor(sf::Color::Red);
	titleText.setPosition({300, 50});
	
	startOption.setString("Start");
	startOption.setCharacterSize(30);
	startOption.setFillColor(sf::Color::Black);
	startOption.setPosition({200, 350});

	quitOption.setString("Quit");
	quitOption.setCharacterSize(30);
	quitOption.setFillColor(sf::Color::Black);
	quitOption.setPosition({800, 350});
}

void Game::inGame()
{
	if (!backgroundTexture.loadFromFile("../Data/Images/WhackaMole Worksheet/background.png"))
	{
		std::cout << "Failed to load background texture \n";
	}

	if (!birdTexture.loadFromFile("../Data/Images/WhackaMole Worksheet/bird.png"))
	{
		std::cout << "Failed to load bird texture \n";
	}
	bird.setScale({ 0.5f, 0.5f });
	bird.setPosition({ 400, 490 });

	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setCharacterSize(30);
	scoreText.setPosition({10, 10});
}

void Game::spawn()
{
	float x = static_cast<float>(rand() % (window.getSize().x - static_cast<int>(bird.getGlobalBounds().size.x)));
	float y = static_cast<float>(rand() % (window.getSize().y - static_cast<int>(bird.getGlobalBounds().size.y)));
	bird.setPosition({ x, y });
	reverse = rand() % 2 == 0; // Randomly set reverse to true or false
}