#ifndef RSA_H
#define RSA_H

long *encrypt(char *chaine, long s, long n);
char *decrypt(long *encrypted, int size, long u, long n);


#endif