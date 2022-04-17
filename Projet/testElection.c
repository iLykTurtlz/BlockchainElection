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



int main(void)  {
    srand(time(NULL));

    int nbCandidates = 3, nbElecteurs = 10;
    generate_random_data(nbElecteurs, nbCandidates);

    //lire les cles publiques des candidats et de tout le monde
    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");

    //afficher ces clefs
/*
    printf("\nCles publiques des candidats :\n");
    print_list_keys(candidates);
    printf("\nCles publiques de tout le monde:\n");
    print_list_keys(publicKeys);
*/
    //lire les declarations de vote
    CellProtected *votes = read_protected("declarations.txt");

    //afficher les declarations
/*  
  printf("\nDeclarations de vote :\n");
    print_list_protected(votes);

    //rajout d'une fraude
    printf("\nAvec une declaration frauduleuse :\n");
    char *KeyStr = key_to_str(candidates->data); 
    Protected *pr = init_protected( publicKeys->data, KeyStr, sign(KeyStr,publicKeys->next->data) );
    add_protected(&votes,pr);
    print_list_protected(votes);
    free(KeyStr);

    //verifier qu'il n'y ait pas eu de hacking
    thwarted(&votes);
    printf("\nDeclarations de vote apres verification :\n");
    print_list_protected(votes);
  
    //determination du gagnant
    Key *gagnant = compute_winner(votes, candidates, publicKeys, nbCandidates*2, nbElecteurs*2);

    char *g = key_to_str(gagnant);
    printf("\n%s a gagne\n\n",g);

  
  free(g);
*/

    delete_list_protected_total(votes);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);

    return 0;
}
