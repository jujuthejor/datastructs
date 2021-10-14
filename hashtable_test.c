#include <stdio.h>

#include "hashtable.h"

int main(void)
{
	HashTable *int_ht = htable_new();

	int int_values[] = {69, 420, 177013};
	if(htable_addEntry(int_ht, "nice", &int_values[0])) {
		printf("Unable to add to hash table\n");
	} else {
		printf("Entry added to hash table...\n");
	}
	if(htable_addEntry(int_ht, "blaze it", &int_values[1])) {
		printf("Unable to add to hash table\n");
	} else {
		printf("Entry added to hash table...\n");
	}
	if(htable_addEntry(int_ht, "oof", &int_values[2])) {
		printf("Unable to add to hash table\n");
	} else {
		printf("Entry added to hash table...\n");
	}

	if(!htable_addEntry(int_ht, "nice", &int_values[2])) {
		printf("Unable to add entry using existing key\n");
	}

	int *pInt = (int *)htable_getEntry(int_ht, "nice");
	printf("Value stored at key \"%s\" is %d\n", "nice", *pInt);

	pInt = (int *)htable_getEntry(int_ht, "blaze it");
	printf("Value stored at key \"%s\" is %d\n", "blaze it", *pInt);

	pInt = (int *)htable_getEntry(int_ht, "oof");
	printf("Value stored at key \"%s\" is %d\n", "oof", *pInt);

	printf("Searching for \"nice\" key...\n");
	if (htable_searchKey(int_ht, "nice")) {
		printf("\"nice\" found.\n");
	} else {
		printf("\"nice\" not found.\n");
	}

	printf("Searching for \"wew\" key...\n");
	if (htable_searchKey(int_ht, "wew")) {
		printf("\"wew\" found.\n");
	} else {
		printf("\"wew\" not found.\n");
	}

	printf("Editing value of key \"nice\"...\n");
	htable_editEntry(int_ht, "nice", &int_values[1]);
	pInt = (int *)htable_getEntry(int_ht, "nice");
	printf("Value stored at key \"%s\" is %d\n", "nice", *pInt);

	printf("Deleting key \"oof\"...\n");
	htable_deleteEntry(int_ht, "oof");
	if(htable_searchKey(int_ht, "oof")) {
		printf("\"oof\" is still here!\n");
	} else {
		printf("\"oof\" deleted!\n");
	}

	htable_free(int_ht);
	return 0;
}
