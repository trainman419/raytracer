/**
 * A thin-film filter modeling program to test the optics library
 *
 * Author: Austin Hendrix
 */

#include "optics.hpp"
#include "source.hpp"

#include <stdio.h>

int main(int argc, char ** argv) {
   Film * film = new Film();
   Index * i1 = new FixedIndex(1.5);
   Index * i2 = new FixedIndex(2.2);

   double thick;
   if( argc == 2 ) {
      sscanf(argv[1], "%lf", &thick);
   } else {
      printf("Usage: model <thickness>\n");
      return -1;
   }

   film->addLayer(Layer(thick, i1));
   film->addLayer(Layer(thick*2, i2));
   film->addLayer(Layer(thick, i1));

   Spectrum * s;
   s = film->reflect(new WhiteSpectrum(), 0);
//   s = new FileSource("color/illuminants/CIE-A.txt");
   Spectrum::const_iterator itr;
   for( itr = s->begin(); itr != s->end(); ++itr ) {
      printf("%06lf %06lf\n", *itr, s->get(*itr));
   }

   sRGB color = s->tosRGB();

   //printf("RGB: %d %d %d\n", color.r, color.g, color.b);
   return 0;
}
