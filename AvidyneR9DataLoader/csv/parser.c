//
//  parser.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "parser.h"

enum flight_record_fields {
    flight_systime = 0,
    flight_date, flight_time,

    norm_acc, long_acc, lateral_acc,

    adahrs_used,
    ahrs_status_bits,

    heading, pitch, roll,
    flight_director_pitch, flight_director_roll,
    heading_rate,

    pressure_altitude,
    indicated_airspeed, true_airspeed, vertical_speed,

    gps_latitude, gps_longitude,

    body_yaw_rate, body_pitch_rate, body_roll_rate,

    mag_status, iru_status, mpu_status, adc_status,
    ahrs_seq, adc_seq, ahrs_startup_mode,

    dfc100_lat_active, dfc100_lat_armed, dfc100_vert_active, dfc_100_vert_armed,
    dfc100_status_flags, dfc_100_fail_flags,
    dfc100_alt_target
};

enum system_record_fields {
    system_systime = 0,
    system_date, system_time,

    outside_air_temperature,

    localizer_deviation, glideslope_deviation,

    flight_director_on_off,
    autopilot_mode,

    ground_speed,

    ground_track,
    cross_track_deviation,
    vertical_deviation,

    altimeter_setting,
    alt_bug, vsi_bug, hdg_bug,

    display_mode, navigation_mode,
    active_wpt_id,
    gps_select,

    navaid_brg, obs, desired_track,
    nav_freq,
    crs_select, nav_type, course_deviation,

    gps_altitude,
    distance_to_active_wpt,

    gps_state,
    gps_horiz_prot_limit, gps_vert_prot_limit,
    hpl_sbas, vpl_sbas,
    hfom, vfom,

    fms_course,
    mag_var,

    gps_msl_altitude, gps_agl_height,

    flta_rtc, flta_atc, flta_vspd, flta_rtc_dist, flta_terr_dist, flta_status
};

enum legacy_engine_record_fields {
    engine_systime = 0,
    engine_date, engine_time,

    oil_temperature, oil_pressure,
    rpm,
    manifold_pressure,
    tit,

    cht1, cht2, cht3, cht4, cht5, cht6,
    egt1, egt2, egt3, egt4, egt5, egt6,

    percent_pwr,
    fuel_flow,
    fuel_used, fuel_remaining,
    fuel_time_remaining,
    fuel_economy,

    alt1_current, alt2_current, bat_current, bat2_current,

    // legacy
    bus1_volts, legacy_bus2_volts, bus3_volts,

    legacy_discrete_inputs, legacy_discrete_outputs
};

enum new_engine_record_fields {
    mbus1_volts = bat2_current + 1, mbus2_volts, new_bus2_volts,

    l_fuel_qty, r_fuel_qty,

    deice_vac,
    rudder_trim,
    flaps,
    ng,
    torque, itt, np,

    new_discrete_inputs, new_discrete_outputs
};

optional parse_int(const char* const restrict value);
optional parse_unsigned_int(const char* const restrict value);
optional parse_float(const char* const restrict value);
optional parse_string(const char* const restrict value);

void parse_flight_field(context_data* const restrict context, char* const restrict value);
void parse_system_field(context_data* const restrict context, char* const restrict value);
void parse_engine_field(context_data* const restrict context, char* const restrict value);

void add_to_key(char* const restrict key, const char* const restrict data, bool divider);

void parser_row_handle_cell(void *data, size_t size, void *_context) {
    context_data* const context = (context_data *)_context;
    context->current_csv_file_offset++;

    if (context->current_csv_file_skip_row) return;

    char* const value = malloc(size + 1);
    memcpy(value, data, size);
    value[size] = 0;

    if (context->current_csv_file_row_num == 0) {
        if (context->current_csv_file_type == record_engine) {
            if (strcmp(value, "Eng1Bus3Volts") == 0)
                context->current_csv_file_legacy = true;
        }
        context->current_csv_file_skip_row = true;
        free(value);
        return;
    }

    if (strstr(value, "POWER ON")) {
        context->current_csv_file_skip_row = true;
        free(value);
        return;
    }

    switch (context->current_csv_file_type) {
        case record_flight: parse_flight_field(context, value); break;
        case record_system: parse_system_field(context, value); break;
        case record_engine: parse_engine_field(context, value); break;
        default: free(value); break;
    }
}

void parser_row_handle_row(int terminating_character, void *_context) {
    context_data* const context = (context_data *)_context;
    context_data_reset_for_next_row(context);
}

