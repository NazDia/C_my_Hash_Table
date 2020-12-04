#ifndef DICTIONARY_BY_ND
#define DICTIONARY_BY_ND

typedef struct hash_t_elem{
    void * key;
    void * elem;
    void * next;
    int depth;
}hash_t_elem;

typedef struct hash_table{
    int (* hashing)(void *, void *, int (* )(void *, void *));
    int (* insert)(void *, void *, void *, int(* )(void *, void *));
    void * (* remove)(void * ,void *, int(* )(void *, void *));
    void * (* value_of)(void *, void *, int(* )(void *, void *));
    void ** keys;
    hash_t_elem * values;
    int count;
    int max_depth;
}hash_table;

hash_table * create_hash_table(int max_depth, int (* )(void *), int (* )(void *, void *));

#endif