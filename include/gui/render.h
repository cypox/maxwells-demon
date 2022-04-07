#pragma once

#include "system.h"

#include <cmath>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>


char* get_time()
{
  int millisec;
  struct timeval tv;
  gettimeofday(&tv, NULL);

  millisec = lrint(tv.tv_usec/1000.0);
  if (millisec>=1000)
  {
    millisec -=1000;
    tv.tv_sec++;
  }
  std::time_t t = std::time(nullptr);
  static char buffer[100];
  std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&t));
  sprintf(buffer+8, ".%03d", millisec);
  return buffer;
}

class render {
public:
  render() = delete;

  render(sf::RenderWindow& window, particle_system& world) : m_window(window), m_world(world)
  {
    if (!m_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"))
    {
      throw std::runtime_error("font not found!");
    }
  }

  void run()
  {
    m_window.setActive(true);

    while (m_window.isOpen())
    {
      handle_events();
      m_window.clear();
      render_world();
      m_window.display();
    }
  }

  void handle_events()
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          m_window.close();
          break;
        
        case sf::Event::Resized:
          event.size.width;
          event.size.height;
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code)
          {
            case sf::Keyboard::S:
              break;
            case sf::Keyboard::Q:
              m_window.close();
            case sf::Keyboard::P:
              break;
            case sf::Keyboard::T:
              break;
          }
          break;

        default:
          break;
      }
    }
  }

  void render_world()
  {
  }

  void draw_background(sf::FloatRect area, sf::Color outline, sf::Color fill = sf::Color::Transparent)
  {
    sf::RectangleShape background(sf::Vector2f(area.width, area.height));
    background.setPosition(area.left, area.top);
    background.setOutlineThickness(2);
    background.setOutlineColor(outline);
    background.setFillColor(fill);
    m_window.draw(background);
  }

private:
  sf::RenderWindow& m_window;
  const particle_system& m_world;
  sf::Font m_font;
};
