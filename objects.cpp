/**
 * obejcts.cpp: implementation of basic object classes
 *
 * Author: Austin Hendrix
 */

#include "objects.hpp"

using namespace std;

// sphere

// get the first intersection point of a ray with this sphere
Point * Sphere::intersect(Ray * in) {
   Point p1 = in->getStart(); // P1
   Point d = in->getDir();    // P2 - P1
   // c                       // P3
   // From: http://paulbourke.net/geometry/sphereline/
   // u*d + p1 = closest point to c
   /*double u = ( (c.x - p1.x)*d.x + (c.y - p1.y)*d.y + (c.z - p1.z)*d.z ) /
      ( d.x*dx + d.y*d.y + d.z*d.z );
   // u > 0 implies point is on forward part of ray
   if( u > 0 ) {
      Point p;
      p.x = u*d.x + p1.x;
      p.y = u*d.y + p1.y;
      p.z = u*d.z + p1.z;
      // distance from point to center of sphere
      double dist = p.x*p.x + p.y*p.y + p.z*p.z;
      // if distance is within the sphere we actually have intersection
      if( dist <= r ) {
         // re-solve for values of u that are on surface of sphere
      }
   }*/
   double a = d.x*d.x + d.y*d.y + d.z*d.z;
   double b = 2 * (d.x*(p1.x-c.x) + d.y*(p1.y-c.y) + d.z*(p1.z-c.z) );
   double cc = c.x*c.x + c.y*c.y + c.z*c.z + p1.x*p1.x + p1.y*p1.y + 
      p1.z*p1.z - 2*(c.x*p1.x + c.y*p1.y + c.z*p1.z) - r*r;
   double root = b*b - 4*a*cc;
   // if root < 0; no intersection
   if( root < 0 ) {
      return NULL;
   } else if( root == 0.0 ) {
      // one root; one intersection
   } else {
      // two roots; two intersections. pick the closer one
   }
   return NULL;
}

// get the angle of intersection with the surface
double angle(Ray *) {
}

// get the reflected ray off of this sphere
Ray * Sphere::reflect(Ray * in) {
   Point * i = intersect(in);
   if( i ) {
      // intersects with sphere. get angle, do math, etc
   }
   return new Ray();
}

Ray * Sphere::transmit(Ray * in) {
   Point * i = intersect(in);
   if( i ) {
   }
   return new Ray();
}

Ray * Sphere::absorb(Ray * in) {
   Point * i = intersect(in);
   if( i ) {
   }
   return new Ray();
}

void Sphere::addToWorld(World * w) {
}
