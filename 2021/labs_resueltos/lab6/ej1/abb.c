#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
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

static bool is_abb(abb tree, abb_elem min, abb_elem max){
    bool b = true;
    if (tree != NULL){
        if(elem_less(tree->elem, min) || elem_less(max, tree->elem)){
            b = false;
        }
        else{
            b = is_abb(tree->left, min, tree->elem) && is_abb(tree->right, tree->elem, max);
        }
    }
    return b;
}


static abb_elem getMin(abb tree){
    abb_elem min;
    abb p = tree;
    while(p->left != NULL){
        p = p->left;
    }
    min = p->elem;
    return min;
}

static abb_elem getMax(abb tree){
    abb_elem max;
    abb p = tree;
    while(p->right != NULL){
        p = p->right;
    }
    max = p->elem;
    return max;
}

static bool invrep(abb tree){
    bool b = true;
    if(tree != NULL){
        abb_elem min = getMin(tree);
        abb_elem max = getMax(tree);
        b = is_abb(tree, min, max);
    }
    return b;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
 	abb p = NULL;
 	if(abb_is_empty(tree)){
 		p = malloc(sizeof(struct _s_abb));
 		p->elem = e;
 		p->right = NULL;
 		p->left = NULL;
 		tree = p;
        p = NULL;
 	}
 	else{
 		if(elem_less(tree->elem, e)){
 			tree->right = abb_add(tree->right, e);
 		}
 		else if(elem_less(e, tree->elem)){
 			tree->left = abb_add(tree->left, e);
 		}
 	}
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty = false;
    assert(invrep(tree));
    is_empty = (tree == NULL);
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists = false;
    assert(invrep(tree));
    if(tree != NULL){
    	if(elem_eq(tree->elem, e)){
    		exists = true;
    	}
    	else if(elem_less(tree->elem, e)){
    		exists = abb_exists(tree->right, e);
    	}
    	else{
    		exists = abb_exists(tree->left, e);
    	}
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length = 0u;
    assert(invrep(tree));
    if(tree != NULL){
    	length = (abb_length(tree->left) + abb_length(tree->right) + 1u);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

static abb min_tree_elem(abb tree){
    abb p = tree;
    while(p->left != NULL){
        p = p->left;
    }
    return p;
}

abb abb_remove(abb tree, abb_elem e){
    assert(invrep(tree));
    abb p = NULL;
    if(!abb_is_empty(tree)){
        if(elem_eq(tree->elem, e)){
            if(tree->right == NULL){
                p = tree;
                tree = tree->left;
                free(p);
                p = NULL;
            }
            else{
                p = min_tree_elem(tree->right);
                tree->elem = p->elem;
                tree->right = abb_remove(tree->right, p->elem);
            }
        }
        else if(elem_less(tree->elem, e)){
            tree->right = abb_remove(tree->right, e);
        }
        else{
            tree->left = abb_remove(tree->left, e);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    abb p = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(!abb_is_empty(p->right)){
    	p = p->right;
    }
    max_e = p->elem;
    p = NULL;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
  	abb p = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(!abb_is_empty(p->left)){
    	p = p->left;
    }
    min_e = p->elem;
    p = NULL;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
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

