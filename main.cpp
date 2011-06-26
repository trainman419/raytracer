
#include <stdio.h>

#include "spectrum.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "objects.hpp"
#include "world.hpp"
#include "png.hpp"


int main( int argc, char ** argv) {
   Spectrum * s = new WhiteSpectrum();

   RGB r = s->toRGB();

   World * world = new World(10, 10, 10);

   Object * o = new Sphere(Point(5,5,5), 2);

   FILE * out = fopen("out.png", "wb");

   // width, height and image buffer
   int w = 100;
   int h = 100;
   char * image = (char*)malloc(sizeof(char)*w*h*3);
   if( !image ) {
      perror("malloc failed");
      return -1;
   }
   for( int i=0; i<h; i++ ) {
      for( int j=0; j<w; j++ ) {
         int k = (i*w + j)*3;
         image[k + 0] = 255; // R
         image[k + 1] =   0; // G
         image[k + 2] =   0; // B
      }
   }

   writePng(out, w, h, image);
   fclose(out);
   free(image);

   return 0;
}
