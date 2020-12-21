#ifndef BASIC_HASH_BY_ND
#define BASIC_HASH_BY_ND

extern unsigned int hash_float(void * param);

extern unsigned int hash_int_like(void * param);

extern unsigned int hash_char(void * param);

extern unsigned int hash_string(void * param);

extern unsigned int hash_ref(void * param);

extern unsigned int mixed_hash(void * param);

extern short int basic_equals(void * param1, void * param2);

#endif