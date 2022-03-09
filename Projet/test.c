#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"

int main()  {
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
    return 0;


     void print_long_vector(long *result, int size){ printf(”Vector: [”);
for (int i=0; i<size; i++){




}
 printf(”]\n”); 7}

\ t ”, result[i]);
int main() {
printf(”%l x
srand(time(NULL));
//Generation de cle :
long p = random_prime_number(3,7, 5000); long q = random_prime_number(3,7, 5000); while(p==q){
q = random_prime_number(3,7, 5000); }
long n, s, u; generate_keys_values(p,q,&n,&s,&u); //Pour avoir des cles positives : if (u<0){
long t = (p-1)*(q-1);
u = u+t; //on aura toujours s*u mod t = 1 }
//Afichage des cles en hexadecimal
printf(” cle publique = (%lx , %lx ) \n”,s,n); printf(”cle privee = (%lx , %lx) \n”,u,n);
//Chiffrement:
char mess[10] = ” Hello ”;
int len = strlen(mess);
long* crypted = encrypt(mess, s,
printf(” Initial message : %s \n”, printf(”Encoded representation : print_long_vector(crypted, len);
//Dechiffrement
char* decoded = decrypt(crypted, printf(”Decoded : %s\n”, decoded);
return 0; 

}