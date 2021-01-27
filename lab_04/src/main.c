#include "clist.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"


struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y){
  struct point *new_point = malloc(sizeof(struct point));
  new_point->x = x;
  new_point->y = y;
  add_node(list, &new_point->node);
}

void remove_point(struct intrusive_list *list, int x, int y){
  // removes all (x, y) pairs
  struct intrusive_node *curr_node = list->head;

  while (curr_node != NULL) {
    struct point *curr_point = container_of(curr_node, struct point, node);
    struct intrusive_node *prev_node = curr_node->prev;
    if (curr_point->x == x && curr_point->y == y) {
      remove_node(list, curr_node);
      free(curr_point);
    }
    curr_node = prev_node;
  }

}

void show_all_points(struct intrusive_list *list) {
  struct intrusive_node *curr_node = list->head;
  int len = get_length(list);

  for (int i = 0; i < len; i++) {
    struct point *curr_point = container_of(curr_node, struct point, node);
    printf("(%d %d)", curr_point->x, curr_point->y);
    if (i != len - 1) {
      printf(" ");
    }
    curr_node = curr_node->prev;
  }
  printf("\n");
}

void remove_all_points(struct intrusive_list *list) {
  struct intrusive_node *curr_node = list->head;
  int len = get_length(list);

  for (int i = 0; i < len; i++) {
    struct point *curr_point = container_of(curr_node, struct point, node);
    struct intrusive_node *prev_node = curr_node->prev;
    remove_node(list, curr_node);
    free(curr_point);
    curr_node = prev_node;
  }

}

int main(){

  struct intrusive_list list;
  init_list(&list);

  char comm[240];
  while (scanf("%239s", comm)) {
    if (strcmp(comm, "add") == 0) {
      int x, y;
      scanf("%d", &x);
      scanf("%d", &y);
      add_point(&list, x, y);
      continue;
    }

    if (strcmp(comm, "rm") == 0) {
      int x, y;
      scanf("%d", &x);
      scanf("%d", &y);
      remove_point(&list, x, y);
      continue;
    }

    if (strcmp(comm, "print") == 0) {
      show_all_points(&list);
      continue;
    }

    if (strcmp(comm, "rma") == 0) {
      remove_all_points(&list);
      continue;
    }

    if (strcmp(comm, "len") == 0) {
      printf("%d\n", get_length(&list));
      continue;
    }

    if (strcmp(comm, "exit") == 0) {
      remove_all_points(&list);
      return 0;
    }

    printf("Unknown command\n");
  }
  
}
