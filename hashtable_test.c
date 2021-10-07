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

	htable_free(int_ht);
	return 0;
}
