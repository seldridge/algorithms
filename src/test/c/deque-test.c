#include "deque.h"

int main(int argc, char * argv[]) {
  deque_t * deque = NULL;
  uint32_t size = 10000;
  int returnVal = 0, testPass;

  if (dequeCreate(&deque, size)) {
    printf("[ERROR] Failed to creat deque\n");
    returnVal = -1;
    goto finish;
  }

  // Fill the deque alternating push back/front. The output should look like:
  //   [deque->size - 1, ..., 7, 5, 3, 1, 0, 2, 4, 6, ..., deque->size - 2]
  testPass = 1;
  for (uint32_t i = 0; i < deque->size; i++) {
    switch (i % 2) {
    case 0:
      if (dequePushBack(deque, i) != 0) {
        printf("[ERROR] Bad dequePushBack return val on non-full deque\n");
        testPass = 0;
        returnVal++;
      }
      break;
    case 1:
      if (dequePushFront(deque, i) != 0) {
        printf("[ERROR] Bad dequePushFront return val on non-full deque\n");
        testPass = 0;
        returnVal++;
      }
    }
  }
  if (testPass)
    printf("[PASS] Push Front/Back test on non-full deque\n");
  else
    printf("[FAIL] Push Front/Back test on non-full deque\n");

  // Try to overwrite
  testPass = 1;
  if (dequePushBack(deque, -1) != 1) {
    printf("[ERROR] Bad dequePushBack return val on full deque\n");
    testPass = 0;
    returnVal++;
  }
  if (dequePushFront(deque, -2) != 1) {
    printf("[ERROR] Bad dequePushFront return val on full deque\n");
    testPass = 0;
    returnVal++;
  }
  if (testPass)
    printf("[PASS] Push Front/Back test on full deque\n");
  else
    printf("[FAIL] Push Front/Back test on full deque\n");

  // Read out all the data
  uint32_t data;
  testPass = 1;
  for (int32_t i = deque->size - 1; i >= 0; i--) {
    switch (i % 2) {
    case 0:
      if (dequePopBack(deque, &data) != 0) {
        printf("[ERROR] Bad dequePopFront return val on non-full deque\n");
        testPass = 0;
        returnVal++;
      }
      break;
    case 1:
      if (dequePopFront(deque, &data) != 0) {
        printf("[ERROR] Bad dequePushFront return val on non-full deque\n");
        testPass = 0;
        returnVal++;
      }
    }
    if (data != i) {
      printf("[ERROR] Expected to read %d from deque but saw %d\n", i, data);
      testPass = 0;
      returnVal++;
    }
  }
  if (testPass)
    printf("[PASS] Deque pop front/back test\n");
  else
    printf("[FAIL] Deque pop front/back test\n");

 finish:
  if (deque != NULL)
    dequeDestroy(&deque);
  return returnVal;
}
