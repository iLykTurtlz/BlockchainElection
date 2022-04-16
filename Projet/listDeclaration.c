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
        Protected *pr = str_to_protected(buffer);   //ne pas desallouer !
        add_protected(&LCP,pr);
    }
    fclose(istream);
    return LCP;
}

void print_list_protected(CellProtected *LCP)  {
    char *prStr;
    while (LCP) {
        prStr = protected_to_str(LCP->data);
        printf("%s\n",prStr);
        free(prStr);
        LCP = LCP->next;
    }
}

void delete_cell_protected(CellProtected *c)    {
    //on ne supprime pas les clefs
    free(c->data->mess);            
    freeSignature(c->data->sgn);
    free(c);
}

void delete_cell_protected_total(CellProtected *c)     {
    //supprime aussi les clefs
    freeProtected(c->data);
    free(c);
}  

void delete_list_protected(CellProtected *LCP) {
    //ne supprime pas les clefs
    CellProtected *tmp;
    while (LCP) {
        tmp = LCP;
        LCP = LCP->next;
        delete_cell_protected(tmp);
    }
}

void delete_list_protected_total(CellProtected *LCP)  {
    //supprime aussi les clefs
    CellProtected *tmp;
    while (LCP) {
        tmp = LCP;
        LCP = LCP->next;
        delete_cell_protected_total(tmp);
    }
}

//Exercice 8.8
//Il faudrait une liste doublement chainee pour avoir une fusion en O(1) au lieu de O(len(votes1))
CellProtected *fusionner_list_protected(CellProtected *votes1, CellProtected *votes2)   {
    //si une liste est vide, la fusion c'est l'autre
    if (!votes1)    {
        return votes2;
    }
    if (!votes2)    {
        return votes1;
    }
    //On parcourt votes1
    CellProtected *curr = votes1;
    while (curr->next)    {
        curr = curr->next;
    }
    curr->next = votes2;
    return votes1;
}


CellProtected *copie_list_protected(CellProtected *votes)   {
    //Cette fonction inverse le sens de la liste, mais ce n'est pas grave
    if (!votes) {
        return NULL;
    }
    CellProtected *copie = NULL;

    while (votes)   {
        add_protected(&copie,votes->data);
        votes = votes->next;
    }
    return copie;
}