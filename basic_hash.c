#include<string.h>

int hash_float(void * param){
    float number = *(float *)param;
    unsigned int ui;
    memcpy(&ui, &number, sizeof(float));
    return (ui & 0xfffff000) * 31;
}

int hash_int_like(void * param){
    int number = *(int *)param;
    return 31 * number;
}

int hash_char(void * param){
    char ch = *(char *)param;
    if ((int)('\00' + '\00' + '\00' + '\01') == 1){
        return 31 * (int)('\00' + '\00' + '\00' + ch);
    }
    else{
        return 31 * (int)(ch + '\00' + '\00' + '\00');
    }
}

int hash_string(void * param){
    char * string = *(char **)param;
    int ret = 0;
    for (int i = 0; i < sizeof(string) / sizeof(char); i++){
        ret += hash_char(&string[i]);
    }
    return ret;
}

int hash_ref(void * param){
    int ref_pos = (int)(param) >> 3;
    return ref_pos;
}