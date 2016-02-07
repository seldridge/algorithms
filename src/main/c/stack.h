#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  uint32_t * data;
  uint32_t top;
  uint32_t size;
} stack_t;

int stackCreate(stack_t ** s, uint32_t size);
void stackDestroy(stack_t ** s);

int stackPush(stack_t * s, uint32_t data);
int stackPop(stack_t * s, uint32_t * data);
int stackPrint(stack_t * s);

#endif
