#ifndef LIST_KEY_H
#define LIST_KEY_H

#include "manipulationClefs.h"

typedef struct cellKey {
    Key *data;
    struct cellKey *next;
} CellKey;

CellKey *create_cell_key(Key *key);
void add_key(CellKey **LCK, Key *key);
CellKey *read_public_keys(char *filename);
void print_list_keys(CellKey *LCK);
void delete_cell_key(CellKey *c);
void delete_list_keys(CellKey *LCK);
int listKeyLength(CellKey *list);


#endif