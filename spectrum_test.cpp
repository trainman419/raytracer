
#include <stdio.h>
#include <math.h>

#include <vector>

#include "spectrum.hpp"
#include "source.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "objects.hpp"
#include "world.hpp"
#include "png.hpp"
#include "optics.hpp"

// coordinates:
//
// z
// ^    y
// |   /
// |  /
// | /
// |/
// L------>x
//
// Rendering thoughts:
//  cast rays from each light source, and reflect them off of the objects in
//   the environment until magnitude is below some threshold
//  cast a ray for each pixel in the final image, until it intsersects with an 
//   object
//
//  reflection/diffusion: when a reflection from a source is diffuse, only
//   propagate either directly reflected rays or rays with magnitude above
//   some threshold
//  when a ray intsersects an object, calculate the ray from that point to the
//   light sources and compute diffuse reflection of light from that source?

int main( int argc, char ** argv) {
   // width, height and image buffer
   int w = 500; // do not make this 10
   int h = 50;
   char * image = (char*)malloc(sizeof(char)*w*h*3);
   if( !image ) {
      perror("malloc failed");
      return -1;
   }
   std::vector<fRGB> output;
   output.reserve(w);
   fRGB rgbmax(0.0, 0.0, 0.0);
   for( int x=0; x<w; x++ ) {
      Approximation a;
      a.addPoint(0.0, 0.0);
      a.addPoint(289 + x, 0.0);
      a.addPoint(290 + x, 1.0);
      a.addPoint(310 + x, 1.0);
      a.addPoint(311 + x, 0.0);
      a.addPoint(1000, 0.0);
      Spectrum s(a);
      fRGB rgb = s.tofRGB();
      output[x] = rgb;
      rgbmax.r = fmax(rgbmax.r, rgb.r);
      rgbmax.g = fmax(rgbmax.g, rgb.g);
      rgbmax.b = fmax(rgbmax.b, rgb.b);
   }

   for( int x=0; x<w; x++ ) {
      sRGB rgb(255 * (output[x].r / rgbmax.r), 255 * (output[x].g / rgbmax.g),
          255 * (output[x].b / rgbmax.b ));
      printf("->RGB %d %d %d\n", rgb.r, rgb.g, rgb.b);
      for( int y=0; y<h; y++ ) {
         // place RGB value into output image
         int k = (y*w + x)*3;
         image[k + 0] = rgb.r; // R
         image[k + 1] = rgb.g; // G
         image[k + 2] = rgb.b; // B
      }
   }

   FILE * out = fopen("spectrum.png", "wb");
   writePng(out, w, h, image);
   fclose(out);
   free(image);

   return 0;
}
