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
#include<stdio.h>

#include "list.h"

int main(void)
{
	List *testList ;
	if(initList(&testList)) {
		printf("Something's wrong...\n");
		return -1;
	}

	addToList(&testList, 69);
	addToList(&testList, 420);
	addToList(&testList, 86);
	addToList(&testList, 39);
	printList(&testList);
	printf("Size of list: %d\n", sizeofList(&testList));

	insertIntoList(&testList, 3, 33);
	insertIntoList(&testList, 0, 44);
	printList(&testList);
	printf("Size of list: %d\n", sizeofList(&testList));

	insertIntoList(&testList, 5, 58008);
	insertIntoList(&testList, 6, 1337);
	printList(&testList);
	printf("Size of list: %d\n", sizeofList(&testList));

	int in_index = 0;
	do {
		printf("Enter index (-1 to finish): ");
		scanf("%d", &in_index);
		if(in_index >= 0 && in_index < sizeofList(&testList)) {
			printf("Value at index %d is: %d\n", in_index, getFromList(&testList, in_index));
		} else if (in_index >= sizeofList(&testList)){
			printf("Please enter a value within the valid range\n");
		}
	} while(in_index >= 0);
//	getFromList(&testList, 100);

	printList(&testList);
	deleteFromList(&testList, 4);
	printList(&testList);
	deleteFromList(&testList, 0);
	printList(&testList);
	deleteFromList(&testList, sizeofList(&testList)-1);
	printList(&testList);

	freeList(&testList);

	return 0;
}
