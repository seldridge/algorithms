#ifndef __TREE_H__
#define __TREE_H__

#include <stdint.h>

typedef struct node node;

typedef struct node {
  node * left;
  node * right;
  uint32_t data;
} node;

void tree_insert(node *, node *);

void tree_create(node **, uint32_t);
void tree_destroy(node **);

void traverse_in_order(node * root, void (*function)(node *));
void traverse_pre_order(node * root, void (*function)(node *));
void traverse_post_order(node * root, void (*function)(node *));

#endif
