
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
   //Source * s = new FileSource("color/illuminants/CIE-D65.txt");
   Source * s = new FileSource("color/illuminants/CIE-C.txt");
   //Source * s = new FileSource("color/illuminants/CIE-A-1nm.txt");
   //Source * s = new WhiteSource();

   fRGB rgb = s->tofRGB();
   fRGB rgbmax(0.0, 0.0, 0.0);
   printf("->RGB %f %f %f\n", rgb.r, rgb.g, rgb.b);

   World * world = new World(20, 20, 20);

   Film * f = new Film();
   Index * i1 = new FixedIndex(1.3);
   Index * i2 = new FixedIndex(1.5);
   /*
   f->addLayer(Layer(50.0, i1));
   f->addLayer(Layer(100.0, i2));
   f->addLayer(Layer(50.0, i1));
   */
   /*
   f->addLayer(Layer(250/1.5, i2));
   */
   f = new FakeFilm();

   world->light(s);

   Sphere * o = new Sphere(Point(10,10,10), 3);
   o->setFilm(f);
   o->addToWorld(world);
   
   o = new Sphere(Point(14, 15, 14), 2);
   o->addToWorld(world);
   
   o = new Sphere(Point(6, 15, 6), 2);
   o->addToWorld(world);

   FILE * out = fopen("out.png", "wb");

   // width, height and image buffer
   int w = 100; // do not make this 10
   if( argc > 1 ) sscanf(argv[1], "%d", &w);
   int h = w;
   fRGB * f_image = (fRGB*)malloc(sizeof(fRGB)*w*h);
   char * image = (char*)malloc(sizeof(char)*w*h*3);
   if( !image || !f_image ) {
      perror("malloc failed");
      return -1;
   }
   for( int y=0; y<h; y++ ) {
      printf("Rendering row %d\n", y);
      for( int x=0; x<w; x++ ) {
         //printf("Rendering (%d, %d)\n", x, y);
         // generate ray to cast
         //  depth here determines field-of-view
         Ray r(Point(10, 0, 10), Point(x - w/2, (w+h)/2, y - h/2));

         // cast ray and get rendered value
         rgb = world->trace(&r);
         rgbmax = max(rgbmax, rgb);
         f_image[y*w + x] = rgb;
      }
   }

   for( int y=0; y<h; y++ ) {
      for( int x=0; x<w; x++ ) {
         rgb = f_image[y*w + x];
         // place RGB value into output image
         int k = (y*w + x)*3;
         image[k + 0] = 255 * (rgb.r / rgbmax.r); // R
         image[k + 1] = 255 * (rgb.g / rgbmax.g); // G
         image[k + 2] = 255 * (rgb.b / rgbmax.b); // B
      }
   }

   writePng(out, w, h, image);
   fclose(out);
   free(image);

   return 0;
}