void parse_flight_field(context_data* const restrict context, char* const restrict value) {
    switch (context->current_csv_file_offset) {
        case flight_systime:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, true);
            context->current_record->flight.systime = parse_unsigned_int(value);
            if (context->current_record->flight.systime.null) context->current_csv_file_skip_row = true;
            free(value);
            break;
        case flight_date:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, false);
            context->current_record->flight.date = parse_string(value);
            if (context->current_record->flight.date.null) context->current_csv_file_skip_row = true;
            break;
        case flight_time:
            if (!context->current_record_stored) {
                add_to_key(context->current_record_id, value, false);
                csv_record *existing_record = tree_set_get(context->csv_records, context->current_record_id);
                if (existing_record) {
                    existing_record->flight = context->current_record->flight;
                    context->current_record = existing_record;
                } else
                    tree_set_add(context->csv_records, context->current_record_id, context->current_record);
                context->current_record_stored = true;
            }
            context->current_record->flight.time = parse_string(value);
            if (context->current_record->flight.time.null) context->current_csv_file_skip_row = true;
            break;
        case norm_acc:
            context->current_record->flight.norm_acc = parse_float(value);
            free(value);
            break;
        case long_acc:
            context->current_record->flight.long_acc = parse_float(value);
            free(value);
            break;
        case lateral_acc:
            context->current_record->flight.lateral_acc = parse_float(value);
            free(value);
            break;
        case adahrs_used:
            context->current_record->flight.adahrs_used = parse_int(value);
            free(value);
            break;
        case ahrs_status_bits:
            context->current_record->flight.ahrs_status_bits = parse_string(value);
            break;
        case heading:
            context->current_record->flight.heading = parse_int(value);
            free(value);
            break;
        case pitch:
            context->current_record->flight.pitch = parse_int(value);
            free(value);
            break;
        case roll:
            context->current_record->flight.roll = parse_int(value);
            free(value);
            break;
        case flight_director_pitch:
            context->current_record->flight.flight_director_pitch = parse_int(value);
            free(value);
            break;
        case flight_director_roll:
            context->current_record->flight.flight_director_roll = parse_int(value);
            free(value);
            break;
        case heading_rate:
            context->current_record->flight.heading_rate = parse_float(value);
            free(value);
            break;
        case pressure_altitude:
            context->current_record->flight.pressure_altitude = parse_int(value);
            free(value);
            break;
        case indicated_airspeed:
            context->current_record->flight.indicated_airspeed = parse_int(value);
            free(value);
            break;
        case true_airspeed:
            context->current_record->flight.true_airspeed = parse_int(value);
            free(value);
            break;
        case vertical_speed:
            context->current_record->flight.vertical_speed = parse_int(value);
            free(value);
            break;
        case gps_latitude:
            if (strcmp(value, "0.00000") != 0)
                context->current_record->flight.gps_latitude = parse_float(value);
            free(value);
            break;
        case gps_longitude:
            if (strcmp(value, "0.00000") != 0)
                context->current_record->flight.gps_longitude = parse_float(value);
            free(value);
            break;
        case body_yaw_rate:
            context->current_record->flight.body_yaw_rate = parse_float(value);
            free(value);
            break;
        case body_pitch_rate:
            context->current_record->flight.body_pitch_rate = parse_float(value);
            free(value);
            break;
        case body_roll_rate:
            context->current_record->flight.body_roll_rate = parse_float(value);
            free(value);
            break;
        case mag_status:
            context->current_record->flight.mag_status = parse_int(value);
            free(value);
            break;
        case iru_status:
            context->current_record->flight.iru_status = parse_int(value);
            free(value);
            break;
        case mpu_status:
            context->current_record->flight.iru_status = parse_int(value);
            free(value);
            break;
        case adc_status:
            context->current_record->flight.adc_status = parse_int(value);
            free(value);
            break;
        case ahrs_seq:
            context->current_record->flight.ahrs_seq = parse_int(value);
            free(value);
            break;
        case adc_seq:
            context->current_record->flight.adc_seq = parse_int(value);
            free(value);
            break;
        case ahrs_startup_mode:
            context->current_record->flight.ahrs_startup_mode = parse_int(value);
            free(value);
            break;
        case dfc100_lat_active:
            context->current_record->flight.dfc100_lat_active = parse_int(value);
            free(value);
            break;
        case dfc100_lat_armed:
            context->current_record->flight.dfc100_lat_armed = parse_int(value);
            free(value);
            break;
        case dfc100_vert_active:
            context->current_record->flight.dfc100_vert_active = parse_int(value);
            free(value);
            break;
        case dfc_100_vert_armed:
            context->current_record->flight.dfc_100_vert_armed = parse_int(value);
            free(value);
            break;
        case dfc100_status_flags:
            context->current_record->flight.dfc100_status_flags = parse_string(value);
            break;
        case dfc_100_fail_flags:
            context->current_record->flight.dfc_100_fail_flags = parse_string(value);
            break;
        case dfc100_alt_target:
            context->current_record->flight.dfc100_alt_target = parse_int(value);
            free(value);
            break;
    }
}

