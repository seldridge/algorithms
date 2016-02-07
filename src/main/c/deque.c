#include "deque.h"

int dequeCreate(deque_t ** deque, uint32_t size) {
  int returnVal = queueCreate((queue_t **) deque, size);
  return returnVal;
}

void dequeDestroy(deque_t ** deque) {
  queueDestroy((queue_t **) deque);
}

int dequePushFront(deque_t * deque, uint32_t data) {
  if (deque->full)
    return 1;
  if (--deque->head < 0)
    deque->head = deque->size - 1;
  deque->data[deque->head] = data;
  deque->full = deque->head == deque->tail;
  deque->empty = 0;
  return 0;
}

int dequePushBack(deque_t * deque, uint32_t data) {
  int returnVal = queueEnqueue((queue_t *) deque, data);
  return returnVal;
}

int dequePopFront(deque_t * deque, uint32_t * data) {
  int returnVal = queueDequeue((queue_t *) deque, data);
  return returnVal;
}

int dequePopBack(deque_t * deque, uint32_t * data) {
  if (deque->empty)
    return 1;
  if (--deque->tail < 0)
    deque->tail = deque->size - 1;
  (*data) = deque->data[deque->tail];
  deque->full = 0;
  deque->empty = deque->head == deque->tail;
  return 0;
}

int printDeque(deque_t * deque) {
  printQueue((queue_t *) deque);
}
