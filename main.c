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
#ifdef __MINGW64__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include<stdio.h>
#include<stdlib.h>

#include "list.h"
#include "stack.h"

void test_list();
void test_stack();

int main(void)
{
	test_list();
	//test_stack();
	return 0;
}

void test_stack()
{
	Stack *testStack = stack_new();
	if(testStack == NULL) {
		printf("Somthing's wrong...\n");
		exit(EXIT_FAILURE);
	}

	printf("Size of stack: %zu\n", stack_sizeof(testStack));
	if (stack_isEmpty(testStack)) {
		printf("Stack is empty\n");
	}
	printf("Pushing elements to stack...\n");
	stack_push(testStack, &(int){69});
	stack_push(testStack, &(int){420});
	stack_push(testStack, &(int){3});
	stack_push(testStack, &(int){4});
	stack_push(testStack, &(int){77});
	printf("Size of stack right now: %zu\n", (size_t)stack_sizeof(testStack));

//	printf("Freeing and reinitializing the stack...\n");
//	stack_free(testStack);
//	testStack = stack_new();
//	if(testStack == NULL) {
//		printf("Something's wrong...\n");
//		exit(EXIT_FAILURE);
//	}

	while(!stack_isEmpty(testStack)) {
		printf("Size of stack right now: %zu\n", (size_t)stack_sizeof(testStack));
		printf("Stack peek: %d\nDeleting...\n", *(int *)stack_peek(testStack));
		if (!stack_isEmpty(testStack)) {
			stack_pop(testStack);
		}
	}

	printf("Size of stack right now: %zu\n", (size_t)stack_sizeof(testStack));

	if (stack_isEmpty(testStack)) {
		printf("Stack is empty\n");
	}

	stack_free(testStack);
}

void test_list()
{
	List *testList = list_new();
	if(testList == NULL) {
		printf("Something's wrong...\n");
		exit(EXIT_FAILURE);
	}

	printf("Size of list: %zu\n", list_sizeof(testList));

	list_add(testList, &(int){69});
	list_add(testList, &(int){420});
	list_add(testList, &(int){86});
	list_add(testList, &(int){39});
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));

	list_insert(testList, 3, &(int){33});
	list_insert(testList, 0, &(int){44});
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));

	list_insert(testList, 5, &(int){58008});
	list_insert(testList, 6, &(int){1337});
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));

	int in_index = 0;
	do {
		printf("Enter index (-1 to finish): ");
		// typecast to void so -Wunused-result won't happen
		(void) !scanf("%d", &in_index);
		if(in_index >= 0 && (size_t)in_index < list_sizeof(testList)) {
			printf("Value at index %d is: %d\n", in_index, *((int*) list_get(testList, in_index)));
		} else if (in_index >= (int)list_sizeof(testList)){
			printf("Please enter a value within the valid range\n");
		}
	} while(in_index >= 0);
//	list_get(testList, 100);	// this is intentionally an error

	list_print(testList);
	list_delete(testList, 4);
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));
	list_delete(testList, 0);
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));
	list_delete(testList, list_sizeof(testList)-1);
	list_print(testList);
	printf("Size of list: %zu\n", list_sizeof(testList));

	while(list_sizeof(testList) != 0) {
		list_delete(testList, 0);
		list_print(testList);
		printf("Size of list: %zu\n", list_sizeof(testList));
	}
	list_free(testList);
}
