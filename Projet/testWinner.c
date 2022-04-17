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
    srand(time(NULL));

    //On verifie la creation d'une table de hachage
    printf("\nOn cree, affiche et detruit une table de hachage\n");
    HashTable *t1 = create_hashtable(NULL, 10);
    afficher_tableH(t1);
    delete_hashtable(t1);
    
    //On genere des donnees
    int nbCandidates = 3, nbElecteurs = 10;
    generate_random_data(nbElecteurs, nbCandidates);
    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");
    CellProtected *votes = read_protected("declarations.txt");

    //On cree les tables qui contiennent les cles publiques soit des electeurs ou soit des candidats
    HashTable *t2 = create_hashtable(candidates, 2*nbCandidates);
    HashTable *t3 = create_hashtable(publicKeys, 2*nbElecteurs);
    printf("\nTable candidats (%d candidats) :\n",nbCandidates);
    afficher_tableH(t2);
    printf("\nTable electeurs (%d electeurs) :\n", nbElecteurs);
    afficher_tableH(t3);

    //Affichage des declarations
    printf("\nDeclarations de vote :\n");
    print_list_protected(votes);

    //Verification de la fonction compute_winner
    printf("\nDebut compute_winner\n");
    Key *gagnant = compute_winner(votes, candidates, publicKeys, nbCandidates*2, nbElecteurs*2);
    char *gagnantStr = key_to_str(gagnant);
    printf("\nFIN COMPUTE_WINNER : le gagnant est %s\n\n",gagnantStr);
    free(gagnantStr);

    delete_hashtable(t2);
    delete_hashtable(t3);
    
    delete_cell_protected_total(votes);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);
    return 0;
}