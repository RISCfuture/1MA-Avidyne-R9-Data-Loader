//
//  csv.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef csv_h
#define csv_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <csv.h>

typedef void (*csv_field_callback)(void* data, size_t size, void* context);
typedef void (*csv_record_callback)(int terminating_character, void* context);

void csv_handler_init(struct csv_parser* const restrict parser);
void csv_handler_read_file(const char* const restrict path, struct csv_parser* const restrict parser, csv_field_callback parser_row_handle_cell, csv_record_callback parser_row_handle_row, void* const restrict data);

#endif /* csv_h */
