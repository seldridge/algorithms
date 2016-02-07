#include "queue.h"

int queueCreate(queue_t ** queue, uint32_t size) {
  (*queue) = (queue_t *) malloc (sizeof(queue_t));
  if (*queue == NULL)
    return 1;

  (*queue)->data = (uint32_t *) malloc(sizeof(uint32_t) * size);
  if ((*queue)->data == NULL)
    return 1;

  (*queue)->head = 0;
  (*queue)->tail = 0;
  (*queue)->size = size;
  (*queue)->empty = 1;
  (*queue)->full = 0;
  return 0;
}

void queueDestroy(queue_t ** queue) {
  free((*queue)->data);
  free(*queue);
}

int queueEnqueue(queue_t * queue, uint32_t data) {
  if (queue->full)
    return 1;
  queue->data[queue->tail] = data;
  queue->tail = (queue->tail + 1) % queue->size;
  queue->full = queue->head == queue->tail;
  queue->empty = 0;
  return 0;
}

int queueDequeue(queue_t * queue, uint32_t * data) {
  if (queue->empty)
    return 1;
  *data = queue->data[queue->head];
  queue->head = (queue->head + 1) % queue->size;
  queue->full = 0;
  queue->empty = queue->head == queue->tail;
  return 0;
}

int printQueue(queue_t * queue) {
  if (queue == NULL) {
    printf("[ERROR] Tried to print uninitialized queue");
    return -1;
  }

  for (uint32_t i = 0; i < queue->size; i++)
    printf("%2d|", queue->data[i]);
  printf("\n");

  for (uint32_t i = 0; i < queue->size; i++) {
    if (i == queue->head) printf("h");
    else                  printf("_");

    if (i == queue->tail) printf("t|");
    else                  printf("_|");
  }

  if (queue->empty) printf("e");
  else              printf(" ");

  if (queue->full)  printf("f");
  printf("\n");
}
