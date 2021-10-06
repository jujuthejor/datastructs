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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "list.h"

#define STRING_SIZE 64
#define BUCKET_SIZE 53

struct kv_pair {
	char key[STRING_SIZE];
	void *value;
};

struct h_table {
	List *table[BUCKET_SIZE];
};

static inline int myHash(char key[], size_t size)
{
	int hash = 0;
	for(int i = 0; i != (int) '\0' || i != (int) size; i++) {
		hash += (int) key[i];
	}

	return hash;
}

HashTable* htable_new()
{
	HashTable *new_ht = malloc(sizeof(HashTable));

	if (new_ht != NULL) {
		for(int i = 0; i < BUCKET_SIZE; i++) {
			new_ht->table[i] = list_new();
		}
	}

	return new_ht;
}

int htable_addEntry(HashTable *htable, char key[], void *value)
{
	if (!htable_searchKey(htable, key)) {
		return -1;
	}

	struct kv_pair *newPair = malloc(sizeof(struct kv_pair));

	if (newPair == NULL) {
		return -1;
	}

	strncpy(newPair->key, key, STRING_SIZE);
	newPair->key[STRING_SIZE - 1] = '\0';
	newPair->value = value;

	int hashValue = myHash(newPair->key, strlen(newPair->key));
	list_add(htable->table[hashValue % BUCKET_SIZE], newPair);
	return 0;
}

bool htable_searchKey(HashTable *htable, char key[])
{
	int hashValue = myHash(key, strlen(key));
	List *bucket = htable->table[hashValue % BUCKET_SIZE];

	for (int i = 0; i < (int)list_sizeof(bucket); i++) {
		struct kv_pair item = *((struct kv_pair *) list_get(bucket, i));

		if (strcmp(item.key, key) == 0) {
			return true;
		}
	}

	return false;
}

int htable_editEntry(HashTable *htable, char key[], void *value)
{
	if (!htable_searchKey(htable, key)) {
		return -1;
	}

	int hashIndex = myHash(key, strlen(key)) % BUCKET_SIZE;
	List *bucket = htable->table[hashIndex];

	for (int i = 0; i < (int)list_sizeof(bucket); i++) {
		struct kv_pair *item = (struct kv_pair *) list_get(bucket, i);

		if (strcmp(item->key, key) == 0) {
			item->value = value;
		}
	}

	return 0;
}

int htable_deleteEntry(HashTable *htable, char key[])
{
	if (!htable_searchKey(htable, key)) {
		return -1;
	}

	int hashIndex = myHash(key, strlen(key)) % BUCKET_SIZE;
	List *bucket = htable->table[hashIndex];

	for (int i = 0; i < (int)list_sizeof(bucket); i++) {
		struct kv_pair *item = (struct kv_pair *) list_get(bucket, i);

		if (strcmp(item->key, key) == 0) {
			list_delete(bucket, i);
		}
	}

	return 0;
}

void* htable_getEntry(HashTable *htable, char key[])
{
	if (!htable_searchKey(htable, key)) {
		return NULL;
	}

	int hashIndex = myHash(key, strlen(key)) % BUCKET_SIZE;
	List *bucket = htable->table[hashIndex];

	struct kv_pair *item = NULL;
	for (int i = 0; i < (int)list_sizeof(bucket); i++) {
		item = (struct kv_pair *) list_get(bucket, i);

		if (strcmp(item->key, key) == 0) {
			break;
		}
	}

	return item->value;
}

void htable_free(HashTable *htable)
{
	for (int i = 0; i < BUCKET_SIZE; i++) {
		list_free(htable->table[i]);
	}

	free(htable);
}
