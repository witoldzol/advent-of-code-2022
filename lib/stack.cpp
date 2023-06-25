#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
  int top = -1;
  int size;
  char *data;
} Stack;

char push(Stack *stack, char c) {
  if (stack->top >= stack->size + 1) {
    printf("Stack overflow! Stack size if = [ %d ], current top = [ %d ]\n",
           stack->size, stack->top);
    exit(1);
  }
  stack->top++;
  stack->data[stack->top] = c;
  printf("[INFO] Inserted %c at index %d\n", c, stack->top);
  return c;
}

char pop(Stack *stack) {
  if (stack->top < 0) {
    printf("Stack underflow! Stack size = [ %d ], current top = [ %d ]\n",
           stack->size, stack->top);
    exit(1);
  }
  char temp = stack->data[stack->top];
  stack->data[stack->top] = 0;
  printf("[INFO] Popped %c at index %d\n", temp, stack->top);
  stack->top--;
  return temp;
}

char top(Stack *stack) {
  if (stack->top < 0) {
    return '\0';
  }
  return stack->data[stack->top];
}
