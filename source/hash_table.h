#ifndef DICTIONARY_BY_ND
#define DICTIONARY_BY_ND

typedef struct hash_t_elem{
    void * key;
    void * elem;
    struct hash_t_elem * next;
    int depth;
}hash_t_elem;

typedef struct hash_table
{
    short int (* equals)(void *, void *);
    unsigned int (* hashing)(void *);
    int (* insert)(void *, void *, void *);
    void * (* remove)(void * ,void *);
    void * (* value_of)(void *, void *);
    void ** keys;
    hash_t_elem * values;
    unsigned int count;
    unsigned int size;
    unsigned int max_depth;
}hash_table;

extern hash_table * create_hash_table(int max_depth, unsigned int (* )(void *), short int (* )(void *, void *));

#endif