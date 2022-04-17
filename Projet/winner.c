#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "listDeclaration.h"
#include "winner.h"
#include "listKey.h"


void thwarted(CellProtected **LCP)  {
    //supprime les votes non verifies
    if (!(*LCP))
        return;
    CellProtected *first = *LCP;
    CellProtected *prev = first;
    CellProtected *curr = first->next;

    while (curr)    {
        if (!verify(curr->data))  {
            prev->next = curr->next;
            //on supprime la cellule et le protected mais pas la cle 
            delete_cell_protected(curr);    
        } else {
            prev = curr;
        }
        curr = prev->next;
    }

    if (!verify(first->data)) {
        *LCP = first->next;
        delete_cell_protected(first);
    }
}

HashCell *create_hashcell(Key *key) {
    HashCell *new = (HashCell *)malloc(sizeof(HashCell));
    new->key = key;
    new->val = 0;
    return new;
}

int hash_function(Key *key, int size)   {
    double A = (sqrt(5)-1)/2;
    int k = ((int)key->m) + ((int)key->n);                
    return abs((int)(size*(k*A-(int)(k*A))));
}

int find_position(HashTable *t, Key *key)   {
    //collisions gerees par probing lineaire
    assert(key != NULL);
    int indice = hash_function(key, t->size);
    assert(indice >= 0);
    
    int i=0;
    while(i < t->size)    {
        assert(((indice + i) % t->size) >= 0);
        //on parcourt au plus toute la table a partir de la case indice (hash + 0)
        if (t->tab[(indice + i) % t->size] != NULL) {
            //key->m correspond a key->val (le nom etait dans les exemples et non dans l'enonce)
            if (  (t->tab[(indice + i) % t->size]->key->m == key->m) && (t->tab[(indice + i) % t->size]->key->n == key->n)  ) {
                return (indice + i) % t->size; //la cle est deja presente dans la table
            } 
        } else { 
            return (indice + i) % t->size; //emplacement libre pour inserer la cle
        }
        i++;
    }
    fprintf(stderr,"Erreur : find_position : pas de position trouvee\n");
    return -1;  //indication d'erreur
}

HashTable *create_hashtable(CellKey *keys, int size)    {
    //creation de la table de hachage
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->tab = (HashCell **)malloc(size*sizeof(HashCell *));
    for (int i=0; i<size; i++)  {
        table->tab[i] = NULL;
    }
    table->size = size;

    //insertion des cles de la liste keys
    int pos;
    while (keys)    {
        pos = find_position(table, keys->data);

        if (pos == -1)  {
            fprintf(stderr, "Erreur : create_hashtable, pas de position trouvee\n");
            for (int i=0; i<table->size; i++)   {
                free(table->tab[i]);
            }
            free(table->tab);
            free(table);
            return NULL;
        }
        //Si la cle n'est pas dans la table on l'ajoute
        if (table->tab[pos] == NULL)    {    
            HashCell *candidate = create_hashcell(keys->data);
            table->tab[pos] = candidate;
        }
        keys = keys->next;
    }
    return table;
}

void delete_hashtable(HashTable *t) {
    for (int i=0; i<t->size; i++)   {
        //on ne libere pas la cle
        free(t->tab[i]);
    }
    free(t->tab);
    free(t);
}

Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)    {
    //verification de sizeC >= len(candidates) && sizeV >= len(voters)
    assert(   (sizeC >= listKeyLength(candidates))   &&   (sizeV >= listKeyLength(voters))   );

    //creation des deux tables de hachage
    HashTable *hc = create_hashtable(candidates,sizeC);
    HashTable *hv = create_hashtable(voters, sizeV);

    //parcours des declarations
    int posV, posC;
    Key *keyC;
    while (decl)    {
        posV = find_position(hv, decl->data->pKey); 
        if (hv->tab[posV] != NULL)   {
            if (hv->tab[posV]->val == 0) {            //il n'a jamais vote
                keyC = str_to_key(decl->data->mess);
                posC = find_position(hc,keyC);
                free(keyC);
                if(hc->tab[posC] != NULL)   {     //si le candidat existe
                    hv->tab[posV]->val = 1;       //il a vote
                    hc->tab[posC]->val = hc->tab[posC]->val + 1; //le candidat a un vote de plus              

                }
            }   
        }
        decl = decl->next;
    }

    //determination du gagnant    //ET SI DEUX CANDIDATS SONT EX AEQUO --on prend le premier dans la table
    HashCell *gagnant = NULL;
    int val_gagnant = -1;
    for (int i=0; i<hc->size; i++)  {
        if (hc->tab[i] != NULL){
            if (val_gagnant < hc->tab[i]->val) {
                gagnant = hc->tab[i];
                val_gagnant = hc->tab[i]->val;
            }
        }
    }
    if (gagnant == NULL){
        fprintf(stderr,"Erreur : compute_winner : gagnant null");
    }

    Key *g = gagnant->key;
    //on ne free pas les cles qui sont stockes egalement dans les listes 
    delete_hashtable(hc);   
    delete_hashtable(hv);
    return g;
}


void afficher_tableH(HashTable *t)  {
    //fonction de test
    printf("La taille de la table est %d\n", t->size);
    for (int i=0; i<t->size; i++)   {
        if (t->tab[i] == NULL)  {
            printf("tab[%d] est null\n", i);
        } else {
            char * key = key_to_str(t->tab[i]->key);
            printf("tab[%d] = key : %s, val : %d\n", i, key, t->tab[i]->val);
            free(key);
        }
    }
}

int listKeyLength(CellKey *list)    {
    //Pour vérifier la longueur de la liste de cles
    //utilise dans compute_winner
    if (!list)  {
        return 0;
    }
    return 1 + listKeyLength(list->next);
}

int listDeclarationLength(CellProtected *list)    {
    //Pour vérifier la longueur de la liste de cles
    if (!list)  {
        return 0;
    }
    return 1 + listDeclarationLength(list->next);
}


