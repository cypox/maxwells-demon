#pragma once

#include <vector>
#include <random>
#include <atomic>

#include "particle.h"


class particle_system {
public:
  particle_system(int n, double dt, int width, int height)
  {
    _dt = dt;
    _running = true;
    _xmin = 0.;
    _xmax = width;
    _ymin = 0.;
    _ymax = height;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> xdist(_xmin, _xmax);
    std::uniform_real_distribution<double> ydist(_ymin, _ymax);
    std::uniform_real_distribution<double> vdist(-10., 10.);
    for (int i = 0 ; i < n ; ++ i)
    {
      double x = xdist(mt);
      double y = ydist(mt);
      double xv = vdist(mt);
      double yv = vdist(mt);
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
        if (p._x > _xmax)
        {
          p._x -= 2*(p._x - _xmax);
          p._xv = -p._xv;
        }
        else if (p._x < _xmin)
        {
          p._x -= 2*(p._x - _xmin);
          p._xv = -p._xv;
        }
        if (p._y > _ymax)
        {
          p._y -= 2*(p._y - _ymax);
          p._yv = -p._yv;
        }
        else if (p._y < _ymin)
        {
          p._y -= 2*(p._y - _ymin);
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
  double _xmin;
  double _xmax;
  double _ymin;
  double _ymax;
  mutable std::atomic<bool> _running;
  double _dt;
  std::vector<particle> _p;
};
