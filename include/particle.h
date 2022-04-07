#pragma once


class particle {
public:
  particle() : _x(0.), _y(0.), _xv(0.), _yv(0.) {}

  particle(double *f())
  {
    _x = *f();
    _y = *f();
    _xv = *f();
    _yv = *f();
  }

  particle(double x, double y, double xv, double yv) : _x(x), _y(y), _xv(xv), _yv(yv) {}

private:
  double _x;
  double _y;
  double _xv;
  double _yv;
};
