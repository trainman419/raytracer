/**
 *
 * Author: Austin Hendrix
 */

#include <math.h>
#include <fstream>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif

#include "spectrum.hpp"

using namespace std;

fRGB max(const fRGB & a, const fRGB & b) {
  return fRGB(max(a.r, b.r), max(a.g, b.g), max(a.b, b.b));
}


double Spectrum::INC = 1.0;

fRGB Spectrum::tofRGB() {
   double itr;
   double X = 0.0;
   double Y = 0.0;
   double Z = 0.0;
   for( itr = I.min(); itr <= I.max(); itr += INC ) {
      Observer::f func = Observer::bar2(itr);
      X += func.x * I(itr);
      Y += func.y * I(itr);
      Z += func.z * I(itr);
   }

   // if any values greater than 1.0, normalize
   /*
   if( X > 1.0 || Y > 1.0 || Z > 1.0 ) {
      double norm = max( X, max(Y, Z));
      X /= norm;
      Y /= norm;
      Z /= norm;
   }
   */

   // conversion from CIE XYZ to sRGB
   double C[3];
   C[0] =  3.2406*X - 1.5372*Y - 0.4986*Z;
   C[1] = -0.9686*X + 1.8758*Y + 0.0415*Z;
   C[2] =  0.0557*X - 0.2040*Y + 1.0570*Z;
   double a = 0.055;
   for( int i=0; i<3; i++ ) {
      if( C[i] > 0.0031308 ) {
         C[i] = (1 + a)*pow(C[i], 1/2.4) - a;
      } else {
         C[i] = 12.92*C[i];
      }
      if( C[i] < 0 ) C[i] = 0.0;
   }

   return fRGB(C[0], C[1], C[2]);
}

sRGB Spectrum::tosRGB() {
  // normalize fRGB
  fRGB f = tofRGB();
  double m = max(f.r, max( f.g, f.b ));
  return sRGB( 255 * (f.r / m), 255 * (f.g / m), 255 * (f.b / m));
}

// Observer helper class
Observer * Observer::t;

Observer::Observer() {
   // construct function table by reading file
   ifstream in("color/observers/CIE-1931-1nm.txt");
#ifdef DEBUG
   cout << "Initializing Observer" << endl;
#endif
   bool found = false;
   string s;
   while( in && !found ) {
      getline(in, s);
      found = s.find("Functions:") == 0;
   }
   f line;
   int wvl;
   while( in ) {
      in >> wvl;
      in >> line.x;
      in >> line.y; 
      in >> line.z;
#ifdef DEBUG
      printf("wvl: %d: %.4f, %.4f, %.4f\n", wvl, line.x, line.y, line.z);
      /*cout << "wvl: " << wvl << ": " << line.x << ", " << line.y <<
        ", " << line.z << endl;*/
#endif
      func[wvl] = line;
   }
}

Observer::f Observer::bar2(int wvl) {
   init();
   if( t->func.find(wvl) != t->func.end() ) {
      return t->func[wvl];
   } else {
      f res = {0, 0, 0};
      return res;
   }
}
