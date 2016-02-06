#include "queue.h"

int main(int argc, char * argv[]) {
  queue_t * queue = NULL;
  int returnVal = 0, testPass;
  const uint32_t size = 10000;

  if (queueCreate(&queue, size)) {
    printf("[ERROR] Failed to create queue\n");
    returnVal = -1;
    goto finish;
  }

  // Fill the queue
  testPass = 1;
  for (uint32_t i = 0; i < queue->size; i++) {
    if (queueEnqueue(queue, (uint32_t) i) != 0) {
      printf("[ERROR] Unable to enqueue item %d\n", i);
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] Enqueue test\n");
  else
    printf("[FAIL] Enqueue test\n");

  // Try to overwrite the queue
  testPass = 1;
  for (uint32_t i = 0; i < queue->size * 2; i++) {
    if (queueEnqueue(queue, (uint32_t) i + queue->size) != 1) {
      printf("[ERROR] Incorrect return val from overwriting queue\n");
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] Overwrite queue test\n");
  else
    printf("[FAIL] Overwrite queue test\n");

  // Try to read all the data from the queue
  uint32_t data;
  testPass = 1;
  for (uint32_t i = 0; i < queue->size; i++) {
    queueDequeue(queue, &data);
    if (data != i) {
      printf("[ERROR] Expected %d, but saw %d\n", i, data);
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] Dequeue test\n");
  else
    printf("[FAIL] Dequeu test\n");

  // Try to read data beyond the queue
  testPass = 1;
  data = 0xdead;
  for (uint32_t i = 0; i < queue->size*2; i++) {
    if (queueDequeue(queue, &data) != 1) {
      printf("[ERROR] queueDequeue reporting wrong return val\n");
      returnVal++;
      testPass = 0;
    }
    if (data != 0xdead) {
      printf("[ERROR] queueDequeue wrote over data\n");
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] Dequeue empty queue test\n");
  else
    printf("[FAIL] Dequeue empty queue test\n");

 finish:
  if (queue != NULL)
    queueDestroy(&queue);
  return returnVal;
}
