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
// TODO: Improve error reports/handling; might want to exit on an error in some cases
// 		 instead of returning -1...
#include <stddef.h>
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
	size_t size;
};

int initList(List **listptr)
{
	*listptr = malloc(sizeof(List));

	if (listptr == NULL) {
		return -1;
	} else {
		(*listptr)->size = 0;
		(*listptr)->head = NULL;
		(*listptr)->tail = NULL;
		return 0;
	}
}

int addToList(List **listptr, int value)
{
	Node *newNode = malloc(sizeof(Node));

	if(newNode == NULL) {
		return -1;
	} else {
		newNode->value = value;
		if ((*listptr)->head == NULL){
			(*listptr)->head = newNode;
			(*listptr)->tail = newNode;
		} else {
			(*listptr)->tail->next = newNode;
			(*listptr)->tail = newNode;
		}
		newNode->next = NULL;
		(*listptr)->size++;
		return 0;
	}
}

size_t sizeofList(List** listptr){
	return (*listptr)->size;
}

int insertIntoList(List **listptr, int index, int value)
{
	Node *prevNode, *currentNode, *newItem;

	if((size_t)index >= sizeofList(listptr)){
		printf("insertIntoList error: index out of bounds\n");
		exit(EXIT_FAILURE);
	}

	newItem = malloc(sizeof(Node));
	if(newItem == NULL) {
		return -1;
	}

	newItem->value = value;
	newItem->next = NULL;

	prevNode = NULL;
	currentNode = (*listptr)->head;

	int i = 0;
	while(i != index) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		i++;
	}

	if(i == 0) {
		newItem->next = currentNode;
		(*listptr)->head = newItem;
	} else {
		prevNode->next = newItem;
		newItem->next = currentNode;

//		if((size_t)i == sizeofList(listptr) - 1) {
//			(*listptr)->tail = newItem;
//		}
	}
	(*listptr)->size++;

	return 0;
}

int getFromList(List **listptr, int index)
{
	Node *currentNode;

	if(sizeofList(listptr) == 0) {
		printf("getFromList error: list empty");
		exit(EXIT_FAILURE);
	}

	if((size_t)index >= sizeofList(listptr)){
		printf("getFromList error: index out of bounds\n");
		exit(EXIT_FAILURE);
	}

	currentNode = (*listptr)->head;

	int i = 0;
	while(i != index) {
		currentNode = currentNode->next;
		i++;
	}

	return currentNode->value;
}

int deleteFromList(List **listptr, int index)
{
	Node *currentNode, *prevNode;

	if(sizeofList(listptr) == 0) {
		printf("deleteFromList error: list empty");
		exit(EXIT_FAILURE);
	}

	if((size_t)index >= sizeofList(listptr)){
		printf("deleteFromList error: index out of bounds\n");
		exit(EXIT_FAILURE);
	}

	prevNode = NULL;
	currentNode = (*listptr)->head;

	int i = 0;
	while(i != index) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		i++;
	}

	if(i == 0) {
		(*listptr)->head = currentNode->next;
	} else if ((size_t)i == sizeofList(listptr) - 1) {
		(*listptr)->tail = prevNode;
		(*listptr)->tail->next = NULL;
	} else {
		prevNode->next = currentNode->next;
	}

	free(currentNode);
	(*listptr)->size--;
	return 0;
}

void printList(List **listptr)
{
	Node *traverse = (*listptr)->head;
	while(traverse != NULL) {
		printf("%d\t", traverse->value);
		traverse = traverse->next;
	}
	printf("\n");
}

void freeList(List **listptr)
{
	while(sizeofList(listptr) != 0) {
		printf("free memory holding value %d\n", getFromList(listptr, 0));
		deleteFromList(listptr, 0);
		printf("freed\n");
	}
	free(*listptr);
}
