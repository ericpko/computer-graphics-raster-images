#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  if (width == 0 || height == 0) {
    throw("Image must have proper dimentions");
  }


  int green_blue, red_green;
  int r, g, b;
  int pxl_index = 0;
  for (int row = 0; row < height; row++) {
    if (row % 2 == 0) {
      // Then we are on an even row of g, b, g, b, ...
      green_blue = 0;
      for (int col = 0; col < width; col++) {
        if (green_blue++ % 2 == 0) {
          // Then we are on a green square. We can get the exact value
          g = bayer[row * width + col];

          // Check our bounds
          if (row == 0 || row == height - 1) {
            // Red can exclusively be above or below
            int fix = (row == 0) ? 1 : -1;
            r = bayer[(row + fix) * width + col];
            if (col == 0) {
              // Blue can only be to the right
              b = bayer[1];
            } else if (col + 1 >= width) {
              // Blue can only be to the left
              b = bayer[col - 1];
            } else {
              // Blue is on both sides of the green square
              b = ((double) bayer[col - 1] + bayer[col + 1]) / 2;
            }
          } else {
            // Then we are in the middle of a column (on a green square)
            // Red is above and below in this case
            r = ((double) bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col]) / 2;
            if (col == 0) {
              // Blue can only be to the right
              b = bayer[row * width + col + 1];
            } else if (col + 1 >= width) {
              // Blue can only be to the left
              b = bayer[row * width + col - 1];
            } else {
              // Blue is on both sides of the green square
              b = ((double) bayer[row * width + col - 1] + bayer[row * width + col + 1]) / 2;
            }
          }

          // Add the rgb values
          rgb[pxl_index++] = (unsigned char) r;
          rgb[pxl_index++] = (unsigned char) g;
          rgb[pxl_index++] = (unsigned char) b;

        } else {
          // Then we are on a blue square. Get the exact value
          b = bayer[row * width + col];

          // Check the bounds
          if (row == 0 || row == height - 1) {
            // Then red can be exclusively above or below
            int fix = (row == 0) ? 1 : -1;
            if (col == width - 1) {
              // Then we are on a blue square in the top or bottom right corner
              r = bayer[(row + fix) * width + col - 1];
              g = ((double) bayer[(row + fix) * width + col] + bayer[row * width + col - 1]) / 2;
            } else {
              // Then we are on a blue square in the middle of the top or bottom row
              r = ((double) bayer[(row + fix) * width + col - 1] + bayer[(row + fix) * width + col + 1]) / 2;
              g = ((double) bayer[(row + fix) * width + col] + bayer[row * width + col - 1] + bayer[row * width + col + 1]) / 3;
            }
          } else {
            // Then we are in the middle of a column (on a blue square)
            if (col == width - 1) {
              // Then we are at the far right edge
              r = ((double) bayer[(row + 1) * width + col - 1] + bayer[(row - 1) * width + col - 1]) / 2;
              g = ((double) bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col] + bayer[row * width + col - 1]) / 3;
            } else {
              // There are 4 red around
              r = ((double) bayer[(row + 1) * width + col - 1] + bayer[(row + 1) * width + col + 1] + bayer[(row - 1) * width + col - 1] + bayer[(row - 1) * width + col + 1]) / 4;
              g = ((double) bayer[(row + 1) * width + col] + bayer[(row - 1) * width + col] + bayer[row * width + col - 1] + bayer[row * width + col + 1]) / 4;
            }
          }

          // Add rgb values
          rgb[pxl_index++] = (unsigned char) r;
          rgb[pxl_index++] = (unsigned char) g;
          rgb[pxl_index++] = (unsigned char) b;
        }
      }

    } else {
      // Then we are on an odd row of r, g, r, g, ...
      red_green = 0;
      for (int col = 0; col < width; col++) {
        if (red_green++ % 2 == 0) {
          // Then we are on a red square. We can get the exact value
          r = bayer[row * width + col];

          // Check bounds
          if (col == 0 || col == width - 1) {
            // Then the red square is on the left side or right side
            int fix = (col == 0) ? 1 : -1;
            if (row == height - 1) {
              // Then we are bottom left or right
              g = ((double) bayer[(row - 1) * width * col] + bayer[row * width + col + fix]) / 2;
              b = bayer[(row - 1) * width + col + fix];
            } else {
              g = ((double) bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col] + bayer[row * width + col + fix]) / 3;
              b = ((double) bayer[(row - 1) * width + col + fix] + bayer[(row + 1) * width + col + fix]) / 2;
            }
          } else {
            if (row == height - 1) {
              // red square is on bottom row center ish
              g = ((double) bayer[row * width + col - 1] + bayer[row * width + col + 1] + bayer[(row - 1) * width + col]) / 3;
              b = ((double) bayer[(row - 1) * width + col - 1] + bayer[(row - 1) * width + col + 1]) / 2;
            } else {
              // red square is centered
              g = ((double) bayer[row * width + col - 1] + bayer[row * width + col + 1] + bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col]) / 4;
              b = ((double) bayer[(row - 1) * width + col - 1] + bayer[(row - 1) * width + col + 1] + bayer[(row + 1) * width + col - 1] + bayer[(row + 1) * width + col + 1]) / 4;
            }
          }

          // Add rgb values
          rgb[pxl_index++] = (unsigned char) r;
          rgb[pxl_index++] = (unsigned char) g;
          rgb[pxl_index++] = (unsigned char) b;

        } else {
          // Then we are on a green square. Get the exact value
          g = bayer[row * width + col];

          /**
           * TODO: Ave red and blue values
           */
          // Check bounds
          if (col == width - 1) {
            // Then the green square is on the right side
            if (row == height - 1) {
              // Then the green square is on the bottom right side
              r = bayer[row * width + col - 1];
              b = bayer[(row - 1) * width + col];
            } else {
              // Then the green square is on the right side not bottom
              r = bayer[row * width + col - 1];
              b = ((double) bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col]) / 2;
            }
          } else {
            // Then the green square is centered in a row
            if (row == height - 1) {
              // Then the green square is on the bottom row centered
              r = ((double) bayer[row * width + col - 1] + bayer[row * width + col + 1]) / 2;
              b = bayer[(row - 1) * width + col];
            } else {
              // Then the green square is centered on the board
              r = ((double) bayer[row * width + col - 1] + bayer[row * width + col + 1]) / 2;
              b = ((double) bayer[(row - 1) * width + col] + bayer[(row + 1) * width + col]) / 2;
            }
          }

          // Add rgb values
          rgb[pxl_index++] = (unsigned char) r;
          rgb[pxl_index++] = (unsigned char) g;
          rgb[pxl_index++] = (unsigned char) b;
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}









// /**
//            * TODO: Ave red and blue values, then put all pixel values in rgb
//            */
//           // Check our bounds. Start with best case for our average
//           if (row - 1 < 0) {
//             // Then we are on the first row. Can't index up a row
//             if (col - 1 < 0) {
//               // Then we are literally at the origin.
//               // Just use the value of the red square below
//               r = bayer[(row + 1) * width + col];
//               // Use the value of the blue square to the right
//               b = bayer[row * width + col + 1];
//             } else if (col + 1 >= width) {
//               // Then we are at the right edge of the image
//             } else {
//               // We are in the middle of a row
//             }
//           } else if (row + 1 >= height) {
//             // Then we are on the bottom row
//             if (col - 1 < 0) {
//               // Then we are literally at the origin
//             } else if (col + 1 >= width) {
//               // Then we are at the right edge of the image
//             } else {
//               // We are in the middle of a row
//             }
//           } else {
//             // Then we are in the middle of a column. We can move up or down
//             if (col - 1 < 0) {
//               // Then we are literally at the origin
//             } else if (col + 1 >= width) {
//               // Then we are at the right edge of the image
//             } else {
//               // We are in the middle of a row
//             }
//           }
