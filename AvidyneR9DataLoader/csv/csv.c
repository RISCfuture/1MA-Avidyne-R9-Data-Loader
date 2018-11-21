//
//  csv.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "csv.h"

static int is_space(unsigned char c) {
    if (c == CSV_SPACE || c == CSV_TAB) return 1;
    return 0;
}

static int is_term(unsigned char c) {
    if (c == CSV_CR || c == CSV_LF) return 1;
    return 0;
}

void csv_handler_init(struct csv_parser* const restrict parser) {
    if (csv_init(parser, 0) != 0) {
        fprintf(stderr, "Failed to initialize CSV parser\n");
        exit(2);
    }

    csv_set_space_func(parser, is_space);
    csv_set_term_func(parser, is_term);
    csv_set_opts(parser, CSV_STRICT);
}

void csv_handler_read_file(const char* const restrict path, struct csv_parser* const restrict parser, csv_field_callback parser_row_handle_cell, csv_record_callback parser_row_handle_row, void* const restrict data) {
    FILE* const restrict csv_file = fopen(path, "rb");
    if (!csv_file) {
        int error = errno;
        fprintf(stderr, "Couldn't open %s: %s\n", path, strerror(error));
        exit(error);
    }

    size_t bytes_read;
    char buffer[1024];
    while ((bytes_read = fread(buffer, 1, 1024, csv_file))) {
        if (csv_parse(parser, buffer, bytes_read, parser_row_handle_cell, parser_row_handle_row, data) < bytes_read) {
            const int error = csv_error(parser);
            fprintf(stderr, "Couldn't parse %s: %s\n", path, csv_strerror(error));
            exit(error);
        }
    }

    csv_fini(parser, parser_row_handle_cell, parser_row_handle_row, data);

    if (ferror(csv_file)) {
        fprintf(stderr, "Couldn't read %s\n", path);
        exit(3);
    }

    fclose(csv_file);
}
