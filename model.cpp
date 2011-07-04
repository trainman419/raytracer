/**
 * A thin-film filter modeling program to test the optics library
 *
 * Author: Austin Hendrix
 */

#include "optics.hpp"
#include "source.hpp"

#include <math.h>
#include <stdio.h>

//#define f(a) log(-log(a))
#define f(a) (a)

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

   /*
   for( int i=0; i<10; i++ ) {
      double q = 1.0 + ((i-5.0)/10.0);
      q /= 4.0;
      fprintf(stderr, "%05.3lf %03.0lf\n", q, thick);
      film->addLayer(Layer(q*thick/1.5, i1));
      film->addLayer(Layer(q*2*thick/2.2, i2));
      film->addLayer(Layer(q*thick/1.5, i1));
   }
   */
   film->addLayer(Layer(thick/2/2.2, i2));

   //film->print();
   //return 0;

   Spectrum * s;
   s = new FileSource("color/illuminants/CIE-C.txt");
   s = film->reflect(s, 0);
   Spectrum::const_iterator itr;
   for( itr = s->begin(); itr != s->end(); ++itr ) {
      printf("%09lf %09lf\n", *itr, f(s->get(*itr)));
   }

   sRGB color = s->tosRGB();

   //printf("RGB: %d %d %d\n", color.r, color.g, color.b);
   return 0;
}
