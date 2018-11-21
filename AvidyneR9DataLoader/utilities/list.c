//
//  list.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "list.h"

list_node *merge(list_node *a, list_node *b, list_sort_callback comparator);
list_node *sort(list_node *head, list_sort_callback comparator);

list *make_list(void) {
    list* const restrict l = malloc(sizeof(list));
    l->first = NULL;
    l->last = NULL;

    return l;
}

void list_free(list* const restrict list) {
    if (list->first != NULL) {
        list_node* current = list->first;

        do {
            list_node* const next = current->next;
            free(current);
            current = next;
        } while (current);
    }

    free(list);
}

unsigned int list_size(const list* const restrict list) {
    unsigned int size = 0;
    const list_node *current = list->first;
    while (current != NULL) {
        current = current->next;
        size++;
    }
    return size;
}

list_node *list_lpush(list* const restrict list, const void* const data) {
    list_node* const restrict first = malloc(sizeof(list_node));
    first->data = data;

    if (list->first != NULL)
        first->next = list->first;
    list->first = first;
    if (list->last == NULL)
        list->last = first;

    return first;
}

list_node *list_rpush(list* const restrict list, const void* const data) {
    list_node* const restrict last = malloc(sizeof(list_node));
    last->data = data;

    if (list->last != NULL)
        list->last->next = last;
    list->last = last;
    if (list->first == NULL)
        list->first = last;
    return last;
}

void list_insert(list_node* const prev, void* item) {
    list_node* const new = malloc(sizeof(list_node));

    new->data = item;
    new->next = prev->next;
    prev->next = new;
}

void swap_nodes(list_node ** const a, list_node ** const b) {
    list_node *c;
    c = *a;
    *a = *b;
    *b = c;
}

void list_sort(list* const restrict list, list_sort_callback comparator) {
    list->first = sort(list->first, comparator);
    list->last = list->first;
    while (list->last->next) list->last = list->last->next;
}

// merge two already sorted lists
list_node *merge(list_node *a, list_node *b, list_sort_callback comparator) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    list_node *temp = malloc(sizeof(list_node));
    temp->data = temp->next = NULL;

    list_node *dest = temp;
    while (true) {
        list_sort_order order = comparator(a->data, b->data);
        if (order == list_order_a_b || order == list_order_equal) {
            dest->next = a;
            dest = a;
            a = a->next;
            if (a == NULL) {
                dest->next = b;
                break;
            }
        } else {
            dest->next = b;
            dest = b;
            b = b->next;
            if (b == NULL) {
                dest->next = a;
                break;
            }
        }
    }
    list_node *new_head = temp->next;
    free(temp);
    return new_head;
}


list_node *sort(list_node *head, list_sort_callback comparator) {
    if (head == NULL || head->next == NULL) return head;

    list_node *alist[32];
    memset(alist, 0, sizeof(list_node *) * 32);
    list_node *node = head;
    list_node *next;
    unsigned int i;

    while (node != NULL) {
        next = node->next;
        node->next = NULL;
        for (i = 0; (i < 32) && (alist[i] != NULL); i++) {
            node = merge(alist[i], node, comparator);
            alist[i] = NULL;
        }
        if (i == 32) i--;
        alist[i] = node;
        node = next;
    }

    for(i = 0; i < 32; i++) node = merge(alist[i], node, comparator);

    return node;
}
