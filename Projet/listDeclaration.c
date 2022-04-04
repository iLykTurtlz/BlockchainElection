#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaration.h"
#include "listDeclaration.h"
#include "manipulationClefs.h"



CellProtected *create_cell_protected(Protected *pr)  {
    CellProtected *new = (CellProtected *)malloc(sizeof(CellProtected));
    new->data = pr;
    new->next = NULL;
    return new;
}

void add_protected(CellProtected **LCP, Protected *pr)    {
    if (!pr)    
        return;
    CellProtected *cp = create_cell_protected(pr);
    cp->next = *LCP;
    *LCP = cp;
}

CellProtected *read_protected(char *filename)   {
    FILE *istream = fopen(filename, "r");
    if (istream == NULL)    {
        fprintf(stderr, "Erreur : read_protected, ouverture du fichier\n");
        return NULL;
    }
    CellProtected *LCP = NULL;
    char buffer[256];
    while (fgets(buffer,256,istream))   {
        Protected *pr = str_to_protected(buffer);
        add_protected(&LCP,pr);
    }
    return LCP;
}

void print_list_protected(CellProtected *LCP)  {
    while (LCP) {
        //new var str
        printf("%s\n",protected_to_str(LCP->data));
        LCP = LCP->next;
    }
}

void delete_cell_protected(CellProtected *c)    {
    free(c->data);
    free(c);
}

void delete_list_protected(CellProtected *LCP) {
    CellProtected *tmp;
    while (LCP) {
        tmp = LCP;
        LCP = LCP->next;
        delete_cell_protected(tmp);
    }
}