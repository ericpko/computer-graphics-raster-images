#include "rgba_to_rgb.h"
#include <iostream>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  /**
   * Below is a couple of print statements to see what we're dealing with
   */
  // std::cout << "The width is: " << width << std::endl;
  // std::cout << "The height is: " << height << std::endl;

  // Iterate through the entire vector
  // int i = 0;
  // for (auto pixel = rgba.begin(); pixel != rgba.end(); pixel++) {
  //   std::cout << (int) *pixel << ' ';
  //   i++;
  // }

  // Print out six pixels (24 sub pixels) (24 channels - 6 x (rgb + alpha))
  // int i = 0;
  // for (auto subpixel = rgba.begin(); i < 24; subpixel++, i++) {
  //   std::cout << (int) *subpixel << ' ';
  // }
  // std::cout << "\n\n\n" << std::endl;

  /**
   * NOTE: rgba is a 1D vector. We want to iterate through every pixel
   * and remove the alpha channel
   */
  // int num_subpixels = width * height * 4;
  // for (int subpix_i = 0, subpix_j = 0, i = 1; subpix_j < num_subpixels; subpix_j++, i++) {
  //   if (i % 4 != 0) {
  //     rgb[subpix_i] = rgba[subpix_j];
  //     subpix_i++;
  //   }
  // }

  // Faster solution
  int num_pixels = width * height;
  for (int subpixel = 0; subpixel < num_pixels; subpixel++) {
    rgb[subpixel * 3] = rgba[subpixel * 4];
    rgb[(subpixel * 3) + 1] = rgba[(subpixel * 4) + 1];
    rgb[(subpixel * 3) + 2] = rgba[(subpixel * 4) + 2];
  }


  // Print test to see if what we modified worked
  // i = 0;
  // for (auto subpixel = rgb.begin(); i < 18; subpixel++, i++) {
  //   std::cout << (int) *subpixel << ' ';
  // }
  // std::cout << "\n\n\n" << std::endl;
  ////////////////////////////////////////////////////////////////////////////
}
