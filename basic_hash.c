#include<string.h>

unsigned int hash_float(void * param){
    float number = *(float *)param;
    unsigned int ui;
    memcpy(&ui, &number, sizeof(float));
    return (ui >> 12) * 31;
}

unsigned int hash_int_like(void * param){
    unsigned int number = *(unsigned int *)param;
    return 31 * number;
}

unsigned int hash_char(void * param){
    char ch = *(char *)param;
    if ((unsigned int)('\00' + '\00' + '\00' + '\01') == 1){
        return 31 * (unsigned int)('\00' + '\00' + '\00' + ch);
    }
    else{
        return 31 * (unsigned int)(ch + '\00' + '\00' + '\00');
    }
}

unsigned int hash_string(void * param){
    char * string = *(char **)param;
    unsigned int ret = 0;
    for (int i = 0; i < sizeof(string) / sizeof(char); i++){
        ret += hash_char(&string[i]);
    }
    return ret;
}

unsigned int hash_ref(void * param){
    unsigned int ref_pos = (unsigned int)(param) >> 3;
    return ref_pos;
}

unsigned int mixed_hash(void * param){
    int * sub_param_i = (int *)param;
    if (sub_param_i != NULL){
        return hash_int_like(sub_param_i);
    }
    float * sub_param_f = (float *)param;
    if (sub_param_f != NULL){
        return hash_float(sub_param_f);
    }
    char * sub_param_c = (char *)param;
    if (sub_param_c != NULL){
        return hash_char(sub_param_c);
    }
    char ** sub_param_s = (char **)param;
    if (sub_param_s != NULL){
        return hash_string(sub_param_s);
    }
    return hash_ref(param);
}


short int basic_equals(void * param1, void * param2){
    if ((int *)param1 != NULL){
        if ((int *)param2 != NULL){
            return hash_int_like(param1) == hash_int_like(param2);
        }
        else{
            return 0;
        }
    }
    else if ((float *)param1 != NULL){
        if ((float *)param2 != NULL){
            return hash_float(param1) == hash_float(param2);
        }
        else{
            return 0;
        }
    }
    else if ((char *)param1 != NULL){
        if ((char *)param2 != NULL){
            return hash_char(param1) == hash_char(param2);
        }
        else{
            return 0;
        }
    }
    else if ((char **)param1 != NULL){
        if ((char **)param2 != NULL){
            return hash_string(param1) == hash_string(param2);
        }
        else{
            return 0;
        }
    }
    else{
        return hash_ref(param1) == hash_ref(param2);
    }
}