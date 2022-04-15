#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "blockchain.h"
#include "blockTree.h"

CellTree *create_node(Block *b) {
    CellTree *new = (CellTree *)malloc(sizeof(CellTree));
    new->block = b;
    new->father = NULL;
    new->firstChild = NULL;
    new->nextBro = NULL;
    new->height = 0;
    return new;
}

int update_height(CellTree *father, CellTree *child)    {
    //???
}

void add_child(CellTree *father, CellTree *child)   {

}

void print_tree(CellTree *tree) {
    
}

void delete_node(CellTree *node)    {
    delete_block(node->block);
    free(node);
}