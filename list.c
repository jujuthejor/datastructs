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
// DONE: get utility
// DONE: delete utility
// TODO: Improve error reports/handling
// TODO: sizeOfList() might be better off returning size_t
#include<stdio.h>
#include<stdlib.h>

#include "list.h"

struct node_t {
	int value;
	struct node_t *next;
};

struct list {
	Node *head;			// first item in list
	Node *tail;			// last item in list
};

int initList(List **plist)
{
	*plist = malloc(sizeof(List));

	if (plist == NULL) {
		return -1;
	} else {
		(*plist)->head = NULL;
		(*plist)->tail = NULL;
		return 0;
	}
}

int addToList(List **plist, int value)
{
	Node *newNode = malloc(sizeof(Node));

	if(newNode == NULL) {
		return -1;
	} else {
		newNode->value = value;
		newNode->next = NULL;
		if ((*plist)->head == NULL){
			(*plist)->head = newNode;
			(*plist)->tail = newNode;
		} else {
			(*plist)->tail->next = newNode;
			(*plist)->tail = newNode;
		}
		return 0;
	}
}

int sizeofList(List** plist){
	int count = 0;
	Node *currentNode = (*plist)->head;

	while(currentNode != NULL) {
		count++;
		currentNode = currentNode->next;
	}
	return count;
}

int insertIntoList(List **plist, int index, int value)
{
	Node *prevNode, *currentNode, *newItem;

	if(index >= sizeofList(plist)){
		printf("index out of bounds\n");
		return -1;
	}

	newItem = malloc(sizeof(Node));
	if(newItem == NULL) {
		return -1;
	}

	newItem->value = value;
	newItem->next = NULL;

	prevNode = NULL;
	currentNode = (*plist)->head;

	int i = 0;
	while(i != index) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		i++;
	}

	if(i == 0) {
		newItem->next = currentNode;
		(*plist)->head = newItem;
	} else {
		prevNode->next = newItem;
		newItem->next = currentNode;

		if(i == sizeofList(plist) - 1) {
			(*plist)->tail = newItem;
		}
	}

	return 0;
}

int getFromList(List **plist, int index)
{
	Node *currentNode;

	if(index >= sizeofList(plist)){
		printf("index out of bounds\n");
		exit(EXIT_FAILURE);
	}

	currentNode = (*plist)->head;

	int i = 0;
	while(i != index) {
		currentNode = currentNode->next;
		i++;
	}

	return currentNode->value;
}

int deleteFromList(List **plist, int index)
{
	Node *currentNode, *prevNode;

	if(index >= sizeofList(plist)){
		printf("index out of bounds\n");
		return -1;
	}

	prevNode = NULL;
	currentNode = (*plist)->head;

	int i = 0;
	while(i != index) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		i++;
	}

	if(i == 0) {
		(*plist)->head = currentNode->next;
	} else if (i == sizeofList(plist) - 1) {
		(*plist)->tail = prevNode;
		(*plist)->tail->next = NULL;
	} else {
		prevNode->next = currentNode->next;
	}

	free(currentNode);
	return 0;
}

void printList(List **plist)
{
	Node *traverse = (*plist)->head;
	while(traverse != NULL) {
		printf("%d\t", traverse->value);
		traverse = traverse->next;
	}
	printf("\n");
}

void freeList(List **plist)
{
	Node *target, *next;

	target = (*plist)->head;
	next = target->next;

	while(target != NULL) {
		free(target);
		target = next;
		if (target != NULL) {
			next = target->next;
		}
	}
}
