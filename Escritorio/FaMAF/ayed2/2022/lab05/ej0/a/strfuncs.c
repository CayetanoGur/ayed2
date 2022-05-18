#include "strfuncs.h"
#include <stdio.h>
/*lenth of the string pointed by str*/
size_t string_length(const char *str){
    size_t i = 0u;
    while(str[i] != '\0'){
        ++i;
    }
    return i;
}

/*filters all the characters C that are inside the string poited by str*/
char *string_filter(const char *str, char c){
    const size_t size = string_length(str);
    char *res = malloc(sizeof(str) * size);
    unsigned int i = 0u;
    unsigned int j = 0u;
    while (str[i] != '\0'){
        if (str[i] != c){
            res[j] = str[i];
            ++j;
        }
        ++i;
        
    }
    //hacer un realloc
    size_t size_res = string_length(res);
    printf("size of res before realloc: %ld\n", size);
    res = realloc(res, sizeof(str)*size_res);
    printf("size of res after realloc: %ld\n", size_res);
    return res;
}

