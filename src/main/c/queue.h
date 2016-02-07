#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  uint32_t * data;
  int32_t head;
  int32_t tail;
  uint32_t size;
  int empty;
  int full;
} queue_t;

int queueCreate(queue_t ** queue, uint32_t size);
void queueDestroy(queue_t ** queue);

int queueEnqueue(queue_t * queue, uint32_t data);
int queueDequeue(queue_t * queue, uint32_t * data);

int printQueue(queue_t * queue);

#endif
