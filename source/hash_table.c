#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


typedef struct hash_t_elem
{
    void * key;
    void * elem;
    struct hash_t_elem * next;
    int depth;
}hash_t_elem;

typedef struct hash_table
{
    short int (* equals)(void *, void *);
    long long (* hashing)(void *);
    long long (* insert)(void *, void *, void *);
    void * (* remove)(void * ,void *);
    void * (* value_of)(void *, void *);
    void ** keys;
    hash_t_elem * values;
    unsigned int count;
    unsigned int size;
    unsigned int max_depth;
}hash_table;



void * get_elem(void * hash_t, void * param){
    hash_table * _hash_t = (hash_table *)hash_t;
    long long index = _hash_t->hashing(param);
    if (index < 0){
        return NULL;
    }
    hash_t_elem * current = &_hash_t->values[index];
    while (current != NULL)
    {
        if (_hash_t->equals(param, current->key)){
            return current->elem;
        }
        current = current->next;
    }
    return NULL;
}

void expand_hash_table(void * hash_t){
    hash_table * _hash_t = (hash_table *)hash_t;
    hash_t_elem * temp_tuples = _hash_t->values;
    hash_t_elem * new = malloc(sizeof(temp_tuples) * 2);
    _hash_t->values = new;
    _hash_t->size *= 2;
    for (int i = 0; i < sizeof(temp_tuples) / sizeof(hash_t_elem); i++){
        hash_t_elem * current = &temp_tuples[i];
        while (current != NULL)
        {
            void * key = current->key;
            void * value = current->elem;
            _hash_t->insert(hash_t, key, value);
            hash_t_elem * temp = current->next;
            free(current);
            current = temp;
        }
    }
    free(temp_tuples);
}

long long add(void * hash_t, void * key, void * value){
    hash_table * _hash_t = (hash_table *)hash_t;
    long long index = _hash_t->hashing(key) % _hash_t->size;
    if (index < 0){
        return -1;
    }
    _hash_t->count++;
    hash_t_elem * current = &_hash_t->values[index];
    if (current->depth == _hash_t->max_depth){
        expand_hash_table(hash_t);
        hash_t_elem * current = &_hash_t->values[index];
    }
    hash_t_elem * for_later = current;
    hash_t_elem * new = malloc(sizeof(hash_t_elem));
    new->key = key;
    new->elem = value;
    new->depth = 0;
    if (current == NULL){
        _hash_t->values[index] = *new;
        return index;
    }
    while (current->next != NULL)
    {
        if (_hash_t->equals(current->key, key)){
            current->elem = value;
            return index;
        }
        current = current->next;
    }
    while (for_later != NULL)
    {
        for_later->depth++;
        for_later = for_later->next;
    }
    current->next = new;
    return index;
}

void * del(void * hash_t, void * key){
    hash_table * _hash_t = (hash_table *) hash_t;
    long long index = _hash_t->hashing(key) % _hash_t->size;
    if (index < 0){
        return NULL;
    }
    hash_t_elem * prev = NULL;
    hash_t_elem * current = &_hash_t->values[index];
    hash_t_elem * for_later = current;
    while (current != NULL && current->key != key)
    {
        prev = current;
        current = (hash_t_elem *)current->next;
    }
    if (prev == NULL){
        _hash_t->values[index] = *(hash_t_elem *)current->next;
    }
    else
    {
        prev->next = current->next;
    }
    while (for_later != current->next && for_later != current)
    {
        for_later->depth--;
        for_later = for_later->next;
    }
    void * ret = current->elem;
    free(current);    
    _hash_t->count--;
    return ret;
}

hash_table * create_hash_table(int max_depth, long long(* hash)(void *), short int(* equals)(void *, void *)){
    hash_table * hash_t = (hash_table *)malloc(sizeof(hash_table));
    hash_t->equals = equals;
    hash_t->hashing = hash;
    hash_t->remove = del;
    hash_t->insert = add;
    hash_t->value_of = get_elem;
    hash_t_elem * vals = malloc(sizeof(hash_t_elem));
    hash_t->values = (void *)vals;
    void ** keys = malloc(sizeof(void *));
    hash_t->keys = keys;
    hash_t->count = 0;
    hash_t->max_depth = max_depth;
    hash_t->size = 1;
    return hash_t;
}