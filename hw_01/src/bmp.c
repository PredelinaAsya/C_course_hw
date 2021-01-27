#include "bmp.h"
#include "stdint.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"


const int bytes_on_pixel = 3;

int8_t** create_mat(int rows, int cols){
  int8_t** mat;
  mat = malloc(sizeof(int8_t*) * rows);
  assert(mat != NULL);
  
  for (int i = 0; i < rows; i++){
    mat[i] = malloc(sizeof(int8_t) * cols);
    assert(mat[i] != NULL);
  }
  
  return mat;
}

void free_mat(int8_t** mat, int rows){
  for (int i = 0; i < rows; i++){
    free(mat[i]);
  }
  free(mat);
}

void load_bmp(char *infile, struct picture *pict){
  FILE* fin = fopen(infile, "rb");
  assert(fin != NULL);
  
  size_t sz = fread(&pict->header, sizeof(struct FILEHEADER), 1, fin);
  assert(sz == 1);
  
  sz = fread(&pict->mapinfoheader, sizeof(struct FILEMAPINFOHEADER), 1, fin);
  assert(sz == 1);
  
  int rows = pict->mapinfoheader.height;
  int cols = bytes_on_pixel * (pict->mapinfoheader.width);
  if (cols % 4 != 0){
    cols += (4 - cols % 4);
  }
  pict->pixels = create_mat(rows, cols);
  
  fseek(fin, pict->header.offset, SEEK_SET);
  
  for (int i = 0; i < rows; i++){
    sz = fread(pict->pixels[i], sizeof(int8_t), cols, fin);
    assert(sz == cols);
  }
  
  fclose(fin);
}

int8_t** crop(struct picture *pict, int x, int y, int w, int h){
  int8_t** piece = create_mat(h, bytes_on_pixel * w);
  
  int H = pict->mapinfoheader.height;
  
  for (int i = 0; i < h; i++){
    memcpy(&piece[i][0], &pict->pixels[H - y - (h - i)][bytes_on_pixel * x],
           bytes_on_pixel * w);
  }
  
  return piece;
}

int8_t** rotate(int8_t** piece, int w, int h){
  int8_t** rot_picture = create_mat(w, 3 * h);
  
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      memcpy(&rot_picture[i][bytes_on_pixel * j],
             &piece[j][bytes_on_pixel * (w - i) - 3], 3);
    }
  }
  
  return rot_picture;
}

void save_bmp(char *outfile, struct picture *rt_pict, int w, int h){
  FILE* fout = fopen(outfile, "wb");
  assert(fout != NULL);
  
  rt_pict->mapinfoheader.width = w;
  rt_pict->mapinfoheader.height = h;
  
  rt_pict->header.offset = sizeof(struct FILEHEADER) +
                           sizeof(struct FILEMAPINFOHEADER);
  int delta = 0;
  if ((3 * w) % 4 != 0){
    delta = 4 - (3 * w) % 4;
  }
  rt_pict->mapinfoheader.sizeimage = h * (3 * w + delta);
  rt_pict->header.size = rt_pict->header.offset +
                         rt_pict->mapinfoheader.sizeimage;
  
  size_t sz = fwrite(&rt_pict->header, sizeof(struct FILEHEADER), 1, fout);
  assert(sz == 1);
  
  sz = fwrite(&rt_pict->mapinfoheader, sizeof(struct FILEMAPINFOHEADER),
              1, fout);
  assert(sz == 1);
  
  int8_t zeros[4] = {0};
  
  for (int i = 0; i < h; i++){
    sz = fwrite(rt_pict->pixels[i], sizeof(int8_t), 3 * w, fout);
    assert(sz == 3 * w);
    sz = fwrite(zeros, sizeof(int8_t), delta, fout);
    assert(sz == delta);
  }
  
  fclose(fout);
} 
