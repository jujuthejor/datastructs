/*
 * Copyright (c) 2021 Jose Gabriel Ramos (@jujuthejor)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct st_node {
	void *value;
	struct st_node *next;
};

struct stack {
	struct st_node *head, *tail;
	size_t size;
};

Stack* stack_new(void)
{
	Stack *stackptr = malloc(sizeof(Stack));

	if (stackptr != NULL) {
		stackptr->size = 0;
		stackptr->head = NULL;
		stackptr->tail = NULL;
	}

	return stackptr;
}

size_t stack_sizeof(Stack *stackptr)
{
	return stackptr->size;
}

int stack_push(Stack *stackptr, void *value)
{
	struct st_node *newElement = malloc(sizeof(struct st_node));

	if(newElement == NULL) {
		return -1;
	}

	newElement->value = value;
	newElement->next = NULL;

	if (stackptr->head == NULL) {
		stackptr->head = newElement;
	} else {
		stackptr->tail->next = newElement;
	}
	stackptr->tail = newElement;

	stackptr->size++;

	return 0;
}

void* stack_peek(Stack *stackptr)
{
	if(stack_isEmpty(stackptr)) {
		printf("Error: stack empty\n");
		exit(EXIT_FAILURE);
	}

	return stackptr->tail->value;
}

void stack_pop(Stack *stackptr)
{
	struct st_node *traverse = stackptr->head;
	struct st_node *newTail = NULL;

	if(stack_isEmpty(stackptr)) {
		printf("Error: stack empty\n");
		exit(EXIT_FAILURE);
	}

	if (stackptr->head == stackptr->tail) {
		stackptr->head = NULL;
		stackptr->tail = NULL;
	} else {
		while (traverse->next != NULL) {
			newTail  = traverse;
			traverse = traverse->next;
		}
		newTail->next = NULL;
		stackptr->tail = newTail;
	}

	free(traverse);
	stackptr->size--;
}

bool stack_isEmpty(Stack *stackptr)
{
	if(stackptr->size == 0) {
		return true;
	} else {
		return false;
	}
}

void stack_free(Stack *stackptr)
{
	while (!stack_isEmpty(stackptr)) {
		stack_pop(stackptr);
	}

	free(stackptr);
}
