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
