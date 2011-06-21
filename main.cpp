
#include "spectrum.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "surface.hpp"
#include "objects.hpp"
#include "world.hpp"

int main( int argc, char ** argv) {
   Spectrum * s = new WhiteSpectrum();

   RGB r = s->toRGB();

   World * w = new World(10, 10, 10);

   Object * o = new Sphere(Point(5,5,5), 2);

   return 0;
}
