#ifndef __DEQUE_H__
#define __DEQUE_H__

#include "queue.h"

typedef queue_t deque_t;

int dequeCreate(deque_t ** deque, uint32_t size);
void dequeDestroy(deque_t ** deque);

int dequePushFront(deque_t * deque, uint32_t data);
int dequePushBack(deque_t * deque, uint32_t data);
int dequePopFront(deque_t * deque, uint32_t * data);
int dequePopBack(deque_t * deque, uint32_t * data);

int printDeque(deque_t * deque);

#endif
