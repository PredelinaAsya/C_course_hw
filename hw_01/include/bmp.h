#ifndef __BMP_H__
#define __BMP_H__

#include "stdint.h"

#pragma pack(push, 1)
struct FILEHEADER{
  int16_t type;
  int32_t size;
  int16_t reserved1;
  int16_t reserved2;
  int32_t offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FILEMAPINFOHEADER{
  int32_t size;
  int32_t width;
  int32_t height;
  int16_t planes;
  int16_t bitcount;
  int32_t compression;
  int32_t sizeimage;
  int32_t XPelsPerMeter;
  int32_t YPelsPerMeter;
  int32_t ClrUsed;
  int32_t ClrImportant;
};
#pragma pack(pop)

struct picture{
  struct FILEHEADER header;
  struct FILEMAPINFOHEADER mapinfoheader;
  int8_t** pixels;
};

void free_mat(int8_t** mat, int rows);
void load_bmp(char *infile, struct picture *pict);
int8_t** crop(struct picture *pict, int x, int y, int w, int h);
int8_t** rotate(int8_t** piece, int w, int h);
void save_bmp(char *outfile, struct picture *rt_pict, /*struct FILEHEADER *header, 
              struct FILEMAPINFOHEADER *mapinfoheader, 
              int8_t** picture, */int w, int h);

#endif
