#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "listDeclaration.h"
#include "manipulationClefs.h"
#include <openssl/sha.h>


typedef struct block    {
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;



Block *creerBlock(Key *author, CellProtected *votes, unsigned char *hash, unsigned char *previous_hash, int nonce);
void write_block(char *filename, Block *block);
Block *lireBlock(char *filename);
char *block_to_str(Block *block);
unsigned char* hash_function_block(const char* str);
int count_zeros(unsigned char* str);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block *B, int d);
void delete_block(Block *B);

#endif