void parse_system_field(context_data* const restrict context, char* const restrict value) {
    switch (context->current_csv_file_offset) {
        case system_systime:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, true);
            context->current_record->system.systime = parse_int(value);
            if (context->current_record->system.systime.null) context->current_csv_file_skip_row = true;
            free(value);
            break;
        case system_date:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, false);
            context->current_record->system.date = parse_string(value);
            if (context->current_record->system.date.null) context->current_csv_file_skip_row = true;
            break;
        case system_time:
            if (!context->current_record_stored) {
                add_to_key(context->current_record_id, value, false);
                csv_record *existing_record = tree_set_get(context->csv_records, context->current_record_id);
                if (existing_record) {
                    existing_record->system = context->current_record->system;
                    context->current_record = existing_record;
                } else
                    tree_set_add(context->csv_records, context->current_record_id, context->current_record);
                context->current_record_stored = true;
            }
            context->current_record->system.time = parse_string(value);
            if (context->current_record->system.time.null) context->current_csv_file_skip_row = true;
            break;
        case outside_air_temperature:
            context->current_record->system.outside_air_temperature = parse_int(value);
            free(value);
            break;
        case localizer_deviation:
            context->current_record->system.localizer_deviation = parse_float(value);
            free(value);
            break;
        case glideslope_deviation:
            context->current_record->system.glideslope_deviation = parse_float(value);
            free(value);
            break;
        case flight_director_on_off:
            context->current_record->system.flight_director_on_off = parse_int(value);
            free(value);
            break;
        case autopilot_mode:
            context->current_record->system.autopilot_mode = parse_int(value);
            free(value);
            break;
        case ground_speed:
            context->current_record->system.ground_speed = parse_int(value);
            free(value);
            break;
        case ground_track:
            context->current_record->system.ground_track = parse_int(value);
            free(value);
            break;
        case cross_track_deviation:
            context->current_record->system.cross_track_deviation = parse_float(value);
            free(value);
            break;
        case vertical_deviation:
            context->current_record->system.vertical_deviation = parse_int(value);
            free(value);
            break;
        case altimeter_setting:
            context->current_record->system.altimeter_setting = parse_float(value);
            free(value);
            break;
        case alt_bug:
            context->current_record->system.alt_bug = parse_int(value);
            free(value);
            break;
        case vsi_bug:
            context->current_record->system.vsi_bug = parse_int(value);
            free(value);
            break;
        case hdg_bug:
            context->current_record->system.hdg_bug = parse_int(value);
            free(value);
            break;
        case display_mode:
            context->current_record->system.display_mode = parse_int(value);
            free(value);
            break;
        case navigation_mode:
            context->current_record->system.navigation_mode = parse_int(value);
            free(value);
            break;
        case active_wpt_id:
            context->current_record->system.active_wpt_id = parse_string(value);
            break;
        case gps_select:
            context->current_record->system.gps_select = parse_int(value);
            free(value);
            break;
        case navaid_brg:
            context->current_record->system.navaid_brg = parse_int(value);
            free(value);
            break;
        case obs:
            context->current_record->system.obs = parse_int(value);
            free(value);
            break;
        case desired_track:
            context->current_record->system.desired_track = parse_int(value);
            free(value);
            break;
        case nav_freq:
            context->current_record->system.nav_freq = parse_int(value);
            free(value);
            break;
        case crs_select:
            context->current_record->system.crs_select = parse_int(value);
            free(value);
            break;
        case nav_type:
            context->current_record->system.nav_type = parse_int(value);
            free(value);
            break;
        case course_deviation:
            context->current_record->system.course_deviation = parse_int(value);
            free(value);
            break;
        case gps_altitude:
            context->current_record->system.gps_altitude = parse_int(value);
            free(value);
            break;
        case distance_to_active_wpt:
            context->current_record->system.distance_to_active_wpt = parse_float(value);
            free(value);
            break;
        case gps_state:
            context->current_record->system.gps_state = parse_int(value);
            free(value);
            break;
        case gps_horiz_prot_limit:
            context->current_record->system.gps_horiz_prot_limit = parse_int(value);
            free(value);
            break;
        case gps_vert_prot_limit:
            context->current_record->system.gps_vert_prot_limit = parse_int(value);
            free(value);
            break;
        case hpl_sbas:
            context->current_record->system.hpl_sbas = parse_int(value);
            free(value);
            break;
        case vpl_sbas:
            context->current_record->system.vpl_sbas = parse_int(value);
            free(value);
            break;
        case hfom:
            context->current_record->system.hfom = parse_int(value);
            free(value);
            break;
        case vfom:
            context->current_record->system.vfom = parse_int(value);
            free(value);
            break;
        case fms_course:
            context->current_record->system.fms_course = parse_int(value);
            free(value);
            break;
        case mag_var:
            context->current_record->system.mag_var = parse_int(value);
            free(value);
            break;
        case gps_msl_altitude:
            context->current_record->system.gps_msl_altitude = parse_int(value);
            free(value);
            break;
        case gps_agl_height:
            context->current_record->system.gps_agl_height = parse_int(value);
            free(value);
            break;
        case flta_rtc:
            context->current_record->system.flta_rtc = parse_int(value);
            free(value);
            break;
        case flta_atc:
            context->current_record->system.flta_atc = parse_int(value);
            free(value);
            break;
        case flta_vspd:
            context->current_record->system.flta_vspd = parse_int(value);
            free(value);
            break;
        case flta_rtc_dist:
            context->current_record->system.flta_rtc_dist = parse_int(value);
            free(value);
            break;
        case flta_terr_dist:
            context->current_record->system.flta_terr_dist = parse_int(value);
            free(value);
            break;
        case flta_status:
            context->current_record->system.flta_status = parse_int(value);
            free(value);
            break;
    }
}

