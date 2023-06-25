#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* my datastructures */
typedef struct Stack {
  int top = -1;
  int size;
  int *data;
} Stack;

// int push(int *stack, int n);
int pop(int *stack, int n);
int top(int *stack);

int push(Stack *stack, int n) {
  if (stack->top >= stack->size + 1) {
    printf("Stack overflow! Stack size if = [ %d ], current top = [ %d ]\n",
           stack->size, stack->top);
    exit(1);
  }
  stack->top++;
  stack->data[stack->top] = n;
  printf("[INFO] Inserted %d at index %d\n", n, stack->top);
  printf("[INFO] Value at index %d = %d\n", stack->top,
         stack->data[stack->top]);
  return n;
}

int pop(Stack *stack) {
  if (stack->top < 0) {
    printf("Stack underflow! Stack size if = [ %d ], current top = [ %d ]\n",
           stack->size, stack->top);
    exit(1);
  }
  int temp = stack->data[stack->top];
  stack->data[stack->top] = 0;
  printf("[INFO] Popped %d at index %d\n", temp, stack->top);
  stack->top--;
  return temp;
}

int main() {
  int *data = (int *)malloc(4 * sizeof(int));
  Stack mystack = {.size = 4, .data = data};
  push(&mystack, 4);
  int r = pop(&mystack);
  // printf("popped === %d", r);
}
