#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  double r, g, b, h, s, v;
  int pxl_idx = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      // Get the rgb values
      r = ((double) rgb[3 * (row * width + col) + 0]) / 255.0;
      g = ((double) rgb[3 * (row * width + col) + 1]) / 255.0;
      b = ((double) rgb[3 * (row * width + col) + 2]) / 255.0;

      // Convert the rgb values to hsv and set the saturation
      rgb_to_hsv(r, g, b, h, s, v);
      s *= (1 - factor);
      // assert(s >= 0 && s <= 1);

      // Convert back to rgb values
      hsv_to_rgb(h, s, v, r, g, b);
      desaturated[pxl_idx++] = (unsigned char) (r * 255);
      desaturated[pxl_idx++] = (unsigned char) (g * 255);
      desaturated[pxl_idx++] = (unsigned char) (b * 255);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
