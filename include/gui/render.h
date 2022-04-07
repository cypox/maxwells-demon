#pragma once

#include <cmath>
#include <sys/time.h>
#include <iomanip>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "system.h"


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
      render_cursor();
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
              if (m_world.is_running())
                m_world.pause_simulation();
              else
                m_world.resume_simulation();
              break;
            case sf::Keyboard::T:
              break;
          }
          break;
        
        case sf::Event::MouseMoved:
          _cursor_pos = sf::Mouse::getPosition(m_window);
          break;

        default:
          break;
      }
    }
  }

  void draw_particle(particle& p)
  {
    double x(p._x), y(p._y);
    int radius = p._r;

    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color(10, 10, 250));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color(250, 150, 100));

    shape.setPosition(x - radius, y - radius);

    m_window.draw(shape);
  }

  void render_world()
  {
    const std::vector<particle>& ps = m_world.get_particles();
    for (auto p : ps)
    {
      draw_particle(p);
    }
  }

  void render_cursor()
  {
    const std::vector<particle>& ps = m_world.get_particles();
    for (auto p : ps)
    {
      double xmin = p._x - p._r;
      double xmax = p._x + p._r;
      double ymin = p._y - p._r;
      double ymax = p._y + p._r;
      if (_cursor_pos.x >= xmin && _cursor_pos.x <= xmax && _cursor_pos.y >= ymin && _cursor_pos.y <= ymax)
      {
        std::stringstream ss;
        ss << p._x << " " << p._y << "\n" << p._xv << " " << p._yv;
        sf::Text text;
        text.setFont(m_font);
        sf::String debug_info;
        debug_info += ss.str();
        text.setString(debug_info);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(_cursor_pos.x, _cursor_pos.y);
        m_window.draw(text);
      }
    }
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
  sf::Vector2i _cursor_pos;
  sf::RenderWindow& m_window;
  const particle_system& m_world;
  sf::Font m_font;
};
