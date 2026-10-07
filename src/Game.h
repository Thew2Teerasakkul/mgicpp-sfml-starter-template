
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);

  void mainMenu();
  void inGame();
  void spawn();

 private:
  sf::RenderWindow& window;

  sf::Texture backgroundTexture{"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(backgroundTexture);

  sf::Texture birdTexture{ "../Data/Images/WhackaMole Worksheet/bird.png" };
  sf::Sprite bird = sf::Sprite(birdTexture);

  sf::Texture menubackgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite menubackground = sf::Sprite(menubackgroundTexture);

  sf::Font font{"../Data/Fonts/OpenSans-Bold.ttf"};
  sf::Text titleText = sf::Text(font);
  sf::Text startOption = sf::Text(font);
  sf::Text quitOption = sf::Text(font);
  sf::Text scoreText = sf::Text(font);

  bool inMenu;
  bool reverse = false;
  
  int score = 0;
  float speed;

};

#endif // SFML_GAME_H
