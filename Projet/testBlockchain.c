#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listDeclaration.h"
#include "manipulationClefs.h"
#include "donneesVote.h"
#include "blockchain.h"
#include "listKey.h"

int main()  {
    srand(time(NULL));
    generate_random_data(16,2);
    
    CellKey *publicKeys = read_public_keys("keys.txt");

    CellProtected *votes = read_protected("declarations.txt");

    unsigned char c1[4] = "001";
    unsigned char c2[4] = "100";

    //on cree juste un bloc avec le premier CellKey
    Block *b = creerBlock(publicKeys->data, votes, c1,c2,0);


    char *strBlock = block_to_str(b);
    printf("Affichage du block : author, previous_hash, votes, nonce : \n");
    printf("\n%s\n",strBlock);
    free(strBlock);

    printf("Verification du block, d=4 (doit etre fausse) : %d\n",verify_block(b,4));

    int nbZero = 3;
    printf("\nAffichage de hash avant compute_proof_of_work : %s\n", b->hash);
    compute_proof_of_work(b,nbZero);
    printf("\nAffichage de hash après compute_proof_of_work (avec nb zero = %d): %s\n", nbZero, b-> hash);
    printf("\nAffichage du block après compute_proof_of_work : \n");
    strBlock = block_to_str(b);
    printf("\n%s\n",strBlock);
    printf("\n"); 
    printf("Verification du block, d = 3 (doit etre vraie) : %d\n",verify_block(b,nbZero));

    free(strBlock);
    free(b->hash);
    free(b->previous_hash);
    free(b);
    delete_list_protected_total(votes);
    delete_list_keys(publicKeys);
    return 0;
}
