#ifndef BASIC_HASH_BY_ND
#define BASIC_HASH_BY_ND

extern long long hash_float(void * param);

extern long long hash_int_like(void * param);

extern long long hash_char(void * param);

extern long long hash_string(void * param);

extern long long hash_ref(void * param);

extern long long mixed_hash(void * param);

extern short int basic_equals(void * param1, void * param2);

#endif