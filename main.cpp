
#include <stdio.h>
#include <math.h>

#include "spectrum.hpp"
#include "source.hpp"
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
   //Spectrum * s = new Source("color/illuminants/CIE-D65.txt");
   Spectrum * s = new Source("color/illuminants/CIE-C.txt");

   sRGB rgb = s->tosRGB();
   printf("D65->RGB %d %d %d\n", rgb.r, rgb.g, rgb.b);

   World * world = new World(10, 10, 10);

   Object * o = new Sphere(Point(0,10,0), 3);
   o->addToWorld(world);
   
   o = new Sphere(Point(2, 10, 2), 2);
   o->addToWorld(world);
   
   o = new Sphere(Point(-2, 10, -2), 2);
   o->addToWorld(world);

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
         // generate ray to cast
         Ray r(Point(x - w/2, 100, y - h/2));

         // cast ray and get rendered value
         rgb = world->trace(&r);

         // place RGB value into output image
         int k = (y*w + x)*3;
         image[k + 0] = rgb.r; // R
         image[k + 1] = rgb.g; // G
         image[k + 2] = rgb.b; // B
      }
   }

   writePng(out, w, h, image);
   fclose(out);
   free(image);

   return 0;
}
