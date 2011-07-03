/**
 * approximation.cpp
 *
 * Piecewise linear approximation of a function.
 *
 * Author: Austin Hendrix
 */

#include "approximation.hpp"

#include <math.h>
#include <assert.h>

using namespace std;

double Approximation::operator()(const double x) const {
   map<double, double>::const_iterator itr;
   itr = f.lower_bound(x);
   // if x is explicitly in our representation, use it
   if( itr->first == x ) {
      //printf("Exact match for %lf\n", x);
      return itr->second;
   } else {
      // didn't find x in our table; approximate

      // x lower than anything in table; use lowest value
      if( itr == f.begin() ) {
         return itr->second;
      }

      // x higher than anything in table; use highest value
      if( itr == f.end() ) {
         itr--;
         return itr->second;
      }

      // linear approximation
      map<double, double>::const_iterator itr_down = itr;
      itr_down--;

      double slope = (itr->second - itr_down->second)/
         (itr->first - itr_down->first);
      assert(isfinite(slope));
      double res = slope * (x - itr_down->first) + itr_down->second;
      return res;
   }
}
