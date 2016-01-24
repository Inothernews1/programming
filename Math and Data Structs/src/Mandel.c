#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char input[256];

char* colors [17] = {
  "  0   0   0 ",
  " 57  57  57 ",
  "157 157 157 ",
  "190  38  51 ",
  "224 111 139 ",
  " 73  60  43 ",
  "235 100  34 ",
  "247 226 107 ",
  " 47  72  78 ",
  " 68 137  26 ",
  "163 206  39 ",
  " 27  38  50 ",
  "  0  87 132 ",
  " 49 162 242 ",
  "178 220 239 ",
  "255   0 255 ",
  "255 255 255 ",
};

int main(int argc, char** argv) {
  // Print 'Image height? ' to stdout
  fputs("Image height? ", stdout);
  // Look in stdin stream, up to 256 - 1 chars, and store it in input
  fgets(input, 256, stdin);
  // Declare a type char* for us to store the non number part of the input
  char *ptr;

  // Store the part of the input that was a number as a double into imHei
  double imHei = strtod(input, &ptr);

  // Reapeat for imHei
  fputs("Image width? ", stdout);
  fgets(input, 256, stdin);

  double imWid = strtod(input, &ptr);

  FILE * imPoi;
  imPoi = fopen("Mandel.ppm", "w");
  fprintf(imPoi, "P3\n%g %g\n255\n", imHei, imWid);

  double minRe = -2.0;
  double maxRe = 1.0;
  double minIm = -1.2;
  // No y-axis stretching
  double maxIm = (minIm + (maxRe - minRe) * imHei / imWid);
  // Precalulated
  double reFactor = (maxRe - minRe) / (imWid - 1);
  double imFactor = (maxIm - minIm) / (imHei - 1);
  unsigned maxIterations = 16;

  for(unsigned y = 0; y < imHei; y++) {
    // Get the i part of the complex number as y-axis
    double c_Im = maxIm - y * imFactor;

    for(unsigned x = 0; x < imWid; x++) {
      // Get the real part of the complex number as x-axis
      double c_Re = minRe + x * reFactor;

      double z_Re = c_Re;
      double z_Im = c_Im;
      bool isInside = true;

      for(unsigned n = 0; n < maxIterations; n++) {
        double z_Re2 = z_Re * z_Re;
        double z_Im2 = z_Im * z_Im;

        if(z_Re2 + z_Im2 > 4) {
          isInside = false;
          fprintf(imPoi, "%s", colors[n + 1]);
          break;
        }

        z_Im = 2 * z_Re * z_Im + c_Im;
        z_Re = z_Re * z_Re - z_Im2 + c_Re;

      }

      if (isInside) {
        fprintf(imPoi, "%s", colors[0]);
      }

    }

  }

  fclose(imPoi);

  return 0;
}
