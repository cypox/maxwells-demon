#pragma once

#include <vector>
#include <random>

#include "particle.h"


class particle_system {
public:
  particle_system(int n)
  {
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
  }

  const std::vector<particle>& get_particles() const
  {
    return _p;
  }

private:
  std::vector<particle> _p;
};
