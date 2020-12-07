#ifndef BASIC_HASH_BY_ND
#define BASIC_HASH_BY_ND

unsigned int hash_float(void * param);

unsigned int hash_int_like(void * param);

unsigned int hash_char(void * param);

unsigned int hash_string(void * param);

unsigned int hash_ref(void * param);

unsigned int mixed_hash(void * param);

short int basic_equals(void * param1, void * param2);

#endif