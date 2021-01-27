#include "bmp.h"
#include "stdlib.h"
#include "stdint.h"
#include "assert.h"


int main(int argc, char* argv[]){
  assert(argc == 8);
  
  char* infile = argv[2];
  char* outfile = argv[3];
  int x = atoi(argv[4]);
  int y = atoi(argv[5]);
  int w = atoi(argv[6]);
  int h = atoi(argv[7]);
  assert(0 <= x);
  assert(x < x + w);
  assert(0 <= y);
  assert(y < y + h);
  
  struct picture pict;
  
  load_bmp(infile, &pict);
  int W = pict.mapinfoheader.width;
  int H = pict.mapinfoheader.height;
  assert(x + w <= W);
  assert(y + h <= H);
  
  int8_t** piece = crop(&pict, x, y, w, h);
  int8_t** rot_pixels = rotate(piece, w, h);
  
  struct picture rt_pict;
  rt_pict.header = pict.header;
  rt_pict.mapinfoheader = pict.mapinfoheader;
  rt_pict.pixels = rot_pixels;
  
  save_bmp(outfile, &rt_pict, h, w);
  
  free_mat(pict.pixels, H);
  free_mat(piece, h);
  free_mat(rot_pixels, w);
}
