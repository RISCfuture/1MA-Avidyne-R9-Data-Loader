//
//  tree_list.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "tree_set.h"

tree_node *tree_node_init(void);
void tree_node_free(tree_node* const restrict node);
char tree_char_index(char character);

tree_set *make_tree_set(void) {
    tree_set* const restrict set = malloc(sizeof(tree_set));
    set->list = make_list();
    set->head = tree_node_init();

    return set;
}

void tree_set_free(tree_set* const restrict set) {
    list_free(set->list);
    tree_node_free(set->head);
    free(set);
}

void tree_node_free(tree_node* const restrict node) {
    for (unsigned int i=0; i!=63; i++)
        if (node->children[i]) tree_node_free(node->children[i]);
    free(node);
}

void tree_set_add(tree_set* const restrict set, const char* const restrict key, void* item) {
    list_node* node = list_rpush(set->list, item);

    tree_node* current = set->head;
    unsigned long key_length = strlen(key);

    for (unsigned long index = 0; index != key_length; index++) {
        char char_index = tree_char_index(key[index]);
        if (char_index == -1) {
            fprintf(stderr, "Invalid character in identifier '%s'", key);
            exit(5);
        }

        if (!current->children[char_index])
            current->children[char_index] = tree_node_init();

        current = current->children[char_index];
    }

    current->list_node = node;
}

void *tree_set_get(const tree_set* const restrict set, const char* const restrict key) {
    unsigned long key_length = strlen(key);
    tree_node* current = set->head;
    for (unsigned long index = 0; index != key_length; index++) {
        char char_index = tree_char_index(key[index]);
        if (char_index == -1) {
            fprintf(stderr, "Invalid character in identifier '%s'", key);
            exit(5);
        }

        if (!current->children[char_index])
            return NULL;

        current = current->children[char_index];
    }

    if (!current) return NULL;
    if (!current->list_node) return NULL;
    return current->list_node->data;
}

tree_node *tree_node_init(void) {
    tree_node* const restrict node = malloc(sizeof(tree_node));
    node->list_node = NULL;
    memset(node->children, 0, sizeof(tree_node*) * 63);

    return node;
}

char tree_char_index(char character) {
    if (character >= 'a' && character <= 'z')
        return character - 'a';
    else if (character >= 'A' && character <= 'Z')
        return 26 + character - 'A';
    else if (character >= '0' && character <= '9')
        return 52 + character - '0';
    else if (character == '_')
        return 62;
    else {
        return -1;
    }
}
