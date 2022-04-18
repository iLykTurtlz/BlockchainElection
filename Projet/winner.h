#ifndef WINNER_H
#define WINNER_H

#include "listKey.h"

void thwarted(CellProtected **LCP);

typedef struct hashcell {
    Key *key;
    int val;
} HashCell;

typedef struct hashtable {
    HashCell **tab;
    int size;
} HashTable;

HashCell *create_hashcell(Key *key);
int hash_function(Key *key, int size);
int find_position(HashTable *t, Key *key);
HashTable *create_hashtable(CellKey *keys, int size);
void delete_hashtable(HashTable *t);
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
void afficher_tableH(HashTable *t);


#endif