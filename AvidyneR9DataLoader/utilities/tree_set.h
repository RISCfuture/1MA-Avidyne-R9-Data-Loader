//
//  tree_list.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef tree_set_h
#define tree_set_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct _tree_node {
    list_node *list_node;
    struct _tree_node *children[63];
} tree_node;

typedef struct _tree_set {
    list *list;
    tree_node *head;
} tree_set;

tree_set *make_tree_set(void);
void tree_set_free(tree_set* const restrict set);

void tree_set_add(tree_set* const restrict set, const char* const restrict key, void* item);
void *tree_set_get(const tree_set* const restrict set, const char* const restrict key);

#endif /* tree_list_h */
