//
//  list.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum _list_sort_order {
    list_order_a_b = -1,
    list_order_equal,
    list_order_b_a
} list_sort_order;

typedef list_sort_order (*list_sort_callback)(const void* const a, const void* const b);

typedef struct _list_node {
    void *data;
    struct _list_node *next;
} list_node;

typedef struct _list {
    list_node *first;
    list_node *last;
} list;

list *make_list(void);
void list_free(list* const restrict list);

unsigned int list_size(const list* const restrict list);

list_node* list_lpush(list* const restrict list, const void* const data);
list_node* list_rpush(list* const restrict list, const void* const data);
void list_insert(list_node* const prev, void* item);

void list_sort(list* const restrict list, list_sort_callback comparator);

#endif /* list_h */
