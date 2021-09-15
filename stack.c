#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct st_node {
	int value;
	struct st_node *next;
};

struct stack {
	struct st_node *head, *tail;
};

int initStack(Stack **stackptr)
{
	*stackptr = malloc(sizeof(Stack));

	if (*stackptr == NULL) {
		return -1;
	}

	(*stackptr)->head = NULL;
	(*stackptr)->tail = NULL;

	return 0;
}

int sizeOfStack(Stack **stackptr)
{
	struct st_node *traverse = (*stackptr)->head;
	int count = 0;

	if(traverse != NULL) {
		while(traverse != NULL) {
			count++;
			traverse = traverse->next;
		}
	}

	return count;
}

int pushStack(Stack **stackptr, int value)
{
	struct st_node *traverse = (*stackptr)->head;
	struct st_node *newElement = malloc(sizeof(struct st_node));

	if(newElement == NULL) {
		return -1;
	}

	newElement->value = value;
	newElement->next = NULL;

	if (traverse == NULL) {
		(*stackptr)->head = newElement;
	} else {
		while (traverse->next != NULL) {
			traverse = traverse->next;
		}
		traverse->next = newElement;
	}

	(*stackptr)->tail = newElement;

	return 0;
}

int peekStack(Stack **stackptr)
{
	if(isEmptyStack(stackptr)) {
		printf("Error: stack empty\n");
		exit(EXIT_FAILURE);
	}

	return (*stackptr)->tail->value;
}

void popStack(Stack **stackptr)
{
	struct st_node *traverse = (*stackptr)->head;

	if(isEmptyStack(stackptr)) {
		printf("Error: stack empty\n");
		exit(EXIT_FAILURE);
	}

	while (traverse->next != (*stackptr)->tail) {
		traverse = traverse->next;
	}
	traverse->next = NULL;

	free((*stackptr)->tail);
	(*stackptr)->tail = traverse;
}

bool isEmptyStack(Stack **stackptr)
{
	if((*stackptr)->head == NULL) {
		return true;
	} else {
		return false;
	}
}

void printStack(Stack **stackptr)
{
	struct st_node *traverse = (*stackptr)->head;

	if(traverse->next != NULL) {
		return;
	}

	traverse = traverse->next;
	while(traverse->next != NULL) {
		printf("%d\t", traverse->value);
	}
	printf("\n");
}

void freeStack(Stack **stackptr)
{
	struct st_node *traverse = (*stackptr)->head;
	struct st_node *target = traverse;

	if (traverse != NULL) {
		while (traverse->next != NULL) {
			free(target);
			traverse = traverse->next;
			target = traverse;
		}
	}

	free(*stackptr);
}
