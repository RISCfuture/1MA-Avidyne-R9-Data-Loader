//
//  parser.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <csv.h>

#include "context.h"
#include "aircraft_record.h"
#include "writer.h"

void parser_row_handle_cell(void *data, size_t size, void *row);
void parser_row_handle_row(int terminating_character, void *row);

#endif /* parser_h */
