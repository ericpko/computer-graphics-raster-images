#include "hsv_to_rgb.h"
#include <algorithm>
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * Algorithm from https://en.wikipedia.org/wiki/HSL_and_HSV
   */
  double c = v * s;               // c for chroma
  double _h = h / 60.0;
  double x = c * (1 - (std::fabs((std::fmod(_h, 2)) - 1)));

  double _r, _g, _b;
  if (h == 0) {
    _r = 0, _g = 0, _b = 0;
  } else if (_h >= 0 && _h <= 1) {
    _r = c, _g = x, _b = 0;
  } else if (_h > 1 && _h <= 2) {
    _r = x, _g = c, _b = 0;
  } else if (_h > 2 && _h <= 3) {
    _r = 0, _g = c, _b = x;
  } else if (_h > 3 && _h <= 4) {
    _r = 0, _g = x, _b = c;
  } else if (_h > 4 && _h <= 5) {
    _r = x, _g = 0, _b = c;
  } else if (_h > 5 && _h <= 6) {
    _r = c, _g = 0, _b = x;
  }

  double m = v - c;

  r = _r + m;
  g = _g + m;
  b = _b + m;

  // assert(r >= 0 && r <= 1);
  // assert(g >= 0 && r <= 1);
  // assert(b >= 0 && r <= 1);
  ////////////////////////////////////////////////////////////////////////////
}
