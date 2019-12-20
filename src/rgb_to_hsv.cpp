#include "rgb_to_hsv.h"
#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * Algorithm from https://en.wikipedia.org/wiki/HSL_and_HSV
   */
  double max = std::max({r, g, b});
  double min = std::min({r, g, b});
  double delta = max - min;

  // Set value
  v = max;

  // Set saturation
  if (max == 0) {
    s = 0;
    h = 0;
    return;
  } else {
    s = delta / max;
  }

  // Set hue
  if (max == min) { // delta == 0
    h = 0;
  } else if (max == r) {
    h = 60 * ((g - b) / delta);
  } else if (max == g) {
    h = 60 * (2 + ((b - r) / delta));
  } else if (max == b) {
    h = 60 * (4 + ((r - g) / delta));
  } else {
    throw("Shouldn't get here");
  }

  // Check that h is in [0, 360)
  while (h < 0) {
    h += 360;
  }

  // assert(h >= 0 && h < 360);
  // assert(s >= 0 && s <= 1);
  // assert(v >= 0 && v <= 1);
  ////////////////////////////////////////////////////////////////////////////
}
