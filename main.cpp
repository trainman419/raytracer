
#include <stdio.h>

#include "spectrum.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "objects.hpp"
#include "world.hpp"
#include "png.hpp"

// coordinates:
//
// z
// ^    y
// |   /
// |  /
// | /
// |/
// L------>x

int main( int argc, char ** argv) {
   Spectrum * s = new WhiteSpectrum();

   RGB r = s->toRGB();

   World * world = new World(10, 10, 10);

   Object * o = new Sphere(Point(0,10,0), 4);

   FILE * out = fopen("out.png", "wb");

   // width, height and image buffer
   int w = 100;
   int h = 100;
   char * image = (char*)malloc(sizeof(char)*w*h*3);
   if( !image ) {
      perror("malloc failed");
      return -1;
   }
   for( int y=0; y<h; y++ ) {
      for( int x=0; x<w; x++ ) {
         int k = (y*w + x)*3;

         Ray r(Point(x - w/2, 100, y - h/2));

         if( o->collide(&r) ) {
            image[k + 0] =   0; // R
            image[k + 1] = 255; // G
            image[k + 2] =   0; // B
         } else {
            image[k + 0] =   0; // R
            image[k + 1] =   0; // G
            image[k + 2] =   0; // B
         }
      }
   }

   writePng(out, w, h, image);
   fclose(out);
   free(image);

   return 0;
}
