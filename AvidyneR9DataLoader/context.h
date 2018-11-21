//
//  context.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/31/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef context_h
#define context_h

#include "csv_record.h"
#include "aircraft_record.h"
#include "transformer.h"
#include "writer.h"
#include "list.h"
#include "tree_set.h"

typedef struct _context_data {
    tree_set* csv_records;
    record_type current_csv_file_type;
    bool current_csv_file_pilot, current_csv_file_legacy, current_csv_file_skip_row;
    int current_csv_file_row_num, current_csv_file_offset;
    csv_record *current_record;
    char *current_record_id;
    bool current_record_stored;

    aircraft aircraft;
    list* aircraft_data;

    int last_active_gps_ifd1, last_active_gps_ifd2,
        last_active_adahrs_ifd1, last_active_adahrs_ifd2;

    writer *writer;
    list_node *position;
} context_data;

context_data *make_context_data(int aircraft_id);
void context_data_free(context_data* const restrict data);

void context_data_reset_for_next_file(context_data* const restrict data, const char* const restrict filename);
void context_data_reset_for_next_row(context_data* const restrict context);

void context_data_build_aircraft(context_data* const restrict context);

void context_data_write_to_file(context_data* const restrict data);

#endif /* context_h */
