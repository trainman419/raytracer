/**
 * Functions common to all objects
 *
 * Author: Austin Hendrix
 */

#include "object.hpp"

using namespace std;

void Object::addToWorld(World * w) {
   w->all.push_back(this);
   list<Object*> **** world = w->w;
   Point b_min = bound_min();
   Point b_max = bound_max();
   for( int x = b_min.x; x < b_max.x; x++ ) {
      if( x >= 0 && x < w->x ) {
         for( int y = b_min.y; y < b_max.y; y++ ) {
            if( y >= 0 && y < w->y ) {
            }
         }
      }
   }
}
