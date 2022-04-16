#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blockchain.h"
#include "listDeclaration.h"
#include "generationClef.h"
#include "manipulationClefs.h"
#include "donneesVote.h"
#include "listKey.h"
#include "declaration.h"
#include "generationNbPremier.h"
#include "rsa.h"
#include "testMillerRabin.h"
#include "signature.h"
#include "outilsMathematiques.h"



int main()    {
    srand(time(NULL));

    FILE *ostream = fopen("proofOfWork.txt","w");
    if (ostream == NULL)    {
        fprintf(stderr, "Erreur a l'ouverture du fichier\n");
        exit(1);
    }

    //variables pour mesurer le temps
    clock_t temps_initial, temps_final;
    double temps;

    //donnees pour creer un block
    generate_random_data(10,2);
    CellKey *publicKeys = read_public_keys("keys.txt");
    CellProtected *votes = read_protected("declarations.txt");

    unsigned char c1[4] = "001";
    unsigned char c2[4] = "100";

    //on cree juste un bloc avec le premier CellKey
    Block *b = creerBlock(publicKeys->data, votes, c1,c2,0);
    char *strBlock = block_to_str(b);

    //on fait 5 tests par nombre de zeros
    for (int nbZeros=0; nbZeros<4; nbZeros++)   {
        for (int i=0; i<5; i++)	{
            temps_initial = clock();
            compute_proof_of_work(b,nbZeros);
            temps_final = clock();
            temps = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
            fprintf(ostream,"%d %f\n",nbZeros,temps);
        }
    }

    free(strBlock);
    free(b->hash);
    free(b->previous_hash);
    delete_list_keys(publicKeys);
    delete_list_protected(votes);
    fclose(ostream);
    return 0;
}
