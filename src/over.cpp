#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  /**
   * "Over" is the Porter-Duff algorithm found at
   * https://en.wikipedia.org/wiki/Alpha_compositing
   */
  double r, g, b, alpha;
  double a_r, a_g, a_b, a_alpha, b_r, b_g, b_b, b_alpha;
  int pxl_idx = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      // Get the rgb subpixel colors in A and B
      a_r = (double) A[4 * (row * width + col) + 0];
      a_g = (double) A[4 * (row * width + col) + 1];
      a_b = (double) A[4 * (row * width + col) + 2];
      a_alpha = ((double) A[(row * width + col) * 4 + 3]) / 255.0;

      b_r = (double) B[(row * width + col) * 4 + 0];
      b_g = (double) B[(row * width + col) * 4 + 1];
      b_b = (double) B[(row * width + col) * 4 + 2];
      b_alpha = ((double) B[(row * width + col) * 4 + 3]) / 255.0;

      // Determine the new rgba values for C
      alpha = a_alpha + (b_alpha * (1.0 - a_alpha));
      r = ((a_r * a_alpha) + (b_r * b_alpha) * (1.0 - a_alpha)) / alpha;
      g = ((a_g * a_alpha) + (b_g * b_alpha) * (1.0 - a_alpha)) / alpha;
      b = ((a_b * a_alpha) + (b_b * b_alpha) * (1.0 - a_alpha)) / alpha;

      // Set the values in C
      C[pxl_idx++] = (unsigned char) r;
      C[pxl_idx++] = (unsigned char) g;
      C[pxl_idx++] = (unsigned char) b;
      C[pxl_idx++] = (unsigned char) (alpha * 255.0);
    }
  }


  // Single loop version with indexes
  // double r, g, b, alpha;
  // double a_r, a_g, a_b, a_alpha, b_r, b_g, b_b, b_alpha;
  // int pxl_idx = 0, a_idx = 0, b_idx = 0;
  // for (int subpxl = 0; subpxl < width * height; subpxl++) {
  //   // Get the rgb subpixel colors in A and B
  //   a_r = (double) A[a_idx++];
  //   a_g = (double) A[a_idx++];
  //   a_b = (double) A[a_idx++];
  //   a_alpha = ((double) A[a_idx++]) / 255.0;

  //   b_r = (double) B[b_idx++];
  //   b_g = (double) B[b_idx++];
  //   b_b = (double) B[b_idx++];
  //   b_alpha = ((double) B[b_idx++]) / 255.0;

  //   // Determine the new rgba values for C
  //   alpha = a_alpha + (b_alpha * (1.0 - a_alpha));
  //   r = ((a_r * a_alpha) + (b_r * b_alpha) * (1.0 - a_alpha)) / alpha;
  //   g = ((a_g * a_alpha) + (b_g * b_alpha) * (1.0 - a_alpha)) / alpha;
  //   b = ((a_b * a_alpha) + (b_b * b_alpha) * (1.0 - a_alpha)) / alpha;

  //   // Set the values in C
  //   C[pxl_idx++] = (unsigned char) r;
  //   C[pxl_idx++] = (unsigned char) g;
  //   C[pxl_idx++] = (unsigned char) b;
  //   C[pxl_idx++] = (unsigned char) (alpha * 255.0);
  // }
  ////////////////////////////////////////////////////////////////////////////
}
