#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int pxl_val, r, g, b;
  int pxl_index = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width * 3; col += 3) {

      // Average the 3-channel pixel into a single pixel
      // greyscale pixel = 0.2126r + 0.7152g + 0.0722b
      // NOTE: We place a higher scale on green since we have more green
      // receptors in our eyes. (We evolved in the jungle - lots of green)
      r = rgb[(row * width * 3) + col + 0];
      g = rgb[(row * width * 3) + col + 1];
      b = rgb[(row * width * 3) + col + 2];
      pxl_val = 0.2126 * r + 0.7152 * g + 0.0722 * b;

      // Update the greyscale pixel
      gray[pxl_index++] = (unsigned char) pxl_val;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
