#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main()  {
    //fonction donnée par l énoncé
    const char *s = "Rosetta code";
    printf("\nAffichage du message chiffre de l'enonce :\n");
    unsigned char *d = SHA256( (const unsigned char*)s,strlen(s),0);
    int i;
    for (i=0; i<SHA256_DIGEST_LENGTH; i++)  {
        printf("%02x",d[i]);
    }
    putchar('\n');

    //fonction test de blockchain
    printf("\nAffichage du message chiffre par notre fonction hash_function_block :\n");
    unsigned char *res = hash_function_block(s);
    printf("%s\n",res);
    free(res);

    return 0;
}

