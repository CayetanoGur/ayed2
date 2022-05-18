#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
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
    if(tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }else {
        if (elem_less(e, tree->elem)){
            tree->left = abb_add(tree->left, e); 

        }else if (elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right, e);
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree){
    bool is_empty;
    assert(invrep(tree));
    if(tree == NULL){
        is_empty = true;
    }
    else{
        is_empty = false;
    }
    return is_empty;
}


bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    exists = ((tree != NULL) && 
             elem_eq(e,tree->elem)) ||
             (elem_less(tree->elem, e) && abb_exists(tree->right,e)) ||
             (elem_less(e,tree->elem) && abb_exists(tree->left,e));
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree != NULL){
        length = length + 1;
        abb_length(tree->left);
        abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) ||  length > 0));
    return length;
}

static abb abb_del_max(abb tree){
    if (tree->right != NULL){
    abb_del_max(tree->right);
    }
    else{
        tree = tree->left;
    }
    return tree;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    //me falta if tree = NULL
    if(e < tree->elem){
        tree->left = abb_remove(tree->left, e);
    }
    else if(e > tree->elem){
        tree->right = abb_remove(tree->right, e);
    }
    else{
        if(tree->left == NULL){
            tree = tree->right;
        }
        else {  /*(tree->left != NULL)*/
        tree->elem = abb_max(tree->left);
        tree = abb_del_max(tree->left);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    //falta un if
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if(tree->right != NULL){
        max_e = abb_max(tree->right);
    }
    else{
        max_e = tree->elem;
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if(tree->left != NULL){
        min_e = abb_min(tree->left);
    }
    else{
        min_e = tree->elem;
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
    }
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

