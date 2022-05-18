#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool gen_invrep_min_max(abb tree, abb_elem min, abb_elem max) {
    return(tree == NULL
            || (elem_less(min, tree->elem) && elem_less(tree->elem, max)
                && gen_invrep_min_max(tree->left, min, tree->elem)
                && gen_invrep_min_max(tree->right, tree->elem, max)
               )
    );
}

static bool gen_invrep_min(abb tree, abb_elem min) {
    return(tree == NULL
            || (elem_less(min, tree->elem)
                && gen_invrep_min_max(tree->left, min, tree->elem)
                && (gen_invrep_min(tree->right, tree->elem))
               )

    );
}

static bool gen_invrep_max(abb tree, abb_elem max) {
    return(tree == NULL
            || (elem_less(tree->elem, max)
                && gen_invrep_max(tree->left, tree->elem)
                && gen_invrep_min_max(tree->right, tree->elem, max)
               )
    );
}

static bool invrep(abb tree) {
    return(tree == NULL
            || (gen_invrep_max(tree->left, tree->elem)
                 && gen_invrep_min(tree->right, tree->elem)
               )
    );
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL) {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if(elem_less(e, tree->elem)) {
        tree->left = abb_add(tree->left, e);
    }
    else if(elem_less(tree->elem, e)) {
        tree->right = abb_add(tree->right, e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    bool is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));
    return (!abb_is_empty(tree)
                && (e == tree->elem || (elem_less(e, tree->elem) && abb_exists(tree->left, e))
                                    || (elem_less(tree->elem, e) && abb_exists(tree->right, e))
                   )
           );
}

unsigned int abb_length(abb tree) {
    assert(invrep(tree));
    unsigned int length = abb_is_empty(tree) ? 0u : 1 + abb_length(tree->left) + abb_length(tree->right);
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0u));
    return length;
}

/* PRE: !abb_is_empty(*tree) */
static abb_elem obtain_max_and_remove(abb* tree) {
    assert(tree != NULL && *tree != NULL);
    abb_elem out = 0u;
    abb temp = NULL;
    if((*tree)->right == NULL) {
        out = (*tree)->elem;
        temp = *tree;
        (*tree) = (*tree)->right;
        free(temp); temp = NULL;
    }
    else {
        out = obtain_max_and_remove(&((*tree)->right));
    }
    return(out);
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    abb temp = NULL;
    if(tree != NULL) {
        if(elem_eq(tree->elem, e)) {
            if(tree->left == NULL) {
                temp = tree;
                tree = tree->right;
                free(temp); temp = NULL;
            }
            else {
                tree->elem = obtain_max_and_remove(&(tree->left));
            }
        }
        else if(elem_less(e, tree->elem)) {
            tree->left = abb_remove(tree->left, e);
        }
        else {
            tree->right = abb_remove(tree->right, e);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem root  = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem max_e = abb_is_empty(tree->right) ? tree->elem : abb_max(tree->right);
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem min_e = abb_is_empty(tree->left) ? tree->elem : abb_min(tree->left);
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree != NULL) {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree); tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

