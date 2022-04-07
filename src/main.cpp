#include <iostream>

#include <SFML/Window.hpp>


int main(int argc, char** argv)
{
  std::cout << "maxwell demon game" << std::endl;

  sf::Window window(sf::VideoMode(800, 600), "Maxwell's Demon Game");

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  return 0;
}
