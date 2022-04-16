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
void delete_cell_protected_total(CellProtected *c);
void delete_list_protected(CellProtected *LCP);
void delete_list_protected_total(CellProtected *LCP);

//Exerice 8.8
CellProtected *fusionner_list_protected(CellProtected *votes1, CellProtected *votes2);
CellProtected *copie_list_protected(CellProtected *votes);




#endif