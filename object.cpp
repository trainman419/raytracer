/**
 * Functions common to all objects
 *
 * Author: Austin Hendrix
 */

#include "object.hpp"

#include <stdio.h>

using namespace std;

void Object::addToWorld(World * w) {
   w->all.push_back(this);
   list<Object*> **** world = w->w;
   Point b_min = bound_min();
   Point b_max = bound_max();
   // explicitly round down
   for( int x = b_min.x; x < b_max.x; x++ ) {
      if( x >= 0 && x < w->x ) {
         for( int y = b_min.y; y < b_max.y; y++ ) {
            if( y >= 0 && y < w->y ) {
               for( int z = b_min.z; z < b_max.z; z++ ) {
                  if( z >= 0 && z < w->z ) {
                     if( occupy(x, y, z) ) {
                        world[x][y][z]->push_back(this);
                        //printf("(%d, %d, %d) is occupied)\n", x, y, z);
                     }
                  }
               }
            }
         }
      }
   }
}
