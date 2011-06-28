/**
 * world.cpp: Implementation of the world
 *
 * Author: Austin Hendrix
 */

#include "world.hpp"

using namespace std;

World::World(int dx, int dy, int dz) {
   w = new list<Object*>***[dx];
   for( int i=0; i<dx; i++ ) {
      w[i] = new list<Object*>**[dy];
      for( int j=0; j<dy; j++ ) {
         w[i][j] = new list<Object*>*[dz];
         for( int k=0; k<dz; k++ ) {
            w[i][j][k] = new list<Object*>();
         }
      }
   }
   x = dx;
   y = dy;
   z = dz;

   min_light = 1.0;  // arbitrary
   min_ray = 0.1;    // 10%
}

World::~World() {
   for( int i=0; i<x; i++ ) {
      for( int j=0; j<y; j++ ) {
         for( int k=0; k<z; k++ ) {
            delete w[i][j][k];
         }
         delete w[i][j];
      }
      delete w[i];
   }
   delete w;
}

list<Object*> * World::getObjects(int x, int y, int z) {
   return w[x][y][z];
}

void World::light(Source * s) {
   lights.push_back(s);
}

sRGB World::trace(Ray * r) {
   // trace a ray through the world
   int x, y, z;
   Point start = r->getStart();
   // truncate down
   x = start.x;
   y = start.y;
   z = start.z;
   list<Object*> * objects = w[x][y][z];
}
