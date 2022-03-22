#ifndef MANIPULATIONCLEFS_H
#define MANIPULATIONCLEFS_H

typedef struct  {
    long m;
    long n;
} Key;

void init_key(Key *key, long val, long n);
void init_pair_keys(Key *pkey, Key *skey, long min_size, long max_size);



#endif