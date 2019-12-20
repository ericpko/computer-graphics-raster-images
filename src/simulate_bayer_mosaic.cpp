#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  if (width == 0 || height == 0) {
    throw("Image must have proper dimentions");
  }
  /**
   * Idea: Start in the upper left corner (green) and since it is an alternating
   * square pattern, we can use even/odd indices to determine the color
   */
  int green_blue, red_green;
  int pxl_idx = 0;
  for (int row = 0; row < height; row++) {
    if (row % 2 == 0) {
      // Then we are on an even row, so we alternate g, b, g, b, ...
      green_blue = 0;
      for (int col = 0; col < width; col++) {
        if (green_blue++ % 2 == 0) {
        // Then we are on a green square
        bayer[pxl_idx++] = rgb[(row * width + col) * 3 + 1];
        } else {
        // Then we are on a blue square
        bayer[pxl_idx++] = rgb[(row * width + col) * 3 + 2];
        }
      }

    } else {
      // Then we are on an odd row, so we alternate r, g, r, g, ...
      red_green = 0;
      for (int col = 0; col < width; col++) {
        if (red_green++ % 2 == 0) {
          // Then we are on a red square
          bayer[pxl_idx++] = rgb[(row * width + col) * 3 + 0];
        } else {
          // Then we are on a green square
          bayer[pxl_idx++] = rgb[(row * width + col) * 3 + 1];
        }
      }
    }
  }
  /**
   * NOTE: When we are indexing a pixel here (i.e. green = rgb[(row * width + col) * 3 + 1];)
   * (row * width + col) is the index of the pixel we want, then we multiply by
   * 3 since we know we are indexing a 3-channel pixel, then we add 1 to get the
   * green subpixel in this case. This is different than the way we indexed
   * in rgb_to_gray.cpp
   */
  ////////////////////////////////////////////////////////////////////////////
}
