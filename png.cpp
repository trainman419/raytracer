/**
 * a simpile interface to libpng
 *
 * Using libpng 1.4; see: http://www.libpng.org/pub/png/libpng-1.4.0-manual.pdf
 *
 * Author: Austin Hendrix
 */

#include <stdlib.h>
#include <png.h>
#include "png.hpp"

// write 24-bit image data to a file
int writePng(FILE * fp, int w, int h, char * data) {
   // set up row pointers
   png_byte ** row_pointers = (png_byte**)malloc(h*png_sizeof(png_bytep));
   if( !row_pointers ) {
      return -1;
   }
   for( int i=0; i<h; i++ ) {
      row_pointers[i] = (png_byte*)(data + i*w*3);
   }

   // set up png structures
   png_structp png_ptr = png_create_write_struct(
         PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
   if(!png_ptr)
      return -1;

   png_infop info_ptr = png_create_info_struct(png_ptr);
   if(!info_ptr) {
      png_destroy_write_struct(&png_ptr, (png_infopp)NULL);

      return -1;
   }

   // set up error-handling
   if( setjmp(png_jmpbuf(png_ptr)) ) {
      png_destroy_write_struct(&png_ptr, &info_ptr);
      return -1;
   }

   png_init_io(png_ptr, fp);

   // set up width, height, RGB with 8-bits/color
   png_set_IHDR(png_ptr, info_ptr, w, h, 8, PNG_COLOR_TYPE_RGB,
         PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
         PNG_FILTER_TYPE_DEFAULT);

   png_set_rows(png_ptr, info_ptr, row_pointers);

   png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

   // clean up
   png_destroy_write_struct(&png_ptr, &info_ptr);
   free(row_pointers);

   return 0;
}
