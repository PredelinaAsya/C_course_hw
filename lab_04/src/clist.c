#include "clist.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"


void init_list(struct intrusive_list *list){
  list->head = NULL;
}

void add_node(struct intrusive_list *list, struct intrusive_node *node){
  node->prev = list->head;
  if (list->head != NULL){
    list->head->next = node;
  }
  node->next = NULL;
  list->head = node;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node){
  if (node->prev != NULL){
    node->prev->next = node->next;
  }
  if (node->next != NULL){
    node->next->prev = node->prev;
  }
  if (list->head == node){
    list->head = node->prev;
  }
}

int get_length(struct intrusive_list *list){
  struct intrusive_node *curr_node = list->head;
  int len = 0;
  
  while (curr_node != NULL){
    len++;
    curr_node = curr_node->prev;
  }
  
  return len;
}
