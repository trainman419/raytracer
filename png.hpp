/**
 * Interface to libpng for writing final images to file.
 *
 * Author: Austin Hendrix
 */

#ifndef PNG_H
#define PNG_H

#include <stdio.h>

// write 24-bit image data to a file
//  image data in RGB order?
int writePng(FILE * fp, int w, int h, char * data);

#endif
