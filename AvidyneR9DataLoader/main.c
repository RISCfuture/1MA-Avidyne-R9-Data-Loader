//
//  main.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <csv.h>
#include <glob.h>

#include "csv.h"
#include "context.h"
#include "parser.h"
#include "list.h"

list_sort_order csv_sort_callback(const void* const a, const void* const b);
int glob_error(const char *path, int error);

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: AvidyneR9DataLoader aircraftID path/to/file1.csv [...]\n");
        exit(-1);
    }

    struct csv_parser parser;
    csv_handler_init(&parser);

    const char * const aircraft_id_string = *(++argv);
    int aircraft_id = atoi(aircraft_id_string);

    context_data *data = make_context_data(aircraft_id);

    glob_t globs;
    globs.gl_offs = 128;

    int glob_flags = GLOB_ERR|GLOB_NOSORT|GLOB_BRACE|GLOB_TILDE;
    while (*(++argv)) {
        int error = glob(*argv, glob_flags, glob_error, &globs);
        switch (error) {
            case GLOB_NOSPACE:
                fprintf(stderr, "Out of memory\n");
                exit(8);
                break;
            case GLOB_ABORTED:
                fprintf(stderr, "Read error (aborted)\n");
                exit(8);
                break;
            case GLOB_NOMATCH:
                fprintf(stderr, "No matches\n");
                exit(0);
                break;
        }

        glob_flags |= GLOB_APPEND;
    }

    for (unsigned int i=0; i!=globs.gl_pathc; i++) {
        data->position = NULL;
        context_data_reset_for_next_file(data, globs.gl_pathv[i]);
        csv_handler_read_file(globs.gl_pathv[i], &parser, parser_row_handle_cell, parser_row_handle_row, data);
    }

    list_sort(data->csv_records->list, csv_sort_callback);
    context_data_build_aircraft(data);
    context_data_write_to_file(data);

    globfree(&globs);
    csv_free(&parser);
    context_data_free(data);

    return 0;
}

list_sort_order csv_sort_callback(const void* const a, const void* const b) {
    const csv_record* const csv_a = (csv_record *)a;
    const csv_record* const csv_b = (csv_record *)b;

    char *date_a, *date_b, *time_a, *time_b;
    unsigned int systime_a, systime_b;

    if (!csv_a->engine.date.null) {
        date_a = csv_a->engine.date.s;
        time_a = csv_a->engine.time.s;
        systime_a = csv_a->engine.systime.u;
    } else if (!csv_a->flight.date.null) {
        date_a = csv_a->flight.date.s;
        time_a = csv_a->flight.time.s;
        systime_a = csv_a->flight.systime.u;
    } else if (!csv_a->system.date.null) {
        date_a = csv_a->system.date.s;
        time_a = csv_a->system.time.s;
        systime_a = csv_a->system.systime.u;
    } else {
        fprintf(stderr, "Tried to sort uninitialized CSV record\n");
        exit(9);
    }

    if (!csv_b->engine.date.null) {
        date_b = csv_b->engine.date.s;
        time_b = csv_b->engine.time.s;
        systime_b = csv_b->engine.systime.u;
    } else if (!csv_b->flight.date.null) {
        date_b = csv_b->flight.date.s;
        time_b = csv_b->flight.time.s;
        systime_b = csv_b->flight.systime.u;
    } else if (!csv_b->system.date.null) {
        date_b = csv_b->system.date.s;
        time_b = csv_b->system.time.s;
        systime_b = csv_b->system.systime.u;
    } else {
        fprintf(stderr, "Tried to sort uninitialized CSV record\n");
        exit(9);
    }

    int date_compare = strcmp(date_a, date_b);
    if (date_compare < 0) return list_order_a_b;
    else if (date_compare > 0) return list_order_b_a;

    int time_compare = strcmp(time_a, time_b);
    if (time_compare < 0) return list_order_a_b;
    else if (time_compare > 0) return list_order_b_a;

    if ((systime_a % 1000) < (systime_b % 1000)) return list_order_a_b;
    else if ((systime_a % 1000) > (systime_b % 1000)) return list_order_b_a;
    else return list_order_equal;
}

int glob_error(const char *path, int error) {
    switch (error) {
        case EACCES:
            fprintf(stderr, "Permission denied: %s\n", path);
            break;
        case EBADF:
            fprintf(stderr, "Bad file descriptor: %s\n", path);
            break;
        case EMFILE:
        case ENFILE:
            fprintf(stderr, "Too many open files\n");
            break;
        case ENOENT:
            fprintf(stderr, "File not found: %s\n", path);
            break;
        case ENOMEM:
            fprintf(stderr, "Out of memory\n");
            break;
        case ENOTDIR:
            fprintf(stderr, "Not a directory: %s\n", path);
            break;
        case EFAULT:
            fprintf(stderr, "Bad address: %s\n", path);
            break;
        case ELOOP:
            fprintf(stderr, "Too many symbolic links: %s\n", path);
            break;
        case ENAMETOOLONG:
            fprintf(stderr, "Name too long: %s\n", path);
            break;
        case EOVERFLOW:
            fprintf(stderr, "Not enough addressible space: %s\n", path);
            break;
        default:
            fprintf(stderr, "Unknown error %d: %s\n", error, path);
            break;
    }

    exit(8);
    return 1;
}
