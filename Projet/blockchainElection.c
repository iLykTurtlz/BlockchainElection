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
    int nbVoters = 20, nbCandidates = 5;
    generate_random_data(nbVoters, nbCandidates);
    printf("\nOn genere %d electeurs et %d candidats.\n",nbVoters,nbCandidates);

    //lire les cles publiques des candidats et de tout le monde
    CellKey *candidates = read_public_keys("candidates.txt");
    CellKey *publicKeys = read_public_keys("keys.txt");

    //lire les declarations de vote
    CellProtected *votes = read_protected("declarations.txt");

    //rajout d'une fraude
    //TO DO

    //soumission de tous les votes et rajout dans l'arbre
    printf("\nOperation en cours : soumission des votes\n");
    CellTree *tree = NULL;  
    int d = 2;  //nombre de bits a 0

    int i, nbFichier = 1, votesParBlock = 10;
    char nomFichier[256];
    CellProtected *current = votes;
    Protected *pr;
    Key *cleAssesseur = NULL;
    
    while (current)   {
        i=0;
        cleAssesseur = current->data->pKey; //la cle de l'assesseur est la cle du premier a voter dans le block
        char *cleAssesseurStr = key_to_str(cleAssesseur);
        Key *cleAssesseurCopie = str_to_key(cleAssesseurStr);
        free(cleAssesseurStr);
        while (current && i<votesParBlock)   {
            pr = current->data;
            submit_vote(pr);
            current = current->next;
            i++;
        }
        create_block(&tree,cleAssesseurCopie,d);
        sprintf(nomFichier,"fichier%d",nbFichier);
        add_block(d,nomFichier);
        nbFichier++;
    }
    printf("\nFin de l'operation de soumission des votes\n");

    //Ayant enregistre les fichiers dans Blockchain on peut supprimer l'arbre de construction
    printf("\nAffichage de l'arbre de construction :\n");
    print_tree(tree);
    delete_tree(tree);

    //Lecture du repertoire Blockchain, re-creation et affichage de l'arbre
    tree = read_tree();
    printf("\nAffichage de l'arbre provenant du repertoire Blockchain :\n");
    print_tree(tree);
  
    //determination du gagnant
    Key *gagnant = compute_winner_BT(tree, candidates, publicKeys,nbCandidates*2,nbVoters*2);

    char *g = key_to_str(gagnant);
    printf("\n%s a gagne\n\n",g);

    free(g);
    delete_tree(tree);
    //delete_list_protected_total(votes);
    delete_list_protected(votes);
    delete_list_keys(candidates);
    delete_list_keys(publicKeys);


    return 0;
}