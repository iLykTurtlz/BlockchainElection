#ifndef LIST_DECLARATION_H
#define LIST_DECLARATION_H

#include "declaration.h"

typedef struct cellProtected {
    Protected *data;
    struct cellProtected *next;
} CellProtected;

CellProtected *create_cell_protected(Protected *pr);
void add_protected(CellProtected **LCP, Protected *pr);
CellProtected *read_protected(char *filename);
void print_list_protected(CellProtected *LCP);
void delete_cell_protected(CellProtected *c);
void delete_list_protected(CellProtected *LCP);



#endif