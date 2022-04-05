#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "listDeclaration.h"
#include "winner.h"
#include "listKey.h"


void thwarted(CellProtected **LCP)  {
    if (!(*LCP))
        return;
    CellProtected *first = *LCP;
    CellProtected *prev = first;
    CellProtected *curr = first->next;

    while (curr)    {
        if (!verify(curr->data))  {
            prev->next = curr->next;
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
    assert(key != NULL);
    int indice = hash_function(key, t->size);
    fprintf(stderr,"indice = %d\n", indice);
    assert(indice >= 0);
    
    int i=0;
    while(i < t->size)    {
        assert(((indice + i) % t->size) >= 0);
        if (t->tab[(indice + i) % t->size] != NULL) {
            assert(((indice + i) % t->size) >= 0);
            assert(t->tab[(indice + i) % t->size] != NULL);
            assert(t->tab[(indice + i) % t->size]->key != NULL);
            assert(key != NULL);

            if (  (t->tab[(indice + i) % t->size]->key->m == key->m) && (t->tab[(indice + i) % t->size]->key->n == key->n)  ) {
                return (indice + i) % t->size;
            } 
        } else { 
            return (indice + i) % t->size;
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
        pos = find_position(table, keys->data);                 //invalid read of size 8
        HashCell *candidate = create_hashcell(keys->data);
        table->tab[pos] = candidate;
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

    //TO DO

    //creation des deux tables de hachage

    HashTable *hc = create_hashtable(candidates,sizeC);
    HashTable *hv = create_hashtable(voters, sizeV);

    fprintf(stderr,"hash tables created\n");
    
    //parcours des declarations
    int posV, posC;
    while (decl)    {
        fprintf(stderr,"tour %d\n", i);
        printf("tour %d\n",i);
        posV = find_position(hv, decl->data->pKey); 
        if (hv->tab[posV] != NULL)   {
            if (hv->tab[posV]->val == 0) {            //il n'a jamais vote
                Key *keyC = str_to_key(decl->data->mess);
                posC = find_position(hc,keyC);
                if(hc->tab[posC] != NULL)   {
                    hv->tab[posV]->val = 1;
                    hc->tab[posC]->val = hc->tab[posC]->val + 1;                 

                }
            }   
        }
        fprintf(stderr,"fin tour %d\n",i);
        printf("fin tour %d\n",i);
        i++;
        decl = decl->next;
    }

    //determination du gagnant    //ET SI DEUX CANDIDATS SONT EX AEQUO ???

    //afficher_tableH(hc);

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


