#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack Stack;

int initStack(Stack **stackptr);

int sizeOfStack(Stack **stackptr);

int pushStack(Stack **stackptr, int value);

int peekStack(Stack **stackptr);

void popStack(Stack **stackptr);

bool isEmptyStack(Stack **stackptr);

void freeStack(Stack **stackptr);
#endif
