#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listDeclaration.h"
#include "listKey.h"
#include "donneesVote.h"
#include "winner.h"

#include "manipulationClefs.h"
#include "generationClef.h"
#include "signature.h"
#include "declaration.h"
#include "rsa.h"
#include "outilsMathematiques.h"
#include "testMillerRabin.h"
#include "generationNbPremier.h"



int main()  {
    /*
    HashTable *t = create_hashtable(NULL, 10);
    afficher_tableH(t);


    delete_hashtable(t);
    */


    int nbCandidates = 3, nbElecteurs = 10;

    srand(time(NULL));
    generate_random_data(nbElecteurs, nbCandidates);

    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");

    /*
    CellKey *tmp = candidates;
    
    while (tmp) {
        char *key = key_to_str(tmp->data);
        printf("key : %s, hashfun : %d \n", key, hash_function(tmp->data,2*nbElecteurs));
        free(key);
        tmp = tmp->next;
    }
    */
    HashTable *t2 = create_hashtable(candidates, 2*nbCandidates);
    //afficher_tableH(t2);

    HashTable *t3 = create_hashtable(publicKeys, 2*nbElecteurs);
    //afficher_tableH(t3);

    delete_hashtable(t3);



    delete_hashtable(t2);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);

    return 0;
}