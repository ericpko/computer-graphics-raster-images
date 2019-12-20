#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // assert(
  //   (num_channels == 3 || num_channels == 1 ) &&
  //   ".ppm only supports RGB or grayscale images");
  /**
   * We want to reflect across the y-axis, so y = f(-x)
   * So in terms of the image, we want to move pixel at (x, y) to (width - x - 1, y)
   */

  // Iterate through all the subpixels and reflect horizontally
  // NOTE we are really just iterating a single list, but through a nested loop
  // and pretending as if it's a matrix.
  // for (int row = 0; row < height; row++) {
  //   for (int col = 0; col < width * num_channels; col += num_channels) {
  //     if (num_channels == 1) {
  //       reflected[(row * width) + col] = input[(row * width) - col - 1];

  //     } else if (num_channels == 3) {
  //       reflected[(row * width * num_channels) + col + 0] = input[(row * width * num_channels) - col - 1 - 2]; // r
  //       reflected[(row * width * num_channels) + col + 1] = input[(row * width * num_channels) - col - 1 - 1]; // g
  //       reflected[(row * width * num_channels) + col + 2] = input[(row * width * num_channels) - col - 1 - 0]; // b
  //     }
  //   }
  // }

  // Solution 2: starting at the origin.. basically the same though
  // for (int y = height - 1; y >= 0; y--) {
  //   for (int x = 0; x < width * num_channels; x += num_channels) {
  //     if (num_channels == 3) {
  //       reflected[(y * width * num_channels) + x + 0] = input[(y * width * num_channels) - x - 1 - 2]; // r
  //       reflected[(y * width * num_channels) + x + 1] = input[(y * width * num_channels) - x - 1 - 1]; // g
  //       reflected[(y * width * num_channels) + x + 2] = input[(y * width * num_channels) - x - 1 - 0]; // b
  //     } else {
  //       reflected[(y * width) + x] = input[(y * width) - x - 1];
  //     }
  //   }
  // }

  // Sol 3: This is the most intuitive solution to me
  int subpixel = 0;                 // index of the subpixel we are on
  for (int row = 0; row < height; row++) {
    for (int col = (width * num_channels) - 1; col >= 0; col -= num_channels) {
      if (num_channels == 1) {
        reflected[subpixel++] = input[(row * width) + col];

      } else if (num_channels == 3) {
        reflected[subpixel++] = input[(row * width * num_channels) + col - 2];
        reflected[subpixel++] = input[(row * width * num_channels) + col - 1];
        reflected[subpixel++] = input[(row * width * num_channels) + col - 0];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
