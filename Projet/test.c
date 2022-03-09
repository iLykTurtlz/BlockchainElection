#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"
#include "rsa.h"

void print_long_vector(long *result, int size) { 
    printf("Vector: [");
    for (int i=0; i<size; i++){
        printf("%ld \t", result[i]);
    }
    printf("]\n"); 
}

int main()  {

    /*tests de generationClef.c*/

    /*
    long p,q,n,s,u;
    int k = 20;
    p = random_prime_number(30,32,k);
    q = random_prime_number(30,32,k);
    if (p == -1)    {
        fprintf(stderr,"erreur : p non premier\n");
    }
     if (q == -1)    {
        fprintf(stderr,"erreur : q non premier\n");
    }

    generate_key_values(p,q,&n,&s,&u);
    printf("Clef publique : (s,n) = (%ld,%ld), clef privée : (u,n) = (%ld,%ld)\n",s,n,u,n);
    */


    /*tests de rsa.c*/

    srand(time(NULL));
    //Generation de cle :
    long p = random_prime_number(3,7,5);
    long q = random_prime_number(3,7,5); 
    while(p==q) {
        q = random_prime_number(3,7,5);
    }
    long n, s, u;
    generate_key_values(p,q,&n,&s,&u);
    //Pour avoir des cles positives : 
    if (u<0) {
        long t = (p-1)*(q-1);
        u = u+t; //on aura toujours s*u mod t = 1
    }

    //Affichage des cles en hexadecimal
    printf("cle publique = (%lx , %lx ) \n",s,n); 
    printf("cle privee = (%lx , %lx) \n",u,n);

    //Chiffrement:
    char mess[10] = "Hello";
    int len = strlen(mess);
    long* encrypted = encrypt(mess, s, n);
    printf("Initial message : %s\n", mess);
    printf("Encoded representation :\n");
    print_long_vector(encrypted, len);

    //Dechiffrement
    char* decoded = decrypt(encrypted, len, u, n);
    printf("Decoded : %s\n", decoded);




    return 0; 

}