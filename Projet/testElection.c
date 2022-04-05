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
    int nbCandidates = 3, nbElecteurs = 10;

    srand(time(NULL));
    generate_random_data(nbElecteurs, nbCandidates);

    //lire les cles publiques des candidats et de tout le monde
    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");

    

    //afficher ces clefs
    printf("Cles publiques des candidats :\n");
    print_list_keys(candidates);
    printf("Cles publiques de tout le monde:\n");
    print_list_keys(publicKeys);


    //lire les declarations de vote
    CellProtected *votes = read_protected("declarations.txt");

    //afficher les declarations
    printf("Declarations de vote :\n");
    print_list_protected(votes);

    //verifier qu'il n'y ait pas eu de hacking
    thwarted(&votes);
    printf("Declarations de vote apres verification :\n");
    print_list_protected(votes);
  
    //determination du gagnant
    Key *gagnant = compute_winner(votes, candidates, publicKeys, nbCandidates*2, nbElecteurs*2);
    
    char *g = key_to_str(gagnant);
    printf("%s a gagne\n",g);


    free(g);
    
    delete_list_protected(votes);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);



    return 0;
}
