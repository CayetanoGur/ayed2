#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

#define min(a, b) a < b ? a : b

struct _s_string {
    char *content;
    unsigned int length; // Length of the string with out counting '\0' at the end
};

static bool inv_rep(string str) {
    return(str != NULL && strlen(str->content) == str->length);
}

string string_create(const char *word) {
    string str = calloc(1, sizeof(struct _s_string));
    str->length = strlen(word);
    str->content = calloc(str->length + 1u, sizeof(char));
    str->content = strncpy(str->content, word, str->length + 1u);
    assert(inv_rep(str)); return (str);
}

unsigned int string_length(string str) {
    assert(inv_rep(str));
    return (str->length);
}

bool string_less(const string str1, const string str2) {
    assert(inv_rep(str1) && inv_rep(str2));
    unsigned int min_length = min(str1->length, str2->length);
    unsigned int j = 0u;
    while (j < min_length && (str1->content)[j] == (str2->content)[j]) {
        ++j;
    }
    return (str1->content)[j] < (str2->content)[j];
}

bool string_eq(const string str1, const string str2) {
    assert(inv_rep(str1) && inv_rep(str2));
    int cmp = strcmp(str1->content, str2->content);
    return (cmp == 0);
}

string string_clone(const string str) {
    assert(inv_rep(str));
    return (string_create(str->content));
}

string string_destroy(string str) {
    assert(inv_rep(str));
    free(str->content);
    free(str); str = NULL;
    return (str);
}

void string_dump(string str, FILE *file) {
    assert(inv_rep(str));
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str) {
    assert(inv_rep(str));
    return (str->content);
}
