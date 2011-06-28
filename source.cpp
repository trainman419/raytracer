/**
 * Implementation of standard CIE light sources
 *
 * Author: Austin Hendrix
 */

#include "source.hpp"

#include <fstream>
#include <errno.h>

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

Source::Source(string fname) {
   ifstream in(fname.c_str());
   if( !in ) {
      perror(("Failed to open " + fname).c_str());
   } else {
#ifdef DEBUG
      cout << "Reading source from " << fname << endl;
#endif
      bool spect = false;
      string line;
      while( in && !spect ) {
         getline(in, line);
         spect = line.find("Spectrum") != string::npos;
      }
      double wvl;
      double i;
      while( in ) {
         in >> wvl >> i;
         I[wvl] = i;
#ifdef DEBUG
         cout << "wvl: " << wvl << ", I: " << i << endl;
#endif
      }
   }
}
