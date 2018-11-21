//
//  record.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "csv_record.h"

void flight_record_init(flight_record* const restrict record);
void system_record_init(system_record* const restrict record);
void engine_record_init(engine_record* const restrict record);

void flight_record_free_data(flight_record* const restrict record);
void system_record_free_data(system_record* const restrict record);
void engine_record_free_data(engine_record* const restrict record);

csv_record *make_csv_record(void) {
    csv_record* const restrict row = malloc(sizeof(csv_record));
    flight_record_init(&(row->flight));
    engine_record_init(&(row->engine));
    system_record_init(&(row->system));
    return row;
}

void csv_record_free(csv_record* const restrict row) {
    flight_record_free_data(&(row->flight));
    engine_record_free_data(&(row->engine));
    system_record_free_data(&(row->system));
    free(row);
}

void flight_record_init(flight_record* const restrict record) {
    record->systime = optnull();
    record->date = optnull();
    record->time = optnull();

    record->norm_acc = optnull();
    record->long_acc = optnull();
    record->lateral_acc = optnull();

    record->adahrs_used = optnull();
    record->ahrs_status_bits = optnull();

    record->heading = optnull();
    record->pitch = optnull();
    record->roll = optnull();
    record->flight_director_pitch = optnull();
    record->flight_director_roll = optnull();
    record->heading_rate = optnull();

    record->pressure_altitude = optnull();
    record->indicated_airspeed = optnull();
    record->true_airspeed = optnull();
    record->vertical_speed = optnull();

    record->gps_latitude = optnull();
    record->gps_longitude = optnull();

    record->body_yaw_rate = optnull();
    record->body_pitch_rate = optnull();
    record->body_roll_rate = optnull();

    record->mag_status = optnull();
    record->iru_status = optnull();
    record->mpu_status = optnull();
    record->adc_status = optnull();
    record->ahrs_seq = optnull();
    record->adc_seq = optnull();
    record->ahrs_startup_mode = optnull();

    record->dfc100_lat_active = optnull();
    record->dfc100_lat_armed = optnull();
    record->dfc100_vert_active = optnull();
    record->dfc_100_vert_armed = optnull();
    record->dfc100_status_flags = optnull();
    record->dfc_100_fail_flags = optnull();
    record->dfc100_alt_target = optnull();
}


void system_record_init(system_record* const restrict record) {
    record->systime = optnull();
    record->date = optnull();
    record->time = optnull();

    record->outside_air_temperature = optnull();

    record->localizer_deviation = optnull();
    record->glideslope_deviation = optnull();

    record->flight_director_on_off = optnull();
    record->autopilot_mode = optnull();

    record->ground_speed = optnull();

    record->ground_track = optnull();
    record->cross_track_deviation = optnull();
    record->vertical_deviation = optnull();

    record->altimeter_setting = optnull();
    record->alt_bug = optnull();
    record->vsi_bug = optnull();
    record->hdg_bug = optnull();

    record->display_mode = optnull();
    record->navigation_mode = optnull();
    record->active_wpt_id = optnull();
    record->gps_select = optnull();

    record->navaid_brg = optnull();
    record->obs = optnull();
    record->desired_track = optnull();
    record->nav_freq = optnull();
    record->crs_select = optnull();
    record->nav_type = optnull();
    record->course_deviation = optnull();

    record->gps_altitude = optnull();
    record->distance_to_active_wpt = optnull();

    record->gps_state = optnull();
    record->gps_horiz_prot_limit = optnull();
    record->gps_vert_prot_limit = optnull();
    record->hpl_sbas = optnull();
    record->vpl_sbas = optnull();
    record->hfom = optnull();
    record->vfom = optnull();

    record->fms_course = optnull();
    record->mag_var = optnull();

    record->gps_msl_altitude = optnull();
    record->gps_agl_height = optnull();

    record->flta_rtc = optnull();
    record->flta_atc = optnull();
    record->flta_vspd = optnull();
    record->flta_rtc_dist = optnull();
    record->flta_terr_dist = optnull();
    record->flta_status = optnull();
}

void engine_record_init(engine_record* const restrict record) {
    record->systime = optnull();
    record->date = optnull();
    record->time = optnull();

    record->oil_temperature = optnull();
    record->oil_pressure = optnull();
    record->rpm = optnull();
    record->manifold_pressure = optnull();
    record->tit = optnull();

    record->cht1 = optnull();
    record->cht2 = optnull();
    record->cht3 = optnull();
    record->cht4 = optnull();
    record->cht5 = optnull();
    record->cht6 = optnull();
    record->egt1 = optnull();
    record->egt2 = optnull();
    record->egt3 = optnull();
    record->egt4 = optnull();
    record->egt5 = optnull();
    record->egt6 = optnull();

    record->percent_pwr = optnull();
    record->fuel_flow = optnull();
    record->fuel_used = optnull();
    record->fuel_remaining = optnull();
    record->fuel_time_remaining = optnull();
    record->fuel_economy = optnull();

    record->alt1_current = optnull();
    record->alt2_current = optnull();
    record->bat_current = optnull();
    record->bat2_current = optnull();
    record->mbus1_volts = optnull();
    record->mbus2_volts = optnull();
    record->bus1_volts = optnull();
    record->bus2_volts = optnull();
    record->bus3_volts = optnull();

    record->bus3_volts = optnull();

    record->l_fuel_qty = optnull();
    record->r_fuel_qty = optnull();
    record->deice_vac = optnull();
    record->rudder_trim = optnull();
    record->flaps = optnull();
    record->ng = optnull();
    record->torque = optnull();
    record->itt = optnull();
    record->np = optnull();

    record->discrete_inputs = optnull();
    record->discrete_outputs = optnull();
}

void flight_record_free_data(flight_record* const restrict record) {
    if (!record->date.null) free(record->date.s);
    if (!record->time.null) free(record->time.s);
    if (!record->ahrs_status_bits.null) free(record->ahrs_status_bits.s);
    if (!record->dfc100_status_flags.null) free(record->dfc100_status_flags.s);
    if (!record->dfc_100_fail_flags.null) free(record->dfc_100_fail_flags.s);
}

void system_record_free_data(system_record* const restrict record) {
    if (!record->date.null) free(record->date.s);
    if (!record->time.null) free(record->time.s);
}

void engine_record_free_data(engine_record* const restrict record) {
    if (!record->date.null) free(record->date.s);
    if (!record->time.null) free(record->time.s);
    if (!record->discrete_inputs.null) free(record->discrete_inputs.s);
    if (!record->discrete_outputs.null) free(record->discrete_outputs.s);
}