void parse_engine_field(context_data* const restrict context, char* const restrict value) {
    switch (context->current_csv_file_offset) {
        case engine_systime:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, true);
            context->current_record->engine.systime = parse_int(value);
            if (context->current_record->engine.systime.null) context->current_csv_file_skip_row = true;
            free(value);
            break;
        case engine_date:
            if (!context->current_record_stored) add_to_key(context->current_record_id, value, false);
            context->current_record->engine.date = parse_string(value);
            if (context->current_record->engine.date.null) context->current_csv_file_skip_row = true;
            break;
        case engine_time:
            if (!context->current_record_stored) {
                add_to_key(context->current_record_id, value, false);
                csv_record *existing_record = tree_set_get(context->csv_records, context->current_record_id);
                if (existing_record) {
                    existing_record->engine = context->current_record->engine;
                    context->current_record = existing_record;
                } else
                    tree_set_add(context->csv_records, context->current_record_id, context->current_record);
                context->current_record_stored = true;
            }
            context->current_record->engine.time = parse_string(value);
            if (context->current_record->engine.time.null) context->current_csv_file_skip_row = true;
            break;
        case oil_temperature:
            context->current_record->engine.oil_temperature = parse_int(value);
            free(value);
            break;
        case oil_pressure:
            context->current_record->engine.oil_pressure = parse_int(value);
            free(value);
            break;
        case rpm:
            context->current_record->engine.rpm = parse_int(value);
            free(value);
            break;
        case manifold_pressure:
            context->current_record->engine.manifold_pressure = parse_float(value);
            free(value);
            break;
        case tit:
            context->current_record->engine.tit = parse_int(value);
            free(value);
            break;
        case cht1:
            context->current_record->engine.cht1 = parse_float(value);
            free(value);
            break;
        case cht2:
            context->current_record->engine.cht2 = parse_float(value);
            free(value);
            break;
        case cht3:
            context->current_record->engine.cht3 = parse_float(value);
            free(value);
            break;
        case cht4:
            context->current_record->engine.cht4 = parse_float(value);
            free(value);
            break;
        case cht5:
            context->current_record->engine.cht5 = parse_float(value);
            free(value);
            break;
        case cht6:
            context->current_record->engine.cht6 = parse_float(value);
            free(value);
            break;
        case egt1:
            context->current_record->engine.egt1 = parse_float(value);
            free(value);
            break;
        case egt2:
            context->current_record->engine.egt2 = parse_float(value);
            free(value);
            break;
        case egt3:
            context->current_record->engine.egt3 = parse_float(value);
            free(value);
            break;
        case egt4:
            context->current_record->engine.egt4 = parse_float(value);
            free(value);
            break;
        case egt5:
            context->current_record->engine.egt5 = parse_float(value);
            free(value);
            break;
        case egt6:
            context->current_record->engine.egt6 = parse_float(value);
            free(value);
            break;
        case percent_pwr:
            context->current_record->engine.percent_pwr = parse_float(value);
            free(value);
            break;
        case fuel_flow:
            context->current_record->engine.fuel_flow = parse_float(value);
            free(value);
            break;
        case fuel_used:
            context->current_record->engine.fuel_used = parse_float(value);
            free(value);
            break;
        case fuel_remaining:
            context->current_record->engine.fuel_remaining = parse_float(value);
            free(value);
            break;
        case fuel_time_remaining:
            context->current_record->engine.fuel_time_remaining = parse_int(value);
            free(value);
            break;
        case fuel_economy:
            context->current_record->engine.fuel_economy = parse_float(value);
            free(value);
            break;
        case alt1_current:
            context->current_record->engine.alt1_current = parse_float(value);
            free(value);
            break;
        case alt2_current:
            context->current_record->engine.alt2_current = parse_float(value);
            free(value);
            break;
        case bat_current:
            context->current_record->engine.bat_current = parse_float(value);
            free(value);
            break;
        case bat2_current:
            context->current_record->engine.bat2_current = parse_float(value);
            free(value);
            break;
    }

    if (context->current_csv_file_legacy) {
        switch (context->current_csv_file_offset) {
            case bus1_volts:
                context->current_record->engine.bus1_volts = parse_float(value);
                free(value);
                break;
            case legacy_bus2_volts:
                context->current_record->engine.bus2_volts = parse_float(value);
                free(value);
                break;
            case bus3_volts:
                context->current_record->engine.bus3_volts = parse_float(value);
                free(value);
                break;
            case legacy_discrete_inputs:
                context->current_record->engine.discrete_inputs = opts(value);
                break;
            case legacy_discrete_outputs:
                context->current_record->engine.discrete_outputs = opts(value);
                break;
        }
    } else {
        switch (context->current_csv_file_offset) {
            case mbus1_volts:
                context->current_record->engine.mbus1_volts = parse_float(value);
                free(value);
                break;
            case mbus2_volts:
                context->current_record->engine.mbus2_volts = parse_float(value);
                free(value);
                break;
            case new_bus2_volts:
                context->current_record->engine.bus2_volts = parse_float(value);
                free(value);
                break;
            case l_fuel_qty:
                context->current_record->engine.l_fuel_qty = parse_int(value);
                free(value);
                break;
            case r_fuel_qty:
                context->current_record->engine.r_fuel_qty = parse_int(value);
                free(value);
                break;
            case deice_vac:
                context->current_record->engine.deice_vac = parse_float(value);
                free(value);
                break;
            case rudder_trim:
                context->current_record->engine.rudder_trim = parse_float(value);
                free(value);
                break;
            case flaps:
                context->current_record->engine.flaps = parse_int(value);
                free(value);
                break;
            case ng:
                context->current_record->engine.ng = parse_float(value);
                free(value);
                break;
            case torque:
                context->current_record->engine.torque = parse_int(value);
                free(value);
                break;
            case itt:
                context->current_record->engine.itt = parse_int(value);
                free(value);
                break;
            case np:
                context->current_record->engine.np = parse_int(value);
                free(value);
                break;
            case new_discrete_inputs:
                context->current_record->engine.discrete_inputs = opts(value);
                break;
            case new_discrete_outputs:
                context->current_record->engine.discrete_outputs = opts(value);
                break;
        }
    }
}

optional parse_int(const char* const restrict value) {
    if (strlen(value) == 0) return optnull();
    if (strcmp(value, "-") == 0) return optnull();

    return opti(atoi(value));
}

optional parse_unsigned_int(const char* const restrict value) {
    if (strlen(value) == 0) return optnull();
    if (strcmp(value, "-") == 0) return optnull();

    return optu(atoi(value));
}

optional parse_float(const char* const restrict value) {
    if (strlen(value) == 0) return optnull();
    if (strcmp(value, "-") == 0) return optnull();
    if (strcmp(value, "0.0") == 0) return optnull();

    return optf(atof(value));
}

optional parse_string(const char* const restrict value) {
    if (strlen(value) == 0) return optnull();
    if (strcmp(value, "-") == 0) return optnull();

    return opts(value);
}

void add_to_key(char* const restrict key, const char* const restrict data, bool divider) {
    long key_pos = strlen(key);
    for (unsigned int i=0; i!=strlen(data); i++) {
        if ((data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= 'a' && data[i] <= 'z') || (data[i] >= '0' && data[i] <= '9'))
            key[key_pos++] = data[i];
    }
    if (divider) key[key_pos++] = '_';
    key[key_pos] = 0;
}
