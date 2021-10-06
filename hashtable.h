#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct h_table HashTable;

HashTable* htable_new();

int htable_addEntry(HashTable *htable, char key[], void *value);

bool htable_searchKey(HashTable *htable, char key[]);

int htable_editEntry(HashTable *htable, char key[], void *value);

int htable_deleteEntry(HashTable *htable, char key[]);

void* htable_getEntry(HashTable *htable, char key[]);

void htable_free(HashTable *htable);
#endif
