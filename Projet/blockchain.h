#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "listDeclaration.h"
#include "manipulationClefs.h"


typedef struct block    {
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;

Block *creerBlock(Key *author, CellProtected *votes, unsigned char hash, unsigned char previous_hash, int nonce);
void enregistrerBlock(char *filename, Block *block);
Block *lireBlock(char *filename);
char *block_to_str(Block *block);


#endif