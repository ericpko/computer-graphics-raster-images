#include "rotate.h"

void rotate(const std::vector<unsigned char> &input, const int width,
            const int height, const int num_channels,
            std::vector<unsigned char> &rotated)
{
  rotated.resize(height * width * num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // assert(
  //   (num_channels == 3 || num_channels == 1 ) &&
  //   ".ppm only supports RGB or grayscale images");
  /**
   * We want to move the pixel at (x, y) = (0, 0) to (x + width - 1, y), but
   * this is not general. In general, we need to use a rotation matrix for
   * each (x, y) -> M (x, y)
   */
  // The for loops labels are from the perspective of iterating through the
  // original (input) vector
  int subpixel = 0;
  for (int col = width * num_channels - 1; col >= 0; col -= num_channels)
  {
    for (int row = 0; row < height; row++)
    {
      if (num_channels == 1)
      {
        rotated[subpixel++] = input[(row * width) + col];
      }
      else if (num_channels == 3)
      {
        rotated[subpixel++] = input[(row * width * num_channels) + col - 2];
        rotated[subpixel++] = input[(row * width * num_channels) + col - 1];
        rotated[subpixel++] = input[(row * width * num_channels) + col - 0];
      }
      else
      {
        throw("The number of channels must be 1 or 3");
        exit(EXIT_FAILURE);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
