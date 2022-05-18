#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"
#include "string.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};


static bool gen_invrep_min_max(dict_t d, string min, string max) {
    return(d == NULL
            || (string_less(min, d->key) && string_less(d->key, max)
                && gen_invrep_min_max(d->left, min, d->key)
                && gen_invrep_min_max(d->right, d->key, max)
               )
    );
}

static bool gen_invrep_min(dict_t d, string min) {
    return(d == NULL
            || (string_less(min, d->key)
                && gen_invrep_min_max(d->left, min, d->key)
                && (gen_invrep_min(d->right, d->key))
               )

    );
}

static bool gen_invrep_max(dict_t d, string max) {
    return(d == NULL
            || (string_less(d->key, max)
                && gen_invrep_max(d->left, d->key)
                && gen_invrep_min_max(d->right, d->key, max)
               )
    );
}

static bool invrep(dict_t d) {
    return(d == NULL
            || (gen_invrep_max(d->left, d->key)
                 && gen_invrep_min(d->right, d->key)
               )
    );
}


dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if(dict == NULL) {
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    }
    else if(string_less(word, dict->key)) {
        dict->left = dict_add(dict->left, word, def);
    }
    else if(string_less(dict->key, word)) {
        dict->right = dict_add(dict->right, word, def);
    }
    else { // In these case, string_eq(word, dict->key)
        dict->value = value_destroy(dict->value);
        dict->value = def;
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}


value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    key_t def = dict == NULL                 ? NULL
              : string_eq(word, dict->key)   ? dict->value
              : string_less(word, dict->key) ? dict_search(dict->left, word)
              : /* otherwise */                dict_search(dict->right, word);
//    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    return(dict_search(dict, word) != NULL);
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    return(dict == NULL ? 0u
         /* otherwise */: 1 + dict_length(dict->left) + dict_length(dict->right));
}


struct key_value {
    string key;
    string value;
};

/* PRE: !abb_is_empty(*tree) */
static struct key_value obtain_max_and_remove(dict_t* dict) {
    assert(dict != NULL && *dict != NULL);
    struct key_value out;
    dict_t temp = NULL;
    if((*dict)->right == NULL) {
        out.key = (*dict)->key;
        out.value = (*dict)->value;
        temp = *dict;
        (*dict) = (*dict)->right;
        free(temp); temp = NULL;
    }
    else {
        out = obtain_max_and_remove(&((*dict)->right));
    }
    return(out);
}

dict_t dict_remove(dict_t dict, string word) {
    assert(invrep(dict));
    dict_t temp = NULL;
    if(dict != NULL) {
        if(string_eq(dict->key, word)) {
            if(dict->left == NULL) {
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                temp = dict;
                dict = dict->right;
                free(temp); temp = NULL;
            }
            else {
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                struct key_value max = obtain_max_and_remove(&(dict->left));
                dict->key = max.key;
                dict->value = max.value;
            }
        }
        else if(string_less(word, dict->key)) {
            dict->left = dict_remove(dict->left, word);
        }
        else {
            dict->right = dict_remove(dict->right, word);
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}


dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL) {
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        free(dict); dict = NULL;
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
/*         dict_dump(dict->left, file);
        fprintf(file, "Key: "); string_dump(dict->key, file);
        fprintf(file, "\nValue: "); string_dump(dict->value, file); fprintf(file, "\n");
        dict_dump(dict->right, file); */
    }
}

dict_t dict_destroy(dict_t dict) {
    return dict_remove_all(dict); // In this implementation, dict_remove_all and dict_destroy ar equal
}

