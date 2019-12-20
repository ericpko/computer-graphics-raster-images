#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  double r, g, b, h, s, v;
  int pxl_idx = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      // Get the rgb values
      r = ((double) rgb[3 * (row * width + col) + 0]) / 255.0;
      g = ((double) rgb[3 * (row * width + col) + 1]) / 255.0;
      b = ((double) rgb[3 * (row * width + col) + 2]) / 255.0;

      // Convert the rgb values to hsv
      rgb_to_hsv(r, g, b, h, s, v);
      h += shift;                     // add the hue shift
      if (h >= 360) {
        h = 359.9;
      }

      // Convert back to rgb values
      hsv_to_rgb(h, s, v, r, g, b);
      shifted[pxl_idx++] = (unsigned char) (r * 255);
      shifted[pxl_idx++] = (unsigned char) (g * 255);
      shifted[pxl_idx++] = (unsigned char) (b * 255);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}






// Other type of loop version
  // double r, g, b, h, s, v;
  // int pxl_idx = 0;
  // for (int row = 0; row < height; row++) {
  //   for (int col = 0; col < width * 3; col += 3) {
  //     // Get the rgb values
  //     r = ((double) rgb[row * width * 3 + col + 0]) / 255.0;
  //     g = ((double) rgb[row * width * 3 + col + 1]) / 255.0;
  //     b = ((double) rgb[row * width * 3 + col + 2]) / 255.0;

  //     // Convert the rgb values to hsv
  //     rgb_to_hsv(r, g, b, h, s, v);
  //     h += shift;                     // add the hue shift
  //     if (h >= 360) {
  //       h = 359.9;
  //     }

  //     // Convert back to rgb values
  //     hsv_to_rgb(h, s, v, r, g, b);
  //     shifted[pxl_idx++] = (unsigned char) (r * 255);
  //     shifted[pxl_idx++] = (unsigned char) (g * 255);
  //     shifted[pxl_idx++] = (unsigned char) (b * 255);
  //   }
  // }
