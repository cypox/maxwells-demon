#pragma once

#include <math.h>
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
    double radius = 20.;
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
      _p.emplace_back(x, y, xv, yv, radius);
    }
  }

  double distance(double x1, double y1, double x2, double y2)
  {
    double a1 = (x2 - x1);
    double b1 = (y2 - y1);
    a1 *= a1;
    b1 *= b1;
    return std::sqrt(a1 + b1);
  }

  void step()
  {
    if (_running)
    {
      for (int i = 0 ; i < _p.size() ; ++ i)
      {
        particle& p = _p[i];
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

      /* avoid particle collisions */
      /* TODO: BVH, Grid or Octree */
      for (int i = 0 ; i < _p.size() ; ++ i)
      {
        particle& p = _p[i];
        for (int j = i+1 ; j < _p.size() ; ++ j)
        {
          if (i != j)
          {
            particle& q = _p[j];
            if (distance(p._x, p._y, q._x, q._y) <= (p._r + q._r)) // i and j are colliding
            {
              std::swap(p._xv, q._xv);
              std::swap(p._yv, q._yv);
            }
          }
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
