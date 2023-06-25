typedef struct Stack {
  int top = -1;
  int size;
  char *data;
} Stack;

char push(Stack *stack, char n);
char pop(Stack *stack);
char top(Stack *stack);
