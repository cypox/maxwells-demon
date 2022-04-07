#pragma once

#include <vector>
#include <random>
#include <atomic>

#include "particle.h"


class particle_system {
public:
  particle_system(int n, double dt)
  {
    _dt = dt;
    _running = true;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (int i = 0 ; i < n ; ++ i)
    {
      double x = dist(mt);
      double y = dist(mt);
      double xv = dist(mt);
      double yv = dist(mt);
      _p.emplace_back(x, y, xv, yv);
    }
  }

  void step()
  {
    if (_running)
    {
      for (auto& p : _p)
      {
        p._x += _dt * p._xv;
        p._y += _dt * p._yv;

        /* avoid wall collision */
        if (p._x > 10.0)
        {
          p._x -= 2*(p._x - 10.);
          p._xv = -p._xv;
        }
        else if (p._x < -10.0)
        {
          p._x -= 2*(p._x + 10.);
          p._xv = -p._xv;
        }
        if (p._y > 10.0)
        {
          p._y -= 2*(p._y - 10.);
          p._yv = -p._yv;
        }
        else if (p._y < -10.0)
        {
          p._y -= 2*(p._y + 10.);
          p._yv = -p._yv;
        }
      }
    }
  }

  const std::vector<particle>& get_particles() const
  {
    return _p;
  }

  bool is_running() const
  {
    return _running;
  }

  void pause_simulation() const
  {
    _running = false;
  }

  void resume_simulation() const
  {
    _running = true;
  }

private:
  mutable std::atomic<bool> _running;
  double _dt;
  std::vector<particle> _p;
};
