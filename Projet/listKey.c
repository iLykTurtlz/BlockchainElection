#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manipulationClefs.h"
#include "listKey.h"


CellKey *create_cell_key(Key *key)  {
    CellKey *new = (CellKey *)malloc(sizeof(CellKey));
    new->data = key;
    new->next = NULL;
    return new;
}

void add_key(CellKey **LCK, Key *key)    {
    if (!key)    
        return;
    CellKey *ck = create_cell_key(key);
    ck->next = *LCK;
    *LCK = ck;
}

CellKey *read_public_keys(char *filename)   {
    FILE *istream = fopen(filename, "r");
    if (istream == NULL)    {
        fprintf(stderr, "Erreur : read_public_keys, ouverture du fichier\n");
        return NULL;
    }
    CellKey *LCK = NULL;
    char buffer[256];
    char lu[256];
    while (fgets(buffer,256,istream))   {
        if (sscanf(buffer,"%s ",lu) == 1)   {
            Key *key = str_to_key(lu);          //ne pas desallouer !
            add_key(&LCK,key);
        }
    }
    fclose(istream);
    return LCK;
}

void print_list_keys(CellKey *LCK)  {
    char *keyStr;
    while (LCK) {
        keyStr = key_to_str(LCK->data);
        printf("%s\n",keyStr);
        free(keyStr);
        LCK = LCK->next;
    }
}

void delete_cell_key(CellKey *c)    {
    free(c->data);
    free(c);
}

void delete_list_keys(CellKey *LCK) {
    CellKey *tmp;
    while (LCK) {
        tmp = LCK;
        LCK = LCK->next;
        delete_cell_key(tmp);
    }
}











