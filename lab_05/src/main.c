#include "point_list.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"


void add_one(intrusive_node *node, void *curr){
  int z = *(int *)curr + 1;
  *(int *)curr = z;
}

void loadtext(char *infile, intrusive_list *list){
  FILE* fin = fopen(infile, "r");
  int x, y;
  while (fscanf(fin, "%d %d", &x, &y) == 2){
    add_point(list, x, y);
  }
  fclose(fin);
}

void loadbin(char *infile, intrusive_list *list){
  FILE* fin = fopen(infile, "rb");
  unsigned char arr[6];
  int x, y;
  while (fread(arr, 1, 6, fin)){
     x = arr[0] | (arr[1] << 8) | (arr[2] << 16);
     if (arr[2] >= 128){
       x -= 1;
       x = ~x;
       x &= (255 | (255 << 8) | (255 << 16));
       x = -x;
     }
     y = arr[3] | (arr[4] << 8) | (arr[5] << 16);
     if (arr[5] >= 128){
       y -= 1;
       y = ~y;
       y &= (255 | (255 << 8) | (255 << 16));
       y = -y;
     }
     add_point(list, x, y);
  }
  fclose(fin);
}

void save_txt_pair(intrusive_node *node, void *fout){
  point_node *curr_point = get_point(node);
  fprintf(fout, "%d %d\n", curr_point->x, curr_point->y);
}

void savetext(char *outfile, intrusive_list *list){
  FILE* fout = fopen(outfile, "w");
  apply(list, save_txt_pair, fout);
  fclose(fout);
}

void save_bin_pair(intrusive_node *node, void *fout){
  point_node *curr_point = get_point(node);
  int x = curr_point->x;
  int y = curr_point->y;
  unsigned char x_0, x_1, x_2, y_0, y_1, y_2;
  if (x < 0){
    x_0 = ~(255 & abs(x));
    x_1 = ~(255 & (abs(x) >> 8));
    x_2 = ~(255 & (abs(x) >> 16));
    x = x_0 | (x_1 << 8) | (x_2 << 16);
    x += 1;
  }
  x_0 = 255 & x;
  x_1 = 255 & (x >> 8);
  x_2 = 255 & (x >> 16);
  if (y < 0){
    y_0 = ~(255 & abs(y));
    y_1 = ~(255 & (abs(y) >> 8));
    y_2 = ~(255 & (abs(y) >> 16));
    y = y_0 | (y_1 << 8) | (y_2 << 16);
    y += 1;
  }
  y_0 = 255 & y;
  y_1 = 255 & (y >> 8);
  y_2 = 255 & (y >> 16);
  unsigned char out_arr[6] = {x_0, x_1, x_2, y_0, y_1, y_2};
      
  fwrite(out_arr, 1, 6, fout);
}

void savebin(char *outfile, intrusive_list *list){
  FILE* fout = fopen(outfile, "wb");
  apply(list, save_bin_pair, fout);
  fclose(fout);
}

void print_frm_point(intrusive_node *node, void *format){
  char *frm = format;
  point_node *pnode = get_point(node);
  printf(frm, pnode->x, pnode->y);
}

int main(int argc, char* argv[]){

  assert(argc >= 4);

  struct intrusive_list list;
  init_list(&list);
  
  char* file_type = argv[1];
  char* infile = argv[2];
  char* action = argv[3];

  if (strcmp(file_type, "loadtext") == 0) {
    loadtext(infile, &list);
  }
  
  if (strcmp(file_type, "loadbin") == 0) {
    loadbin(infile, &list);
  }
  
  if (strcmp(action, "savetext") == 0 || strcmp(action, "savebin") == 0) {
    assert(argc == 5);
    char* outfile = argv[4];
    
    if (strcmp(action, "savetext") == 0) {
      savetext(outfile, &list);
    }
    
    if (strcmp(action, "savebin") == 0) {
      savebin(outfile, &list);
    }
  }
  
  if (strcmp(action, "print") == 0) {
    assert(argc == 5);
    char* format = argv[4];
    apply(&list, print_frm_point, format);
    printf("\n");
  }
  
  if (strcmp(action, "count") == 0) {
    assert(argc == 4);
    int len = 0;
    apply(&list, add_one, &len);
    printf("%d\n", len);
  }
  
  remove_all_points(&list);
  
}
