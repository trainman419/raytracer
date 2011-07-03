/**
 * CIE standard light sources
 *
 * Author: Austin Hendrix
 * Based on CIE source profiles from OpenFilters
 *
 * TODO: extend this to describe the shape of the light source
 */

#ifndef SOURCE_H
#define SOURCE_H

#include "spectrum.hpp"
#include <string>

// a spectrum that can be read from a file
class Source : public Spectrum {
   public:
      virtual ~Source() {}
};

class FileSource : public Source {
   public:
      FileSource(std::string fname);

      virtual ~FileSource() {}
};

class WhiteSource : public Source {
   public:
      virtual sRGB tosRGB() { return sRGB(255, 255, 255); }
      virtual ~WhiteSource() {}
};

#endif
