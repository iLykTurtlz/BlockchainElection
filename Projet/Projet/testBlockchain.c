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
    Block *b = creerBlock(publicKeys->data, votes, c1,c2,8);


    char *strBlock = block_to_str(b);
    printf("Affichage du block : author, previous_hash, votes, nonce : \n");
    printf("%s\n",strBlock);
    free(b);
    return 0;
}