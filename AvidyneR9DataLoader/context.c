//
//  context.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 1/12/19.
//  Copyright © 2019 Tim Morgan. All rights reserved.
//

#include "context.h"

void insert_data(context_data* const restrict context, const aircraft_record* const data);

context_data *make_context_data(int aircraft_id) {
    context_data* const restrict data = malloc(sizeof(context_data));
    memset(data, 0, sizeof(context_data));

    data->aircraft.id = aircraft_id;
    data->aircraft.num_anti_ice_systems = 1;
    data->aircraft.num_electrical_systems = 6;
    data->aircraft.num_engines = 1;
    data->aircraft.num_flight_controls = 2;
    data->aircraft.num_fuel_tanks = 2;
    data->aircraft.num_instrument_sets = 2;
    data->aircraft.num_trucks = 3;
    data->aircraft.num_navigation_systems = 5;
    data->aircraft.num_pitot_static_systems = 3;
    data->aircraft.num_position_sensors = 6;
    data->aircraft.num_radios = 4;
    data->aircraft.cylinders_per_engine[0] = 6;
    data->aircraft.propellers_per_engine[0] = 1;
    data->aircraft.tires_per_truck[0] = 1;
    data->aircraft.tires_per_truck[1] = 1;
    data->aircraft.tires_per_truck[2] = 1;

    data->aircraft_data = make_list();
    data->csv_records = make_tree_set();
    data->current_record = NULL;

    data->last_active_gps_ifd1 = -1;
    data->last_active_gps_ifd2 = -1;
    data->last_active_adahrs_ifd1 = -1;
    data->last_active_adahrs_ifd2 = -1;

    return data;
}

void context_data_free(context_data* const restrict data) {
    tree_set_free(data->csv_records);
    if (data->current_record && !data->current_record_stored) csv_record_free(data->current_record); // the last record is not written to and not stored in csv_records
    list_free(data->aircraft_data);
    if (data->writer) writer_free(data->writer);
    free(data);
}

void context_data_reset_for_next_row(context_data* const restrict context) {
    context->current_csv_file_offset = -1;
    context->current_csv_file_skip_row = false;
    context->current_csv_file_row_num++;

    context->current_record = make_csv_record();
    context->current_record_stored = false;
    context->current_record->legacy = context->current_csv_file_legacy;
    context->current_record->pilot = context->current_csv_file_pilot;

    context->current_record_id = malloc(sizeof(char)*64);
    memset(context->current_record_id, 0, sizeof(char)*64);
}

void context_data_reset_for_next_file(context_data* const restrict data, const char* const restrict filename) {
    if (strlen(filename) < 12) {
        fprintf(stderr, "Unrecognized CSV file name %s\n", filename);
        exit(4);
    }

    const char* const filename_offset = filename + (strlen(filename) - 12);

    if (strstr(filename, "P_FLIGHT.CSV") == filename_offset) {
        data->current_csv_file_type = record_flight;
        data->current_csv_file_pilot = true;
    } else if (strstr(filename, "C_FLIGHT.CSV") == filename_offset) {
        data->current_csv_file_type = record_flight;
        data->current_csv_file_pilot = false;
    } else if (strstr(filename, "P_SYSTEM.CSV") == filename_offset) {
        data->current_csv_file_type = record_system;
        data->current_csv_file_pilot = true;
    } else if (strstr(filename, "C_SYSTEM.CSV") == filename_offset) {
        data->current_csv_file_type = record_system;
        data->current_csv_file_pilot = false;
    } else if (strstr(filename, "P_ENGINE.CSV") == filename_offset) {
        data->current_csv_file_type = record_engine;
        data->current_csv_file_pilot = true;
    } else if (strstr(filename, "C_ENGINE.CSV") == filename_offset) {
        data->current_csv_file_type = record_engine;
        data->current_csv_file_pilot = false;
    } else {
        fprintf(stderr, "Unrecognized CSV file name %s\n", filename);
        exit(4);
    }

    data->current_csv_file_legacy = false;
    data->current_csv_file_row_num = -1;

    context_data_reset_for_next_row(data);
}

void context_data_build_aircraft(context_data* const restrict context) {
    const list_node *csv_node = context->csv_records->list->first;

    while (csv_node != NULL) {
        csv_record* const csv = csv_node->data;
        if (!csv->flight.adahrs_used.null) {
            if (csv->pilot) context->last_active_adahrs_ifd1 = csv->flight.adahrs_used.i;
            else context->last_active_adahrs_ifd2 = csv->flight.adahrs_used.i;
        }
        if (!csv->system.gps_select.null) {
            if (csv->pilot) context->last_active_gps_ifd1 = csv->system.gps_select.i;
            else context->last_active_gps_ifd2 = csv->system.gps_select.i;
        }

        int last_active_adahrs = csv->pilot ? context->last_active_adahrs_ifd1 : context->last_active_adahrs_ifd2;
        int last_active_gps = csv->pilot ? context->last_active_gps_ifd1 : context->last_active_gps_ifd2;

        aircraft_record* const new_record = make_aircraft_record(&(context->aircraft));
        csv_to_aircraft(csv, new_record, last_active_adahrs, last_active_gps);

        if (new_record->timestamp.seconds) {
            calculate_estimated_data(new_record);
            insert_data(context, new_record);
        }

        csv_node = csv_node->next;
    }
}

char *strchomp(char *str);

char *strchomp(char *str) {
    unsigned long len = strlen(str);
    while (str[len-1] == '\n' || str[len-1] == '\r')
        str[--len] = 0;
    return str;
}

void insert_data(context_data* const restrict context, const aircraft_record* const data) {
    if (context->position == NULL) {
        context->position = list_lpush(context->aircraft_data, data);
        return;
    }

    aircraft_record* const existing_data = (aircraft_record *)context->position->data;

    if (existing_data->timestamp.seconds < data->timestamp.seconds)
        context->position = list_rpush(context->aircraft_data, data);
    else if (existing_data->timestamp.seconds == data->timestamp.seconds) {
        if (existing_data->timestamp.milliseconds < data->timestamp.milliseconds)
            context->position = list_rpush(context->aircraft_data, data);
        else if (existing_data->timestamp.milliseconds == data->timestamp.milliseconds)
            aircraft_record_merge(existing_data, data);
        else {
            fprintf(stderr, "Out-of-order timestamps detected: {%ld.%03d, %ld.%03d}\n", existing_data->timestamp.seconds, existing_data->timestamp.milliseconds, data->timestamp.seconds, data->timestamp.milliseconds);
            exit(7);
        }
    } else {
        fprintf(stderr, "Out-of-order timestamps detected: {%ld.%03d, %ld.%03d}\n", existing_data->timestamp.seconds, existing_data->timestamp.milliseconds, data->timestamp.seconds, data->timestamp.milliseconds);
        exit(7);
    }
}

void context_data_write_to_file(context_data* const restrict data) {
    data->writer = make_writer();
    list_node *node = data->aircraft_data->first;

    while (node != NULL) {
        aircraft_record* const row = (aircraft_record* const)(node->data);
        writer_process_row(data->writer, row);
        node = node->next;
    }
}
