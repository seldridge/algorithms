#include "stack.h"

int main(int argc, char * argv[]) {
  stack_t * s = NULL;
  uint32_t size = 8;
  int returnVal = 0, testPass;

  stackCreate(&s, size);

  // Push data into the stack
  testPass = 1;
  for (uint32_t i = 0; i < s->size; i++) {
    if (stackPush(s, i) != 0) {
      printf("[ERROR] stackPush on non-full stack saw wrong return value\n");
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] stackPush non-full\n");
  else
    printf("[FAIL] stackPush non-full\n");

  // Push data onto a full stack
  testPass = 1;
  if (stackPush(s, -1) == 0) {
    printf("[ERROR] stackPush on full stack saw wrong return value\n");
    returnVal++;
    testPass = 0;
  }
  if (testPass)
    printf("[PASS] Stack push full\n");
  else
    printf("[FAIL] Stack push full\n");

  // Pop all the data off
  testPass = 1;
  uint32_t data;
  for (int32_t i = s->size - 1; i >= 0; i--) {
    if (stackPop(s, &data) != 0) {
      printf("[ERROR] stackPop on non-empty stack saw wrong return value\n");
      returnVal++;
      testPass = 0;
    }
    if (data != i) {
      printf("[ERROR] stackPop on non-empty stack saw wrong data\n");
      returnVal++;
      testPass = 0;
    }
  }
  if (testPass)
    printf("[PASS] Stack pop non-empty\n");
  else
    printf("[FAIL] Stack pop non-empty\n");

  // Pop empty stack
  testPass = 1;
  data = -1;
  if (stackPop(s, &data) == 1) {
    printf("[ERROR] stackPop on empty stack saw wrong return value\n");
    returnVal++;
    testPass = 0;
  }
  if (data != -1) {
    printf("[ERROR] stackPop on empty stack overwrote data\n");
    returnVal++;
    testPass = 0;
  }
  if (testPass)
    printf("[PASS] Stack pop empty\n");
  else
    printf("[FAIL] Stack pop empty\n");

  if (s != NULL)
    stackDestroy(&s);
  return 0;
}
