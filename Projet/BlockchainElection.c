#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "donneesVote.h"
#include "blockchain.h"
#include "blockTree.h"
#include "winner.h"

int main()  {
    srand(time(NULL));

    //generation de donnees
    int nbVoters = 1000, nbCandidates = 5;
    generate_random_data(nbVoters, nbCandidates);

    //lire les cles publiques des candidats et de tout le monde
    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");

    //lire les declarations de vote
    CellProtected *votes = read_protected("declarations.txt");

    //rajout d'une fraude
    printf("\nAvec une declaration frauduleuse :\n");
    char *KeyStr = key_to_str(candidates->data); 
    Protected *pr = init_protected( publicKeys->data, KeyStr, sign(KeyStr,publicKeys->next->data) );
    add_protected(&votes,pr);
    print_list_protected(votes);
    free(KeyStr);

    //soumission de tous les votes et rajout dans l'arbre
    CellTree *tree = NULL;  
    int d = 3;  //nombre de bits a 0

    int i, nbFichier = 1, votesParBloc = 10;
    char nomFichier[256];
    CellProtected *current = votes;
    Protected *pr;
    Key *cleAssesseur = NULL;
    while (current)   {
        i=0;
        cleAssesseur = current->data->pKey;
        while (current && i<votesParBloc)   {
            pr = votes->data;
            submit_vote(pr);
            current = current->next;
            i++;
        }
        create_block(tree,cleAssesseur,d);
        sprintf(nomFichier,"fichier%d",nbFichier);
        add_block(d,nomFichier);
        nbFichier++;
    }

    //Lecture du repertoire Blockchain et creation de l'arbre
    read_tree();
        




    //verifier qu'il n'y ait pas eu de hacking
    thwarted(&votes);
    printf("\nDeclarations de vote apres verification :\n");
    print_list_protected(votes);
  
    //determination du gagnant
    Key *gagnant = compute_winner(votes, candidates, publicKeys, nbCandidates*2, nbElecteurs*2);

    char *g = key_to_str(gagnant);
    printf("\n%s a gagne\n\n",g);

    free(g);
    delete_list_protected_total(votes);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);







    return 0;
}