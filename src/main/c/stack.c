#include "stack.h"

int stackCreate(stack_t ** s, uint32_t size) {
  if (size == 0)
    return -1;

  *s = (stack_t *) malloc(sizeof(stack_t));
  if (*s == NULL)
    return -2;

  (*s)->data = NULL;
  (*s)->data = (uint32_t *) malloc(size * sizeof(uint32_t));
  if ((*s)->data == NULL)
    return -3;

  (*s)->top = 0;
  (*s)->size = size;
  return 0;
}

void stackDestroy(stack_t ** s) {
  free((*s)->data);
  free(*s);
}

int stackPush(stack_t * s, uint32_t data) {
  if (s->top == s->size)
    return -1;
  s->data[s->top++] = data;
  return 0;
}

int stackPop(stack_t * s, uint32_t * data) {
  if (s->top == 0)
    return -1;
  *data = s->data[--s->top];
  return 0;
}

int stackPrint(stack_t * s) {
  if (s == NULL || s->data == NULL)
    return -1;
  for (uint32_t i = 0; i < s->size; i++)
    printf("%2d|", s->data[i]);
  printf("\n");

  for (uint32_t i = 0; i < s->size; i++) {
    if (s->top == i) printf("_t|");
    else             printf("__|");
  }

  if (s->top == s->size)      printf("t");
  else                        printf(" ");

  if (s->top == 0)            printf("e");
  else if (s->top == s->size) printf("f");
  printf("\n");
  return 0;
}
