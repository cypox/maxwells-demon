#include <iostream>

#include <SFML/Window.hpp>

#include "system.h"
#include "gui/render.h"


int main(int argc, char** argv)
{
  std::cout << "maxwell demon game" << std::endl;

  particle_system world(10, 0.0001, 1500, 900);

  sf::RenderWindow window(sf::VideoMode(1500, 900), "Maxwell's Demon Game");
  window.setFramerateLimit(60);

  render renderer(window, world);

  sf::Thread thread(&render::run, &renderer);
  thread.launch();

  while (window.isOpen())
  {
    window.setActive(false);
    world.step();
  }

  return 0;
}
