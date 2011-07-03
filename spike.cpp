/**
 * spike.cpp
 *
 * Unit-type tests for various things.
 *
 * Author: Austin Hendrix
 */

#include "approximation.hpp"
#include <stdio.h>

int main(int argc, char ** argv) {
   Approximation a;
   a.addPoint(0, 0);
   a.addPoint(1, 1);
   a.addPoint(2, 2);
   a.addPoint(3, -1);

#define f(q) printf("%lf %lf\n", q, a(q))
   f(-1.0);
   f(-0.5);
   f(0.0);
   f(0.5);
   f(1.0);
   f(1.5);
   f(2.0);
   f(2.5);
   f(3.0);
   f(3.5);
   f(4.0);

   return 0;
}
