#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main()  {
    //fonction donnée par l énoncé
    const char *s = "Rosetta code";
    unsigned char *d = SHA256( (const unsigned char*)s,strlen(s),0);
    int i;
    for (i=0; i<SHA256_DIGEST_LENGTH; i++)  {
        printf("%02x",d[i]);
    }
    putchar('\n');

    //fonction test de blockchain
    unsigned char *res = hash_function_block(s);
    for (i=0; i<SHA256_DIGEST_LENGTH; i++)  {
        printf("%02x",res[i]);
    }
    putchar('\n');

    return 0;
}

