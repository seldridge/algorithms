#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

void tree_create(node ** tree, uint32_t data) {
  (*tree) = (node*) malloc(sizeof(node));
  (*tree)->left = NULL;
  (*tree)->right = NULL;
  (*tree)->data = data;
  printf("Creating tree\n  - data: %d\n  - addres: 0x%p\n", (*tree)->data, *tree);
}

void tree_destroy(node ** tree) {
  if ((*tree)->left != NULL) {
    tree_destroy(&((*tree)->left));
  }
  if ((*tree)->right != NULL) {
    tree_destroy(&((*tree)->right));
  }
  printf("Freeing tree\n  - data: %d\n  - addres: 0x%p\n", (*tree)->data, *tree);
  free(*tree);
}

void tree_insert(node * tree, node * newNode) {
  if (newNode->data < tree->data) {
    if (tree->left == NULL) {
      tree->left = newNode;
    } else {
      tree_insert(tree->left, newNode);
    }
  } else if (newNode->data > tree->data) {
    if (tree->right == NULL) {
      tree->right = newNode;
    } else {
      tree_insert(tree->right, newNode);
    }
  }
}

void traverse_in_order(node * root, void (*function)(node *)) {

  if (root->left != NULL)
    traverse_in_order(root->left, function);

  if (function != NULL)
    function(root);

  if (root->right != NULL)
    traverse_in_order(root->right, function);

}

void traverse_pre_order(node * root, void (*function)(node *)) {

  if (function != NULL)
    function(root);

  if (root->left != NULL)
    traverse_in_order(root->left, function);

  if (root->right != NULL)
    traverse_in_order(root->right, function);

}

void traverse_post_order(node * root, void (*function)(node *)) {

  if (root->left != NULL)
    traverse_in_order(root->left, function);

  if (root->right != NULL)
    traverse_in_order(root->right, function);

  if (function != NULL)
    function(root);

}
